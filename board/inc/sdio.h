#ifndef SDIO_H
#define SDIO_H

#include <stm32f4xx_sdio.h>

#define SD_CMD_GO_IDLE_STATE                       ((uint8)0)
#define SD_CMD_SEND_OP_COND                        ((uint8)1)
#define SD_CMD_ALL_SEND_CID                        ((uint8)2)
#define SD_CMD_SET_REL_ADDR                        ((uint8)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define SD_CMD_SET_DSR                             ((uint8)4)
#define SD_CMD_SDIO_SEN_OP_COND                    ((uint8)5)
#define SD_CMD_HS_SWITCH                           ((uint8)6)
#define SD_CMD_SEL_DESEL_CARD                      ((uint8)7)
#define SD_CMD_HS_SEND_EXT_CSD                     ((uint8)8)
#define SD_CMD_SEND_CSD                            ((uint8)9)
#define SD_CMD_SEND_CID                            ((uint8)10)
#define SD_CMD_READ_DAT_UNTIL_STOP                 ((uint8)11) /*!< SD Card doesn't support it */
#define SD_CMD_STOP_TRANSMISSION                   ((uint8)12)
#define SD_CMD_SEND_STATUS                         ((uint8)13)
#define SD_CMD_HS_BUSTEST_READ                     ((uint8)14)
#define SD_CMD_GO_INACTIVE_STATE                   ((uint8)15)
#define SD_CMD_SET_BLOCKLEN                        ((uint8)16)
#define SD_CMD_READ_SINGLE_BLOCK                   ((uint8)17)
#define SD_CMD_READ_MULT_BLOCK                     ((uint8)18)
#define SD_CMD_HS_BUSTEST_WRITE                    ((uint8)19)
#define SD_CMD_WRITE_DAT_UNTIL_STOP                ((uint8)20) /*!< SD Card doesn't support it */
#define SD_CMD_SET_BLOCK_COUNT                     ((uint8)23) /*!< SD Card doesn't support it */
#define SD_CMD_WRITE_SINGLE_BLOCK                  ((uint8)24)
#define SD_CMD_WRITE_MULT_BLOCK                    ((uint8)25)
#define SD_CMD_PROG_CID                            ((uint8)26) /*!< reserved for manufacturers */
#define SD_CMD_PROG_CSD                            ((uint8)27)
#define SD_CMD_SET_WRITE_PROT                      ((uint8)28)
#define SD_CMD_CLR_WRITE_PROT                      ((uint8)29)
#define SD_CMD_SEND_WRITE_PROT                     ((uint8)30)
#define SD_CMD_SD_ERASE_GRP_START                  ((uint8)32) /*!< To set the address of the first write block to be erased. (For SD card only) */
#define SD_CMD_SD_ERASE_GRP_END                    ((uint8)33) /*!< To set the address of the last write block of the continuous range to be erased. (For SD card only) */
#define SD_CMD_ERASE_GRP_START                     ((uint8)35) /*!< To set the address of the first write block to be erased. (For MMC card only spec 3.31) */
#define SD_CMD_ERASE_GRP_END                       ((uint8)36) /*!< To set the address of the last write block of the continuous range to be erased. (For MMC card only spec 3.31) */
#define SD_CMD_ERASE                               ((uint8)38)
#define SD_CMD_FAST_IO                             ((uint8)39) /*!< SD Card doesn't support it */
#define SD_CMD_GO_IRQ_STATE                        ((uint8)40) /*!< SD Card doesn't support it */
#define SD_CMD_LOCK_UNLOCK                         ((uint8)42)
#define SD_CMD_APP_CMD                             ((uint8)55)
#define SD_CMD_GEN_CMD                             ((uint8)56)
#define SD_CMD_NO_CMD                              ((uint8)64)
/*
 * Following commands are SD Card Specific commands.
 * SDIO_APP_CMD should be sent before sending these commands.
 */
#define SD_CMD_APP_SD_SET_BUSWIDTH                 ((uint8)6)  /*!< For SD Card only */
#define SD_CMD_SD_APP_STAUS                        ((uint8)13) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        ((uint8)22) /*!< For SD Card only */
#define SD_CMD_SD_APP_OP_COND                      ((uint8)41) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CLR_CARD_DETECT          ((uint8)42) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_SCR                     ((uint8)51) /*!< For SD Card only */
#define SD_CMD_SDIO_RW_DIRECT                      ((uint8)52) /*!< For SD I/O Card only */
#define SD_CMD_SDIO_RW_EXTENDED                    ((uint8)53) /*!< For SD I/O Card only */


