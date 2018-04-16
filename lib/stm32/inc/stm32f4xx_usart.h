/***********************************************************
 *
 * stm32f4xx_usart - 串口
 *
 ************************************** 高乙超.2017.0131 ***/
#pragma once

#include <types.h>

struct usart_sr_bits {
    // PE - 奇偶校验错误，由硬件置位。
    // 软件通过先读SR寄存器，再读/写DR寄存器，可以清除该位;
    // 但在清除该位之前，必须等待RXNE位置位。
    uint16 PE : 1;
    // FE - 帧错误，检测到不同步、噪声过大、或者接收到Bread帧时，有硬件置位。
    // 软件通过先读SR,再读DR寄存器清除该位。
    // 如果当前正在处理的数据，即产生了帧错误，又产生Overrun错误，那么数据将会被传送，同时只有ORE位置位。
    uint16 FE : 1;
    // NF - 噪声标志位，硬件置位。
    // 软件通过先读SR，再读DR寄存器清除该位
    uint16 NF : 1;
    // ORE - Overrun错误，当RXNE=1时，接收移位寄存器就已经完成接收新数据，并发送到RDR(读数据)寄存器中。
    // 软件通过先读SR,再读DR寄存器清除该位。
    uint16 ORE : 1;
    // IDLE - 硬件检测到Idle Line时置位，
    // 软件通过先读SR,再读DR寄存器清除该位。
    uint16 IDLE : 1;
    // RXNE - 读数据寄存器非空，硬件置位
    // 软件读DR寄存器就可以清除该位，但也可以通过直接向该位写0清空
    uint16 RXNE : 1;
    // TC - Transmission Complete, 发送完一帧并且TXE = 1时置位
    // 软件通过先读SR寄存器，再写DR寄存器，可以清除该位;但也可以通过直接向该位写0清空
    uint16 TC : 1;
    // TXE - 发送数据寄存器为空，当TDR寄存器中的数据写入发送移位寄存器时置位。
    // 软件写DR寄存器清除该位。
    uint16 TXE : 1;
    // LBD - LIN Bread Detection,
    // 软件写0清除
    uint16 LBD : 1;
    // CTS - 当输入CTS翻转时置位
    // 软件写0清除
    uint16 CTS : 1;
    uint16 rsv0 : 6;
    uint16 rsv1 : 16;
};

union usart_sr {
    struct usart_sr_bits bits;
    uint32 all;
};

struct usart_dr_bits {
    uint16 byte : 8;
    uint16 rsv0 : 8;
    uint16 rsv1 : 16;
};

union usart_dr {
    struct usart_dr_bits bits;
    uint32 all;
};

/*
 * 标准USART模式下(包括SPI模式)：
 * 波特率 = f_ck / (8 * (2 - OVER8) * USARTDIV)
 * OVER8 = 0时，USARTDIV = mantissa + fraction / 16
 * OVER8 = 1时，USARTDIV = mantissa + fraction / 8
 *
 * Smartcard, LIN, IrDA模式下：
 * 波特率 = f_ck / (16 * USARTDIV)
 */
struct usart_brr_bits {
    // DIV的小数部分
    uint16 fraction : 4;
    // DIV的整数部分
    uint16 mantissa : 12;
    uint16 rsv : 16;
};

union usart_brr {
    struct usart_brr_bits bits;
    uint32 all;
};

struct usart_cr1_bits {
    // SBK - Send BreaK
    uint16 SBK : 1;
    // RWU - Receive WakeUp, 由软件置位复位, 决定串口是否处于mute模式
    uint16 RWU : 1;
    // RE - 使能接收器
    uint16 RE : 1;
    // TE - 使能发送器
    uint16 TE : 1;
    // IDLEIE - 使能IDLE中断
    uint16 IDLEIE : 1;
    // RXNEIE - 使能接收中断
    uint16 RXNEIE : 1;
    // TCIE - 发送完成中断使能
    uint16 TCIE : 1;
    // TXEIE - TXE中断使能
    uint16 TXEIE : 1;
    // PEIE - 奇偶校验中断使能
    uint16 PEIE : 1;
    // PS - 奇偶校验方式选择, 0:Even, 1:Odd,奇数
    uint16 PS : 1;
    // PCE - 奇偶校验使能
    uint16 PCE : 1;
    // WAKE - 唤醒方式，0:Idle Line, 1: 地址唤醒
    uint16 WAKE : 1;
    // M - 帧字长，0:1起始位，8数据位，n停止位
    // 1: 1起始位， 9数据位，n停止位
    uint16 M : 1;
    // UE - USART使能
    uint16 UE : 1;
    uint16 rsv0 : 1;
    // OVER8 - 重采样方式，0：16次采样, 1:8次采样
    uint16 OVER8 : 1;
    uint16 rsv1 : 16;
};

union usart_cr1 {
    struct usart_cr1_bits bits;
    uint32 all;
};

