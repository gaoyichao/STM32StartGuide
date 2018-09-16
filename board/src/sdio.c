#include <sdio.h>
#include <stm32f407.h>

#include <utils.h>

/*
 * sdio_init_hw - 初始化SDIO的硬件配置
 *
 * 设置PC8, PC9, PC10, PC11复用做SDIO_D[0:3], 上拉, 推挽
 * 设置PD2复用做SDIO_CMD, 上拉, 推挽
 * 设置PC12复用做SDIO_CK, 浮空, 推挽
 * 开启APB2总线上的SDIO驱动时钟
 * 开启DMA2的驱动时钟
 */
static void sdio_init_hw(void) {
    struct gpio_pin_conf pincof;
    // 时钟
    RCC->AHB1ENR.bits.gpioc = 1;
    RCC->AHB1ENR.bits.gpiod = 1;
    RCC->APB2ENR.bits.sdio = 1;
    RCC->AHB1ENR.bits.dma2 = 1;
    // 功能选择
    GPIOC->AFR.bits.pin8 = GPIO_AF_SDIO;
    GPIOC->AFR.bits.pin9 = GPIO_AF_SDIO;
    GPIOC->AFR.bits.pin10 = GPIO_AF_SDIO;
    GPIOC->AFR.bits.pin11 = GPIO_AF_SDIO;
    GPIOC->AFR.bits.pin12 = GPIO_AF_SDIO;
    GPIOD->AFR.bits.pin2 = GPIO_AF_SDIO;
    // PC8, PC9, PC10, PC11 ==> D0, D1, D2, D3
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;
    pincof.speed = GPIO_OSpeed_Medium;
    pincof.pull = GPIO_Pull_Up;
    gpio_init(GPIOC, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11, &pincof);
    // PD2 ==> CMD
    gpio_init(GPIOD, GPIO_Pin_2, &pincof);
    // PC12 ==> CLK
    pincof.pull = GPIO_Pull_No;
    gpio_init(GPIOC, GPIO_Pin_12, &pincof);
}
/*
 * sdio_check_resp0 - 我们把不响应定义为响应R0
 */
static enum SD_Error sdio_check_resp0(void) {
    enum SD_Error e = SDE_ERROR;
    uint32 timeout = SDIO_TIMEOUT;

    // 判定response
    while ((timeout > 0) && (0 == SDIO->STA.bits.cmdsent))
        timeout--;
    e = (0 == timeout) ? SDE_CMD_RSP_TIMEOUT : SDE_OK;
    SDIO->ICR.bits.cmdsentc = 1;

    return e;
}

static enum SD_Error sdio_check_resp1(struct sd_card *card, uint8 cmd) {
    uint32 status = SDIO->STA.all;

    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
        status = SDIO->STA.all;

    if (status & SDIO_FLAG_CTIMEOUT) {
        SDIO->ICR.bits.ctimeoutc = 1;
        return SDE_CMD_RSP_TIMEOUT;
    } else if (status & SDIO_FLAG_CCRCFAIL) {
        SDIO->ICR.bits.ccrcfailc = 1;
        return SDE_CMD_CRC_FAIL;
    }

    if (SDIO->RESPCMD.bits.RESPCMD != cmd) {
        return SDE_ILLEGAL_CMD;
    }

    // 清除所有状态
    SDIO->ICR.all = 0x05FF;
    card->csr.all = SDIO->RESP1;

    if (0 == (card->csr.all & SD_CSR_ERRORBITS))
        return SDE_OK;
    else
        return SDE_CS_ERROR;
}

static enum SD_Error sdio_check_resp2(void) {
    uint32 status = SDIO->STA.all;

    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
        status = SDIO->STA.all;

    if (status & SDIO_FLAG_CTIMEOUT) {
        SDIO->ICR.bits.ctimeoutc = 1;
        return SDE_CMD_RSP_TIMEOUT;
    } else if (status & SDIO_FLAG_CCRCFAIL) {
        SDIO->ICR.bits.ccrcfailc = 1;
        return SDE_CMD_CRC_FAIL;
    }

    SDIO->ICR.all = 0x05FF;
    return SDE_OK;
}

static enum SD_Error sdio_check_resp3(void) {
    uint32 status = SDIO->STA.all;

    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
        status = SDIO->STA.all;