#define SDIO_CMD_SEND_IF_COND       (8)

#define SDIO_TIMEOUT            (10000)

#define SD_CHECK_PATTERN        ((uint32)0x000001AA)

/*
 * Supported SD Memory Cards
 */
#define SDIO_STD_CAPACITY_SD_CARD_V1_1             ((uint32)0x00000000)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0             ((uint32)0x00000001)
#define SDIO_HIGH_CAPACITY_SD_CARD                 ((uint32)0x00000002)
#define SDIO_MULTIMEDIA_CARD                       ((uint32)0x00000003)
#define SDIO_SECURE_DIGITAL_IO_CARD                ((uint32)0x00000004)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD            ((uint32)0x00000005)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD          ((uint32)0x00000006)
#define SDIO_HIGH_CAPACITY_MMC_CARD                ((uint32)0x00000007)

/*
 * Mask for errors Card Status R1
 */
#define SD_CSR_ERRORBITS                ((uint32)0xFDFFE008)

#define SD_CS_IDLE  0x0
#define SD_CS_READY 0x1
#define SD_CS_IDENT 0x2
#define SD_CS_STBY  0x3
#define SD_CS_TRAN  0x4
#define SD_CS_DATA  0x5
#define SD_CS_RCV   0x6
#define SD_CS_PRG   0x7
#define SD_CS_DIS   0x8

struct sd_csr_bits {
    uint32 rsv0 : 3;                /* 0: 保留 */
    uint32 AKE_SEQ_ERROR : 1;       /* 3: Error in the sequence of the authentication process */
    uint32 rsv1 : 1;                /* 4: 保留 */
    uint32 APP_CMD : 1;             /* 5: 一个ACMD */
    uint32 rsv2 : 2;                /* 6: 保留 */
    uint32 READY_FOR_DATA : 1;      /* 8: 缓存为空 */
    uint32 CURRENT_STATE : 4;       /* 9: 卡的当前状态 */
    uint32 ERASE_RESET : 1;         /* 13: 擦写操作清除 */
    uint32 CARD_ECC_DISABLED : 1;   /* 14: The command has been executed without internal ECC */
    uint32 WP_ERASE_SKIP : 1;       /* 15: 因为写保护导致部分擦写 */
    uint32 CSD_OVERWRITE : 1;       /* 16: 文档没看懂，反正就是出错了 */
    uint32 rsv3 : 2;                /* 17: 保留 */
    uint32 ERROR : 1;               /* 19: 就是出错了 */
    uint32 CC_ERROR : 1;            /* 20: 内部的卡控制器出错 */
    uint32 CARD_ECC_FAILED : 1;     /* 21: 应用了卡内部的ECC，但仍然没有修正数据 */
    uint32 ILLEGAL_COMMAND : 1;     /* 22: 非法指令 */
    uint32 COM_CRC_ERROR : 1;       /* 23: 上一条指令的CRC校验错误 */
    uint32 LOCK_UNLOCK_FAILED : 1;  /* 24: 就是锁或者解锁时出错 */
    uint32 CARD_IS_LOCKED : 1;      /* 25: 卡被宿主锁了 */
    uint32 WP_VIOLATION : 1;        /* 26: 企图写受保护的区域 */
    uint32 ERASE_PARAM : 1;         /* 27: 文档没看懂 */
    uint32 ERASE_SEQ_ERROR : 1;     /* 28: 擦写指令序列错误 */
    uint32 BLOCK_LEN_ERROR : 1;     /* 29: 发送数据块长度与卡支持的不符 */
    uint32 ADDRESS_ERROR : 1;       /* 30: misaligned address */
    uint32 OUT_OF_RANGE : 1;        /* 31: 溢出 */
};

union sd_csr {
    struct sd_csr_bits bits;
    uint32 all;
};

/*
 * Masks for R6 Response
 */
#define SD_R6_GENERAL_UNKNOWN_ERROR     ((uint32)0x00002000)
#define SD_R6_ILLEGAL_CMD               ((uint32)0x00004000)
#define SD_R6_COM_CRC_FAILED            ((uint32)0x00008000)

