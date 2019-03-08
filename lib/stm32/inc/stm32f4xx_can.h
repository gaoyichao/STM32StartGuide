/***********************************************************
 *
 * stm32f4xx_can - CAN总线
 *
 ************************************** 高乙超.2019.0305 ***/
#ifndef STM32F4XX_CAN_H
#define STM32F4XX_CAN_H

#include <types.h>

struct can_mcr_bits {
    // 写1进入初始化状态, 写0进入Normal状态
    uint32 INRQ : 1;
    // 写1进入Sleep状态
    uint32 SLEEP : 1;
    // 发送邮箱优先级, 1:根据请求顺序, 0:根据消息ID
    uint32 TXFP : 1;
    // 接收队列满动作, 1:抛弃新数据，0:覆盖旧数据
    uint32 RFLM : 1;
	// 是否关闭出错重发送
    uint32 NART : 1;
    // 是否开启自动唤醒
    // 1: 检测到总线上数据后自动退出Sleep状态
    // 0: 必须由软件写SLEEP位退出Sleep状态
    uint32 AWUM : 1;
    // Automatic Bus Off Management
    uint32 ABOM : 1;
    // Time Triggered Communication Mode
    uint32 TTCM : 1;
    
    uint32 r8_14 : 7;
    // 复位bxCAN控制器
    uint32 RESET : 1;
    // DeBug Freeze
    uint32 DBF : 1;
    
    uint32 r17_31 : 15;
};
union can_mcr {
    struct can_mcr_bits bits;
    uint32 all;
};

struct can_msr_bits {
    // initialization acknowledge
    uint32 INAK : 1;
    // sleep acknowledge
    uint32 SLAK : 1;
    // error interrupt
    uint32 ERRI : 1;
    // wakeup interrupt
    uint32 WKUI : 1;
    // sleep aknowledge interrupt
    uint32 SLAKI : 1;
    
    uint32 r5_7 : 3;
    // transmit mode
    uint32 TXM : 1;
    // receive mode
    uint32 RXM : 1;
    // last sample point
    uint32 SAMP : 1;
    // can rx signal
    uint32 RX : 1;
    
    uint32 r12_31 : 20;
};

union can_msr {
    struct can_msr_bits bits;
    uint32 all;
};

struct can_tsr_bits {
    // ReQuest ComPlete Mailbox0
    uint32 RQCP0 : 1;
    // 上次尝试发送是否成功
    uint32 TXOK0 : 1;
    // 总裁失败
    uint32 ALST0 : 1;
    // 因为错误导致发送失败
    uint32 TERR0 : 1;
    
    uint32 r4_6 : 3;
    // 软件撤销发送
    uint32 ABRQ0 : 1;
    // ReQuest ComPlete Mailbox0
    uint32 RQCP1 : 1;
    // 上次尝试发送是否成功
    uint32 TXOK1 : 1;
    // 总裁失败
    uint32 ALST1 : 1;
    // 因为错误导致发送失败
    uint32 TERR1 : 1;
    
    uint32 r12_14 : 3;
    // 软件撤销发送
    uint32 ABRQ1 : 1;
    // ReQuest ComPlete Mailbox0
    uint32 RQCP2 : 1;
    // 上次尝试发送是否成功
    uint32 TXOK2 : 1;
    // 总裁失败
    uint32 ALST2 : 1;
    // 因为错误导致发送失败
    uint32 TERR2 : 1;
    
    uint32 r20_22 : 3;
    // 软件撤销发送
    uint32 ABRQ2 : 1;
    // Mailbox code
    uint32 CODE : 2;
    // Tx Mailbox 0 Empty
    uint32 TME0 : 1;
    // 邮箱1空
    uint32 TME1 : 1;
    // 邮箱2空
    uint32 TME2 : 1;
    // 邮箱0具有最低优先级
    uint32 LOW0 : 1;
    // 邮箱1具有最低优先级
    uint32 LOW1 : 1;
    // 邮箱2具有最低优先级    
    uint32 LOW2 : 1;
};
union can_tsr {
    struct can_tsr_bits bits;
    uint32 all;
};

struct can_rcr_bits {
    // 接收队列中的消息数量
    uint32 FMP : 2;
    
    uint32 r2 : 1;
    // 队列满
    uint32 FULL : 1;
    // 队列溢出
    uint32 FOVR : 1;
    // 释放FIFO Output, 必须在释放FIFO Output后, 才能获得下一帧
    uint32 RFOM : 1;
    