    if (status & SDIO_FLAG_CTIMEOUT) {
        SDIO->ICR.bits.ctimeoutc = 1;
        return SDE_CMD_RSP_TIMEOUT;
    }
    // 为什么不检测CRC校验
    SDIO->ICR.all = 0x05FF;
    return SDE_OK;
}

static enum SD_Error sdio_check_resp6(uint8 cmd, uint16 *rca) {
    uint32 status = SDIO->STA.all;

    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
        status = SDIO->STA.all;

    if (status & SDIO_FLAG_CTIMEOUT) {
        SDIO->ICR.bits.ctimeoutc = 1;
        return SDE_CMD_RSP_TIMEOUT;
    } else if (status & SDIO_FLAG_CCRCFAIL) {
        SDIO->ICR.bits.ccrcfailc = 1;
        return SDE_CMD_CRC_FAIL;
    }

    if (SDIO->RESPCMD.bits.RESPCMD != cmd) {
        return SDE_ILLEGAL_CMD;
    }

    // 清除所有状态
    SDIO->ICR.all = 0x05FF;
    uint32 r1 = SDIO->RESP1;

    if (r1 & SD_R6_GENERAL_UNKNOWN_ERROR)
        return SDE_GENERAL_UNKNOWN_ERROR;
    if (r1 & SD_R6_ILLEGAL_CMD)
        return SDE_ILLEGAL_CMD;
    if (r1 & SD_R6_COM_CRC_FAILED)
        return SDE_COM_CRC_FAILED;

    *rca = (uint16)(r1 >> 16);
    return SDE_OK;
}

/*
 * sdio_check_resp7 - SD卡的接口条件，CMD8的响应
 */
static enum SD_Error sdio_check_resp7(uint32 vol) {
    enum SD_Error e = SDE_ERROR;
    uint32 status = SDIO->STA.all;

    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT))) {
        status = SDIO->STA.all;
    }

    if (status & SDIO_FLAG_CTIMEOUT) {
        e = SDE_CMD_RSP_TIMEOUT;
        SDIO->ICR.bits.ctimeoutc = 1;
    } else if (status & SDIO_FLAG_CCRCFAIL) {
        e = SDE_CMD_CRC_FAIL;
        SDIO->ICR.bits.ccrcfailc = 1;
    } else if (SDIO_FLAG_CMDREND & status) {
        // 判定返回数据是否与CMD8请求一致
        e = (vol == SDIO->RESP1) ? SDE_OK : SDE_ERROR;
        SDIO->ICR.bits.cmdrendc = 1;
    }

    return e;
}

/*
 * sdio_cmd8 - 发送CMD8判定SD卡是否支持V2.0版的协议
 *
 * 如果响应超时则认为支持V1.1版的协议
 * 如果成功返回则认为支持V2.0版的协议
 */
static enum SD_Error sdio_cmd8(void) {
    sdio_send_cmd(SDIO_CMD_SEND_IF_COND, SD_CHECK_PATTERN, SDIO_Response_Short);
    return sdio_check_resp7(SD_CHECK_PATTERN);
}

static enum SD_Error sdio_cmd55(struct sd_card *card, uint32 arg) {
    sdio_send_cmd(SD_CMD_APP_CMD, arg, SDIO_Response_Short);
    return sdio_check_resp1(card, SD_CMD_APP_CMD);
}

static enum SD_Error sdio_cmd41(void) {
    sdio_send_cmd(SD_CMD_SD_APP_OP_COND, SD_VOLTAGE_WINDOW_SD | SD_HIGH_CAPACITY, SDIO_Response_Short);
    return sdio_check_resp3();
}

/*
 * sdio_find_scr - 获取SD卡的 SCR寄存器的值
 *
 * @rca: 选择SD卡地址
 * @pscr: 输出SCR寄存器的缓存地址
 */
static enum SD_Error sdio_find_scr(struct sd_card *card, uint16 rca, uint32 *pscr) {
    enum SD_Error e = SDE_OK;
    union sdio_dctrl dctrl;

    // 设置Block大小为8字节
    sdio_send_cmd(SD_CMD_SET_BLOCKLEN, 8, SDIO_Response_Short);
    e = sdio_check_resp1(card, SD_CMD_SET_BLOCKLEN);
    if (SDE_OK != e)
        return e;

    e = sdio_cmd55(card, (uint32)rca << 16);
    if (SDE_OK != e)
        return e;