#define USART_STOP_1bit 0x00
#define USART_STOP_0_5bit 0x01
#define USART_STOP_2bit 0x02
#define USART_STOP_1_5bit 0x03
struct usart_cr2_bits {
    // 串口组网的地址
    uint16 add : 4;
    uint16 rsv0 : 1;
    // LBDL - LIN break detection length, 0:10-bit, 1:11-bit
    uint16 LBDL : 1;
    // LBDIE - LIN break detection 中断使能
    uint16 LBDIE : 1;
    uint16 rsv1 : 1;
    // LBCL - Last Bit Clock Pulse, 在同步模式下，发送MSB时，CK引脚是否反应MSB
    uint16 LBCL : 1;
    // CPHA - Clock Phase, 同步模式下，决定什么时候获取数据
    // 0: 第一个时钟跳变沿是第一次获取数据的时钟沿
    // 1: 第二个时钟跳变沿是第一次获取数据的时钟沿
    uint16 CPHA : 1;
    // CPOL - Clock Polarity, 同步模式下，CK引脚的稳态电平，0:steady low, 1:steady high
    uint16 CPOL : 1;
    // CLKEN - 时钟使能
    uint16 CLKEN : 1;
    // STOP - 停止位长，2'b00:1bit, 2'01:0.5bit, 2'10:2bit, 2'11:1.5bit
    uint16 STOP : 2;
    // LINEN - LIN模式开启
    uint16 LINEN : 1;
    uint16 rsv2 : 1;
    uint16 rsv3 : 16;
};

union usart_cr2 {
    struct usart_cr2_bits bits;
    uint32 all;
};

struct usart_cr3_bits {
    // EIE - 错误中断使能
    uint16 EIE : 1;
    // IREN - 开启IrDA模式
    uint16 IREN : 1;
    // IRLP - IrDA低电压模式
    uint16 IRLP : 1;
    // HDSEL - 半双工模式选择
    uint16 HDSEL : 1;
    // NACK - Smartcard模式下，该位置1时开启奇偶校验，如果出错接收方会返回一个NACK信号
    uint16 NACK : 1;
    // SCEN - Smartcard模式开启
    uint16 SCEN : 1;
    // DMAR - 接收数据采用DMA方式
    uint16 DMAR : 1;
    // DMAT - 发送数据采用DMA方式
    uint16 DMAT : 1;
    // RTSE - RTS Enable,流控制
    uint16 RTSE : 1;
    // CTSE - CTS Enable,流控制
    uint16 CTSE : 1;
    // CTSIE - CTS中断使能,流控制
    uint16 CTSIE : 1;
    // ONEBIT - 位采样方式,0:三次采样,1:1次采样
    uint16 ONEBIT : 1;
    uint16 rsv0 : 4;
    uint16 rsv1 : 16;
};

union usart_cr3 {
    struct usart_cr3_bits bits;
    uint32 all;
};

struct usart_gtpr_bits {
    uint16 PSC : 8;
    uint16 GT : 8;
    uint16 rsv0 : 16;
};

union usart_gtpr {
    struct usart_gtpr_bits bits;
    uint32 all;
};

typedef struct usart_regs {
    volatile union usart_sr SR;         /* 串口状态寄存器, offset: 0x00 */
    volatile union usart_dr DR;         /* 串口数据寄存器, offset: 0x04 */
    volatile union usart_brr BRR;       /* 串口波特率寄存器, offset: 0x08 */
    volatile union usart_cr1 CR1;       /* 串口控制寄存器1, offset: 0x0C */
    volatile union usart_cr2 CR2;       /* 串口控制寄存器2, offset: 0x10 */
    volatile union usart_cr3 CR3;       /* 串口控制寄存器3, offset: 0x14 */
    volatile union usart_gtpr GTPR;     /* 串口守护时间和分频寄存器, offset: 0x18 */
} usart_regs_t;


/* 串口寄存器地址映射 */
#define USART1_BASE 0x40011000
#define USART2_BASE 0x40004400
#define USART3_BASE 0x40004800
#define UART4_BASE  0x40004C00
#define UART5_BASE  0x40005000
#define USART6_BASE 0x40011400
/* 串口寄存器指针访问 */
#define USART1 ((usart_regs_t *) USART1_BASE)
#define USART2 ((usart_regs_t *) USART2_BASE)
#define USART3 ((usart_regs_t *) USART3_BASE)
#define UART4  ((usart_regs_t *) UART4_BASE)
#define UART5  ((usart_regs_t *) UART5_BASE)
#define USART6 ((usart_regs_t *) USART6_BASE)

void uart_init(usart_regs_t *uart, uint32 baudrate);
void uart_send_byte(usart_regs_t *uart, uint8 value);
void uart_send_bytes(usart_regs_t *uart, const uint8 *buf, uint32 len);
void uart_send_str(usart_regs_t *uart, const uint8 *str);

