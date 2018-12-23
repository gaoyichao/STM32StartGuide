#ifndef IAP_HEX_H
#define IAP_HEX_H

#include <types.h>

#define CFG_HEX_RECV_TIMEOUT 10000



struct iap_hex_record {
    uint8 len;
    uint16 offset;
    uint8 type;
    uint8 data[256];
};

struct iap_hex_parser {
    uint32 base_addr;
    uint32 start_addr;
    struct iap_hex_record record;
};

extern struct iap_hex_parser gIapHexParser;

#define IAP_HexType_ExtLinearAdd_Record 0x04
#define IAP_HexType_StartLinearAdd_Record 0x05
#define IAP_HexType_Data_Record 0x00
#define IAP_HexType_Eof_Record 0x01

typedef uint8 Iap_ErrType;
#define Iap_NoErr        ((uint8)0x00)   // 没错
#define Iap_Finished     ((uint8)0x01)   // Hex文件发送结束
#define Iap_CheckErr     ((uint8)0x10)   // 校验错误
#define Iap_WrongErr     ((uint8)0x40)   // 不可能的指令
#define Iap_TimeOutErr   ((uint8)0x80)   // 通信超时

Iap_ErrType IapHex_Update(struct iap_hex_parser *parser);

#endif