    dctrl.all = SDIO->DCTRL.all;
    dctrl.bits.DBLOCKSIZE = SDIO_DataBlockSize_8b;
    dctrl.bits.DTDIR = SDIO_TransDir_ToSdio;
    dctrl.bits.DTMODE = SDIO_TransMode_Block;
    dctrl.bits.DTEN = 1;
    sdio_config_data(dctrl, SD_DATATIMEOUT, 8);

    sdio_send_cmd(SD_CMD_SD_APP_SEND_SCR, 0, SDIO_Response_Short);
    e = sdio_check_resp1(card, SD_CMD_SD_APP_SEND_SCR);
    if (SDE_OK != e)
        return e;

    uint32 i = 1;
    union sdio_sta status = SDIO->STA;
    while (!(status.all & (SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))) {
        if (status.bits.rxdavl == 1) {
            pscr[i] = change_ending_32b(SDIO->FIFO);
            i--;
        }
        status = SDIO->STA;
    }

    if (status.bits.dtimeout) {
        SDIO->ICR.bits.dtimeoutc = 1;
        return SDE_DATA_TIMEOUT;
    } else if (status.bits.dcrcfail) {
        SDIO->ICR.bits.dcrcfailc = 1;
        return SDE_DATA_CRC_FAIL;
    } else if (status.bits.rxoverr) {
        SDIO->ICR.bits.rxoverrc = 1;
        return SDE_RX_OVERRUN;
    } else if (status.bits.stbiterr) {
        SDIO->ICR.bits.stbiterrc = 1;
        return SDE_START_BIT_ERR;
    }

    SDIO->ICR.all = 0x05FF;

    return e;
}

/*
 * sdio_load_card_info - 装载SD卡信息
 */
static enum SD_Error sdio_load_card_info(struct sd_card *card) {
    enum SD_Error e = SDE_OK;

    if (SDIO_Power_Off == SDIO->POWER.bits.PWRCTRL) {
        e = SDE_ERROR;
        return e;
    }

    sdio_send_cmd(SD_CMD_SEND_CSD, (uint32)(card->rca << 16), SDIO_Response_Long);
    e = sdio_check_resp2();
    if (SDE_OK != e)
        return e;

    card->csd.words[0] = SDIO->RESP1;
    card->csd.words[1] = SDIO->RESP2;
    card->csd.words[2] = SDIO->RESP3;
    card->csd.words[3] = SDIO->RESP4;

    card->blocknum = ((card->csd.bits.DeviceSizeH << 2) + card->csd.bits.DeviceSizeL);
    card->blocknum += 1;
    card->blocknum *= (1 << card->csd.bits.DeviceSizeMul + 2);
    card->blocksize = 1 << card->csd.bits.RdBlockLen;
    card->capacity = card->blocknum * card->blocksize;

    return SDE_OK;
}

/*
 * sdio_sel_desel - 选择设备
 */
enum SD_Error sdio_sel(struct sd_card *card) {
    sdio_send_cmd(SD_CMD_SEL_DESEL_CARD, (uint32)(card->rca) << 16, SDIO_Response_Short);
    return sdio_check_resp1(card, SD_CMD_SEL_DESEL_CARD);
}
/*
 * sdio_en_widemode - 开启多线传输模式
 *
 * 只支持4线
 *
 * @rca: 设备地址
 */
enum SD_Error sdio_en_widemode(struct sd_card *card) {
    enum SD_Error e = SDE_OK;
    uint32 scr[2] = { 0, 0 };

    if (SDIO->RESP1 & SD_CARD_LOCKED) {
        e = SDE_LOCK_UNLOCK_FAILED;
        return e;
    }

    e = sdio_find_scr(card, card->rca, scr);
    if (SDE_OK != e)
        return e;

    if (SD_WIDE_BUS_SUPPORT & scr[1]) {
        e = sdio_cmd55(card, (uint32)(card->rca) << 16);
        if (SDE_OK != e)
            return e;

        sdio_send_cmd(SD_CMD_APP_SD_SET_BUSWIDTH, 2, SDIO_Response_Short);
        e = sdio_check_resp1(card, SD_CMD_APP_SD_SET_BUSWIDTH);
        if (SDE_OK != e)
            return e;

        sdio_init_clkcr(0, SDIO_BusWid_4);
        return e;
    } else {
        return SDE_ERROR;
    }
}
/*
 * sdio_en_widemode - 关闭多线传输模式
 *
 * @rca: 设备地址
 */