#define SD_VOLTAGE_WINDOW_SD            ((uint32)0x80100000)
#define SD_HIGH_CAPACITY                ((uint32)0x40000000)
#define SD_STD_CAPACITY                 ((uint32)0x00000000)
#define SD_CHECK_PATTERN                ((uint32)0x000001AA)

#define SD_MAX_VOLT_TRIAL               ((uint32)0x0000FFFF)
#define SD_ALLZERO                      ((uint32)0x00000000)

#define SD_WIDE_BUS_SUPPORT             ((uint32)0x00040000)
#define SD_SINGLE_BUS_SUPPORT           ((uint32)0x00010000)
#define SD_CARD_LOCKED                  ((uint32)0x02000000)

#define SD_DATATIMEOUT                  ((uint32)0xFFFFFFFF)
#define SD_0TO7BITS                     ((uint32)0x000000FF)
#define SD_8TO15BITS                    ((uint32)0x0000FF00)
#define SD_16TO23BITS                   ((uint32)0x00FF0000)
#define SD_24TO31BITS                   ((uint32)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((uint32)0x01FFFFFF)

#define SD_HALFFIFO                     ((uint32)0x00000008)
#define SD_HALFFIFOBYTES                ((uint32)0x00000020)

/*
 * card specification data
 */
struct sd_csd_bits {
    // csd_tab[0]
    uint32 MaxBusClkFrec : 8;
    uint32 NSAC : 8;
    uint32 TAAC : 8;
    uint32 rsv1 : 2;
    uint32 SysSpecVersion : 4;
    uint32 CSDStruct : 2;
    // csd_tab[1]
    uint32 DeviceSizeH : 10;
    uint32 rsv2 : 2;
    uint32 DSRImpl : 1;
    uint32 RdBlockMisalign : 1;
    uint32 WrBlockMisalign : 1;
    uint32 PartBlockRead : 1;
    uint32 RdBlockLen : 4;
    uint32 CardComdClasses : 12;
    // csd_tab[2]
    uint32 WrProtectGrSize : 7;
    uint32 EraseGrMul : 7;
    uint32 EraseGrSize : 1;
    uint32 DeviceSizeMul : 3;
    uint32 MaxWrCurrentVDDMax : 3;
    uint32 MaxWrCurrentVDDMin : 3;
    uint32 MaxRdCurrentVDDMax : 3;
    uint32 MaxRdCurrentVDDMin : 3;
    uint32 DeviceSizeL : 2;
    // csd_tab[3]
    uint32 rsv4 : 1;
    uint32 CSD_CRC : 7;
    uint32 ECC : 2;
    uint32 FileFormat : 2;
    uint32 TempWrProtect : 1;
    uint32 PermWrProtect : 1;
    uint32 CopyFlag : 1;
    uint32 FileFormatGrouop : 1;
    uint32 ContentProtectAppli : 1;
    uint32 rsv3 : 4;
    uint32 WriteBlockPaPartial : 1;
    uint32 MaxWrBlockLen : 4;
    uint32 WrSpeedFact : 3;
    uint32 ManDeflECC : 2;
    uint32 WrProtectGrEnable : 1;
};
union sd_csd {
    struct sd_csd_bits bits;
    uint32 words[4];
    uint8 bytes[16];
};

/*
 * card indentification data
 */
struct sd_cid_bits {
    uint32 ProdName1_H : 8;
    uint32 OEM_AppliID : 16;
    uint32 ManufacturerID : 8;
    uint32 ProdName2 : 8;
    uint32 ProdName1_L : 24;
    uint32 ProdSN_H : 24;
    uint32 ProdRev : 8;
    uint32 rsv2 : 1;
    uint32 CID_CRC : 7;
    uint32 ManufactDate : 12;
    uint32 rsv1 : 4;
    uint32 ProdSN_L : 8;
};
union sd_cid {
    struct sd_cid_bits bits;
    uint32 words[4];
    uint8 bytes[16];
};

struct sd_card {
    uint32 cardtype;
    uint32 rca;

    union sd_cid cid;   /* 卡标识号 */
    union sd_csd csd;   /* 卡描述数据 */
    union sd_csr csr;   /* 卡状态寄存器 */

    uint32 blocknum;
    uint32 blocksize;
    uint64 capacity;
};

enum SD_Error sdio_init(struct sd_card *card);
enum SD_Error sdio_read_block(struct sd_card *card, uint32 bnum, uint8 *buf);
enum SD_Error sdio_write_block(struct sd_card *card, uint32 bnum, const uint8 *buf);

#endif