    uint32 r6_31 : 26;
};
union can_rcr {
    struct can_rcr_bits bits;
    uint32 all;
};

struct can_ier_bits {
    // 发送邮箱空中断
    uint32 TMEIE : 1;
    // FIFO 0 pending中断
    uint32 FMPIE0 : 1;
    // FIFO 0满中断
    uint32 FFIE0 : 1;
    // FIFO 0过载中断
    uint32 FOVIE0 : 1;
    // FIFO 1 pending中断
    uint32 FMPIE1 : 1;
    // FIFO 1满中断
    uint32 FFIE1 : 1;
    // FIFO 1过载中断
    uint32 FOVIE1 : 1;
    
    uint32 r7 : 1;
    // Error Warning中断
    uint32 EWGIE : 1;
    // Error Passive中断
    uint32 EPVIE : 1;
    // Bus-Off中断
    uint32 BOFIE : 1;
    // Last Error Code中断
    uint32 LECIE : 1;
    
    uint32 r12_14 : 3;
    // Error中断
    uint32 ERRIE : 1;
    // 唤醒中断
    uint32 WKUIE : 1;
    // Sleep中断
    uint32 SLKIE : 1;
    
    uint32 r18_31 : 14;
};
union can_ier {
    struct can_ier_bits bits;
    uint32 all;
};

#define CAN_ESR_LEC_NoError 0
#define CAN_ESR_LEC_StuffError 1
#define CAN_ESR_LEC_FormError 2
#define CAN_ESR_LEC_AckError 3
#define CAN_ESR_LEC_BitRecessiveError 4
#define CAN_ESR_LEC_BitDominantError 5
#define CAN_ESR_LEC_CRCError 6
#define CAN_ESR_LEC_SoftwareError 7

struct can_esr_bits {
    // Error Warning
    uint32 EWGF : 1;
    // Error passive
    uint32 EPVF : 1;
    // Bus Off
    uint32 BOFF : 1;
    
    uint32 r3 : 1;
    // 最近一次错误号
    uint32 LEC : 3;
    
    uint32 r7_15 : 9;
    // 9位发送错误计数器的低位
    uint32 TEC : 8;
    // 接收错误计数器
    uint32 REC : 8;
};
union can_esr {
    struct can_esr_bits bits;
    uint32 all;
};

struct can_btr_bits {
    // 波特率预分频, t_q = (BRP[9:0] + 1) × t_{PCLK}
    uint32 BRP : 10;
    
    uint32 r10_15 : 6;
    // Time Segment 1, t_{BS1} = t_q × (TS1[3:0] + 1)
    uint32 TS1 : 4;
    // Time Segment 2, t_{BS2} = t_q × (TS2[2:0] + 1)
    uint32 TS2 : 3;
    
    uint32 r23 : 1;
    // 同步跳转宽度
    uint32 SJW : 2;
    
    uint32 r26_29 : 4;
    // 回环模式
    uint32 LBKM : 1;
    // 沉默模式
    uint32 SILM : 1;
};

union can_btr {
    struct can_btr_bits bits;
    uint32 all;
};

struct can_tsir_bits {
    // 请求发送
    uint32 TXRQ : 1;
    // 远程帧标识
    uint32 RTR : 1;
    // 扩展帧标识
    uint32 IDE : 1;
    // 扩展帧低18位
    uint32 r : 18;
    // 标准帧,扩展帧高11位
    uint32 STID : 11;
};
// 扩展帧ID
struct can_teir_bits {
    // 请求发送
    uint32 TXRQ : 1;
    // 远程帧标识
    uint32 RTR : 1;
    // 扩展帧标识
    uint32 IDE : 1;
    // 扩展帧低18位
    uint32 EXID : 29;
};

union can_trir {
    struct can_tsir_bits sbits;
    struct can_teir_bits ebits;
    uint32 all;
};

struct can_tdtr_bits {
    // 数据长度
    uint32 DLC : 4;
    
    uint32 r4_7 : 4;
    // 是否发送时间戳
    uint32 TGT : 1;
    