enum SD_Error sdio_dis_widemode(struct sd_card *card, uint16 rca) {
    enum SD_Error e = SDE_OK;
    uint32 scr[2] = { 0, 0 };

    if (SDIO->RESP1 & SD_CARD_LOCKED) {
        e = SDE_LOCK_UNLOCK_FAILED;
        return e;
    }

    e = sdio_find_scr(card, rca, scr);
    if (SDE_OK != e)
        return e;

    if (SD_SINGLE_BUS_SUPPORT & scr[1]) {
        e = sdio_cmd55(card, (uint32)rca << 16);
        if (SDE_OK != e)
            return e;

        sdio_send_cmd(SD_CMD_APP_SD_SET_BUSWIDTH, 0, SDIO_Response_Short);
        e = sdio_check_resp1(card, SD_CMD_APP_SD_SET_BUSWIDTH);
        if (SDE_OK != e)
            return e;

        sdio_init_clkcr(0, SDIO_BusWid_1);
        return e;
    } else {
        return SDE_ERROR;
    }
}

/*
 * sdio_init_interface - 初始化SDIO接口
 */
static void sdio_init_interface() {
    sdio_init_hw();

    sdio_init_clkcr(118, SDIO_BusWid_1);

    SDIO->POWER.bits.PWRCTRL = SDIO_Power_On;
    SDIO->CLKCR.bits.CLKEN = 1;
}
/*
 * sdio_init_card - SD卡的枚举过程
 */
static enum SD_Error sdio_init_card(struct sd_card *card) {
    sdio_send_cmd(SD_CMD_GO_IDLE_STATE, 0, SDIO_Response_No);
    enum SD_Error e = sdio_check_resp0();
    if (SDE_OK != e)
        return e;

    e = sdio_cmd8();
    if (SDE_CMD_RSP_TIMEOUT == e)
        card->cardtype = SDIO_STD_CAPACITY_SD_CARD_V1_1;
    else if (SDE_OK == e)
        card->cardtype = SDIO_STD_CAPACITY_SD_CARD_V2_0;
    else
        return e;

    BOOL ready = FALSE;
    uint32 count = 0, res = 0;
    while (!ready && (count < SD_MAX_VOLT_TRIAL)) {
        e = sdio_cmd55(card, 0);
        if (SDE_OK != e)
            return e;
        e = sdio_cmd41();
        if (SDE_OK != e)
            return e;
        res = SDIO->RESP1;
        ready = (((res >> 31) == 1) ? TRUE : FALSE);
        count++;
    }

    if (count >= SD_MAX_VOLT_TRIAL)
        return SDE_INVALID_VOLTRANGE;

    if (SDIO_STD_CAPACITY_SD_CARD_V2_0 == card->cardtype)
        card->cardtype = (((res >> 30) & 1) ? SDIO_HIGH_CAPACITY_SD_CARD : SDIO_STD_CAPACITY_SD_CARD_V2_0);

    // CMD2: 获取枚举信息CID
    sdio_send_cmd(SD_CMD_ALL_SEND_CID, 0, SDIO_Response_Long);
    e = sdio_check_resp2();
    if (SDE_OK != e)
        return e;
    card->cid.words[0] = SDIO->RESP1;
    card->cid.words[1] = SDIO->RESP2;
    card->cid.words[2] = SDIO->RESP3;
    card->cid.words[3] = SDIO->RESP4;

    // CMD3
    sdio_send_cmd(SD_CMD_SET_REL_ADDR, 0, SDIO_Response_Short);
    uint16 rca = 0x01;
    e = sdio_check_resp6(SD_CMD_SET_REL_ADDR, &rca);
    if (SDE_OK != e)
        return e;
    card->rca = rca;

    return SDE_OK;
}

/*
 * sdio_init - 初始化SDIO设备
 */
enum SD_Error sdio_init(struct sd_card *card) {
    sdio_init_interface();

    enum SD_Error e = sdio_init_card(card);
    if (SDE_OK != e)
        return e;

    sdio_init_clkcr(0, SDIO_BusWid_1);

    e = sdio_load_card_info(card);
    if (SDE_OK != e)
        return e;

    e = sdio_sel(card);
    if (SDE_OK != e)
        return e;

    e = sdio_en_widemode(card);

    return e;
}
/*
 * sdio_read_block - 读一个block的数据,通过DMA实现
 *
 * @card: 目标SD卡
 * @bnum: 需要读取block地址
 * @buf: 缓存地址
 */
