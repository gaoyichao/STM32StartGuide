#include <iap_hex.h>
#include <stm32f4xx_flash.h>
#include <utils.h>

struct iap_hex_parser gIapHexParser;
/******************************************************************************/
#include <usart1.h>

#define IapHex_DataBufCount() usart1_buf_count()
#define IapHex_RecvByte(pByte) usart1_rsv_byte((pByte))
#define IapHex_SendByte(data) uart_send_byte(USART1, (data))

/******************************************************************************/

/*
 * IapHex_ExpectByte - 期望接收到字节@data
 *
 * 若没有接收到字节,返回Iap_TimeOutErr
 * 若接收到字节与@data不一致,返回Iap_CheckErr
 * 若接收到字节与@data一致,返回Iap_NoErr
 */
static Iap_ErrType IapHex_ExpectByte(uint8 data) {
    uint32 times = 0;
    uint8 rcv;

    while (!IapHex_RecvByte(&rcv)) {
        times++;
        if (times > CFG_HEX_RECV_TIMEOUT)
            return Iap_TimeOutErr;
    }

    if (data != rcv)
        return Iap_CheckErr;

    return Iap_NoErr;
}

/*
 * IapHex_ParseByte - 解析一个字节
 *
 * @buf: 接收数据缓存
 * return: 错误信息
 */
static Iap_ErrType IapHex_ParseByte(uint8 *buf) {
    uint32 times = 0;
    while (IapHex_DataBufCount() < 2) {
        times++;
        if (times > CFG_HEX_RECV_TIMEOUT)
            return Iap_TimeOutErr;
    }

    uint8 tmpH, tmpL;
    IapHex_RecvByte(&tmpH);
    IapHex_RecvByte(&tmpL);

    buf[0] = (HexChar2Uint8(tmpH) << 4) + HexChar2Uint8(tmpL);

    return Iap_NoErr;
}

#define PARSE(data) {                 \
    err = IapHex_ParseByte((data));       \
    if (Iap_NoErr != err)                \
        return err;                     \
}

#define EXPECT(data) {              \
    err = IapHex_ExpectByte((data));    \
    if (Iap_NoErr != err)            \
        return err;                 \
}

/*
 * IapHex_RecvRecord - 接收记录
 *
 * @parser: HEX文件解析器
 */
Iap_ErrType IapHex_RecvRecord(struct iap_hex_parser *parser) {
    Iap_ErrType err;
    uint8 sum = 0, sum_rcv, len;

    EXPECT(':');
    PARSE(&len);
    parser->record.len = len;
    
    uint8 *offset = (uint8*)&(parser->record.offset);    
    PARSE(&(offset[1]));
    PARSE(&(offset[0]));
    
    PARSE(&(parser->record.type));
    
    for (int i = 0; i < len; i++)
        PARSE(&(parser->record.data[i]));

    PARSE(&sum_rcv);
    
    sum = 0x100 - len - offset[0] - offset[1] - parser->record.type;
    for (int i = 0; i < len; i++)
        sum -= parser->record.data[i];
    
    if (sum != sum_rcv)
        return Iap_CheckErr;
    
    return Iap_NoErr;
}

int gEraseSectorIdx = 1;

Iap_ErrType IapHex_ProgramData(struct iap_hex_parser *parser) {
    uint32 addr = parser->base_addr + parser->record.offset;
    int len = parser->record.len;
    uint8 *data = parser->record.data;
   
    flash_unlock();
    for (int i = 0; i < len; i++) {
        if (addr == flash_sector_start_addr[gEraseSectorIdx]) {
            flash_sector_erase(gEraseSectorIdx);
            gEraseSectorIdx++;
        }
        
        flash_write_byte(addr, data[i]);
        addr++;
    }
    flash_lock();
    return Iap_NoErr;
}
/*
 * IapHex_HandleRecord - 处理记录
 */
Iap_ErrType IapHex_HandleRecord(struct iap_hex_parser *parser) {
    uint8 *data = parser->record.data;
    
    switch (parser->record.type) {
    case IAP_HexType_Eof_Record:
        return Iap_Finished;
    case IAP_HexType_Data_Record:
        return IapHex_ProgramData(parser);
    case IAP_HexType_ExtLinearAdd_Record:
        parser->base_addr = (data[0] << 24) + (data[1] << 16);
        break;
    case IAP_HexType_StartLinearAdd_Record:
        parser->start_addr = (data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3];
        break;
    }
    return Iap_NoErr;
}
/*
 * IapHex_Update - 根据Hex文件更新Flash
 */
Iap_ErrType IapHex_Update(struct iap_hex_parser *parser) {
    Iap_ErrType err;
    
    while (1) {
        IapHex_SendByte('Y');
        if (Iap_NoErr != IapHex_RecvRecord(parser))
            continue;
        
        err = IapHex_HandleRecord(parser);
        if (Iap_Finished == err) {
            IapHex_SendByte('Z');
            return Iap_NoErr;
        } else if (Iap_NoErr != err) {
            IapHex_SendByte('N');
            return err;
        }
    }
}