    uint32 r9_15 : 7;
    // SOF时间戳
    uint32 TIME : 16;
};
struct can_rdtr_bits {
    uint32 DLC : 4;
    uint32 r4_7 : 4;
    // 过滤器索引
    uint32 FMI : 8;
    uint32 TIME : 16;
};
union can_trdtr {
    struct can_tdtr_bits tbits;
    struct can_rdtr_bits rbits;
    uint32 all;
};

struct can_mailbox {
    volatile union can_trir TIR;   /* 邮箱ID寄存器, offset: 0x180 */
    volatile union can_trdtr TDTR; /* 邮箱数据长度和时间戳寄存器, offset: 0x184 */
    volatile uint32 TDLR;          /* 邮箱低32位数据寄存器, offset: 0x188 */
    volatile uint32 TDHR;          /* 邮箱高32位数据寄存器, offset: 0x18C */
};

struct can_fmr_bits {
    // 过滤器初始化模式, 0:开启过滤模式
    uint32 FINIT : 1;
    
    uint32 r1_7 : 7;
    // CAN2可用的过滤器起始索引
    uint32 CAN2SB : 6;
    
    uint32 r14_31 : 18;
};
union can_fmr {
    struct can_fmr_bits bits;
    uint32 all;
};

struct can_fidx_bits {
    uint32 F0 : 1;
    uint32 F1 : 1;
    uint32 F2 : 1;
    uint32 F3 : 1;
    uint32 F5 : 1;
    uint32 F6 : 1;
    uint32 F7 : 1;
    uint32 F8 : 1;
    uint32 F9 : 1;
    uint32 F10 : 1;
    uint32 F11 : 1;
    uint32 F12 : 1;
    uint32 F13 : 1;
    uint32 F14 : 1;
    uint32 F15 : 1;
    uint32 F16 : 1;
    uint32 F17 : 1;
    uint32 F18 : 1;
    uint32 F19 : 1;
    uint32 F20 : 1;
    uint32 F21 : 1;
    uint32 F22 : 1;
    uint32 F23 : 1;
    uint32 F24 : 1;
    uint32 F25 : 1;
    uint32 F26 : 1;
    uint32 F27 : 1;
    uint32 r28_31 : 4;
};

union can_fidx {
    struct can_fidx_bits bits;
    uint32 all;
};

struct can_filter {
    volatile uint32 FR0;
    volatile uint32 FR1;
};

typedef struct can_regs {
    volatile union can_mcr MCR;     /* 主控制寄存器, offset: 0x00 */
    volatile union can_msr MSR;     /* 主状态寄存器, offset: 0x04 */
    volatile union can_tsr TSR;     /* 发送状态寄存器, offset: 0x08 */
    volatile union can_rcr RF0R;    /* 接收FIFO 0状态寄存器, offset: 0x0C */
    volatile union can_rcr RF1R;    /* 接收FIFO 0状态寄存器, offset: 0x10 */
    volatile union can_ier IER;     /* 中断使能寄存器, offset: 0x14 */
    volatile union can_esr ESR;     /* 错误状态寄存器, offset: 0x18 */
    volatile union can_btr BTR;     /* 位时序寄存器, offset: 0x1C */
    uint32 rsv0[88];
    struct can_mailbox TxMailBox[3];/* 发送邮箱, offset: 0x180 */
    struct can_mailbox RxMailBox[2];/* 接收邮箱, offset: 0x1B0 */
    uint32 rsv1[12];
    volatile union can_fmr FMR;     /* 过滤器管理器寄存器, offset: 0x200 */
    volatile union can_fidx FM1R;   /* 过滤器模式管理, offset: 0x204, 0: Mask, 1:List */
    uint32 rsv2;
    volatile union can_fidx FS1R;   /* 过滤器尺寸管理, offset: 0x20C, 0: 2个16位, 1: 1个32位 */
    uint32 rsv3;
    volatile union can_fidx FFA1R;  /* 过滤器绑定FIFO, offset: 0x214 */
    uint32 rsv4;
    volatile union can_fidx FA1R;   /* 过滤器开关, offset: 0x21C, 1:激活 */
    uint32 rsv5[8];
    volatile struct can_filter Filters[28];
} can_regs_t;

/* CAN寄存器地址映射 */
#define CAN1_BASE 0x40006400
#define CAN2_BASE 0x40006800
/* CAN寄存器指针访问 */
#define CAN1 ((can_regs_t *) CAN1_BASE)
#define CAN2 ((can_regs_t *) CAN2_BASE)


#endif