enum SD_Error sdio_read_block(struct sd_card *card, uint32 bnum, uint8 *buf) {
    // 设置Block大小
    uint16 blocksize = card->blocksize;
    sdio_send_cmd(SD_CMD_SET_BLOCKLEN, blocksize, SDIO_Response_Short);
    enum SD_Error e = sdio_check_resp1(card, SD_CMD_SET_BLOCKLEN);
    if (SDE_OK != e)
        return e;
    // 设置数据
    SDIO->DCTRL.all = 0;
    union sdio_dctrl dctrl;
    dctrl.all = SDIO->DCTRL.all;
    dctrl.bits.DBLOCKSIZE = SDIO_DataBlockSize_512b;
    dctrl.bits.DTDIR = SDIO_TransDir_ToSdio;
    dctrl.bits.DTMODE = SDIO_TransMode_Block;
    dctrl.bits.DTEN = 1;
    sdio_config_data(dctrl, SD_DATATIMEOUT, blocksize);
    // CMD17
    sdio_send_cmd(SD_CMD_READ_SINGLE_BLOCK, bnum, SDIO_Response_Short);
    e = sdio_check_resp1(card, SD_CMD_READ_SINGLE_BLOCK);
    if (SDE_OK != e)
        return e;
    // 开启DMA和中断
    sdio_enable_interrupts();
    SDIO->DCTRL.bits.DMAEN = 1;
    sdio_config_dma_rx((uint32 *)buf, blocksize);
    return e;
}
/*
 * sdio_write_block - 写一个block的数据,通过DMA实现
 *
 * @card: 目标SD卡
 * @bnum: 需要写数据的block地址
 * @buf: 缓存地址
 */
enum SD_Error sdio_write_block(struct sd_card *card, uint32 bnum, const uint8 *buf) {
    // 设置Block大小
    uint16 blocksize = card->blocksize;
    sdio_send_cmd(SD_CMD_SET_BLOCKLEN, blocksize, SDIO_Response_Short);
    enum SD_Error e = sdio_check_resp1(card, SD_CMD_SET_BLOCKLEN);
    if (SDE_OK != e)
        return e;
    // 设置数据
    SDIO->DCTRL.all = 0;
    union sdio_dctrl dctrl;
    dctrl.all = SDIO->DCTRL.all;
    dctrl.bits.DBLOCKSIZE = SDIO_DataBlockSize_512b;
    dctrl.bits.DTDIR = SDIO_TransDir_ToCard;
    dctrl.bits.DTMODE = SDIO_TransMode_Block;
    dctrl.bits.DTEN = 1;
    sdio_config_data(dctrl, SD_DATATIMEOUT, blocksize);
    // CMD24
    sdio_send_cmd(SD_CMD_WRITE_SINGLE_BLOCK, bnum, SDIO_Response_Short);
    e = sdio_check_resp1(card, SD_CMD_WRITE_SINGLE_BLOCK);
    if (SDE_OK != e)
        return e;
    // 开启DMA和中断
    sdio_enable_interrupts();
    SDIO->DCTRL.bits.DMAEN = 1;
    sdio_config_dma_tx((uint32 *)buf, blocksize);
    return e;
}



void SDIO_IRQHandler(void) {
    if (SDIO->STA.bits.dataend) {
        SDIO->ICR.bits.dataendc = 1;
        uart_send_byte(USART1, 'g');
    } else if (SDIO->STA.bits.dcrcfail) {
        uart_send_byte(USART1, 'a');
        SDIO->ICR.bits.dcrcfailc = 1;
    } else if (SDIO->STA.bits.dtimeout) {
        uart_send_byte(USART1, 'b');
        SDIO->ICR.bits.dtimeoutc = 1;
    } else if (SDIO->STA.bits.rxoverr) {
        uart_send_byte(USART1, 'c');
        SDIO->ICR.bits.rxoverrc = 1;
    } else if (SDIO->STA.bits.stbiterr) {
        uart_send_byte(USART1, 'd');
        SDIO->ICR.bits.stbiterrc = 1;
    }

    sdio_disable_interrupts();
}

void DMA2_Stream3_IRQHandler(void) {
    if (1 == DMA2->LISR.bits.TCIF3) {
        DMA2->LIFCR.bits.TCIF3 = 1;
        uart_send_byte(USART1, 'y');
    }
}

