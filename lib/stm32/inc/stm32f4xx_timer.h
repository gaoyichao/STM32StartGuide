/***********************************************************
*
* stm32f4xx_timer - 计时器
*
************************************** 高乙超.2017.0618 ***/
#pragma once

#include <types.h>

/*
* TIM控制寄存器1 TIMx_CR1
* 偏移地址: 0x00
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
#define TIM_COUNT_DIR_UP        0
#define TIM_COUNT_DIR_DOWN      1
#define TIM_COUNT_DIR_CENTER1   2
#define TIM_COUNT_DIR_CENTER2   4
#define TIM_COUNT_DIR_CENTER3   6

struct timer_cr1_bits {
    /* 使能计数器 */
    uint16 CEN : 1;
    /* 关闭更新事件UEV */
    uint16 UDIS : 1;
    /* 更新事件UEV的请求源 */
    uint16 URS : 1;
    /* One Pulse Mode,计数器在下次UEV发生时停止计数,清除CEN */
    uint16 OPM : 1;
    /* DIR计数方向, 综合了DIR和CMS两个位段 */
    uint16 DIR : 3;
    /* 自动重装载使能,1:TIMx_ARR寄存器有缓存 */
    uint16 ARPE : 1;
    /* Clock Division, dead-time相关 */
    uint16 CKD : 2;
    uint16 rsv : 6;
};
union timer_cr1 {
    struct timer_cr1_bits bits;
    uint16 all;
};
/*
* TIM控制寄存器2 TIMx_CR2
* 偏移地址: 0x04
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_cr2_bits {
    /* Capture/Compare Preloaded Control */
    uint16 CCPC : 1;
    uint16 rsv0 : 1;
    /* Capture/Compare Update Selection */
    uint16 CCUS : 1;
    /* Capture/Compare DMA Selection */
    uint16 CCDS : 1;
    /* Master Mode Selection */
    uint16 MMS : 3;
    /* TI1的输入选择 */
    uint16 TI1S : 1;
    /* 通道1闲时(when MOE=0)输出,合并了OISx和OISxN位 */
    uint16 OIS1 : 2;
    /* 通道2闲时(when MOE=0)输出 */
    uint16 OIS2 : 2;
    /* 通道3闲时(when MOE=0)输出 */
    uint16 OIS3 : 2;
    /* 通道4闲时(when MOE=0)输出 */
    uint16 OIS4 : 2;
};
union timer_cr2 {
    struct timer_cr2_bits bits;
    uint16 all;
};
/*
* TIM从模式控制寄存器 TIMx_SMCR
* 偏移地址: 0x08
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_smcr_bits {
    uint16 SMS : 3;
    uint16 rsv0 : 1;
    uint16 TS : 3;
    uint16 MSM : 1;
    uint16 ETF : 4;
    uint16 ETPS : 2;
    uint16 ECE : 1;
    uint16 ETP : 1;
};
union timer_smcr {
    struct timer_smcr_bits bits;
    uint16 all;
};
/*
* TIM DMA中断使能寄存器 TIMx_DIER
* 偏移地址: 0x0C
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_dier_bits {
    uint16 UIE : 1;
    uint16 CC1IE : 1;
    uint16 CC2IE : 1;
    uint16 CC3IE : 1;
    uint16 CC4IE : 1;
    uint16 COMIE : 1;
    uint16 TIE : 1;
    uint16 BIE : 1;
    uint16 UDE : 1;
    uint16 CC1DE : 1;
    uint16 CC2DE : 1;
    uint16 CC3DE : 1;
    uint16 CC4DE : 1;
    uint16 COMDE : 1;
    uint16 TDE : 1;
    uint16 rsv0 : 1;
};
union timer_dier {
    struct timer_dier_bits bits;
    uint16 all;
};
/*
* TIM状态寄存器 TIMx_SR
* 偏移地址: 0x10
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_sr_bits {
    uint16 UIF : 1;
    uint16 CC1IF : 1;
    uint16 CC2IF : 1;
    uint16 CC3IF : 1;
    uint16 CC4IF : 1;
    uint16 COMIF : 1;
    uint16 TIF : 1;
    uint16 BIF : 1;
    uint16 rsv0 : 1;
    uint16 CC1OF : 1;
    uint16 CC2OF : 1;
    uint16 CC3OF : 1;
    uint16 CC4OF : 1;
    uint16 rsv1 : 3;
};
union timer_sr {
    struct timer_sr_bits bits;
    uint16 all;
};
/*
* TIM事件生成寄存器 TIMx_EGR
* 偏移地址: 0x14
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_egr_bits {
    uint16 UG : 1;
    uint16 CC1G : 1;
    uint16 CC2G : 1;
    uint16 CC3G : 1;
    uint16 CC4G : 1;
    uint16 COMG : 1;
    uint16 TG : 1;
    uint16 BG : 1;
    uint16 rsv0 : 8;
};
union timer_egr {
    struct timer_egr_bits bits;
    uint16 all;
};
/*
* TIM捕获/比较模式寄存器 TIMx_CCMR
* 偏移地址: 0x18,0x1C
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
#define TIM_OCMode_Frozen   0   /* 输出对比寄存器CCR与计数寄存器CNT的对比关系不影响输出 */
#define TIM_OCMode_ACT      1   /* 当计数寄存器CNT与对比寄存器CCR相等时, OCxREF信号置高 */
#define TIM_OCMode_INACT    2   /* 置OCxREF低 */
#define TIM_OCMode_Toggle   3   /* 翻转OCxREF */
#define TIM_OCMode_FINACT   4   /* 强制OCxREF为低 */
#define TIM_OCMode_FACT     5   /* 强制OCxREF为高 */
#define TIM_OCMode_PWM1     6   /* 向上计数时,当CNT < CCR时 OCxREF = 1 否则OCxREF = 0, 向下计数时, 当CNT > CCR时 OCxREF = 0 否则OCxREF = 1 */
#define TIM_OCMode_PWM2     7   /* 输出电平逻辑与PWM1相反 */

#define TIM_Channel_Mode_Output 0   /* 输出模式 */
#define TIM_Channel_Mode_Input1 1   /* 输入模式1, ICx => TIx */
#define TIM_Channel_Mode_Input2 2   /* 输入模式2, ICx => TIy */
#define TIM_Channel_Mode_Input3 3   /* 输入模式3, ICx => TRC */

#define TIM_ICMode_PSC_0    0   /* 输入捕获0分频 */
#define TIM_ICMode_PSC_2    1   /* 输入捕获2分频 */
#define TIM_ICMode_PSC_4    2   /* 输入捕获4分频 */
#define TIM_ICMode_PSC_8    3   /* 输入捕获8分频 */

struct timer_oc_cfg {
    uint8 CCxS : 2;
    uint8 OCxFE : 1;
    uint8 OCxPE : 1;
    uint8 OCxM : 3;
    uint8 OCxCE : 1;
};
struct timer_ic_cfg {
    uint8 CCxS : 2;
    uint8 ICxPSC : 2;
    uint8 ICxF : 4;
};
union timer_chanel_mode {
    struct timer_oc_cfg oc;
    struct timer_ic_cfg ic;
    uint8 byte;
};
struct timer_ccmr_bytes {
    uint16 b13 : 8;
    uint16 b24 : 8;
};
struct timer_ccmr_oc_bits {
    /* 选择工作模式 */
    uint16 CC13S : 2;
    /* Output Comare Fast Enable */
    uint16 OC13FE : 1;
    /* OC Preload Enable */
    uint16 OC13PE : 1;
    /* OC Mode */
    uint16 OC13M : 3;
    /* OC Clear Enable */
    uint16 OC13CE : 1;
    /* 选择工作模式 */
    uint16 CC24S : 2;
    /* Output Comare Fast Enable */
    uint16 OC24FE : 1;
    /* OC Preload Enable */
    uint16 OC24PE : 1;
    /* OC Mode */
    uint16 OC24M : 3;
    /* OC Clear Enable */
    uint16 OC24CE : 1;
};
struct timer_ccmr_ic_bits {
    /* 选择工作模式 */
    uint16 CC13S : 2;
    uint16 IC13PSC : 2;
    uint16 IC13F : 4;

    uint16 CC24S : 2;
    uint16 IC24PSC : 2;
    uint16 IC24F : 4;
};
union timer_ccmr {
    struct timer_ccmr_oc_bits ocbits;
    struct timer_ccmr_ic_bits icbits;
    struct timer_ccmr_bytes bytes;
    uint16 all;
};
/*
* TIM捕获/比较使能寄存器 TIMx_CCER
* 偏移地址: 0x20
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_cen {
    uint8 CCxE : 1;
    uint8 CCxP : 1;
    uint8 CCxNE : 1;
    uint8 CCxNP : 1;
    uint8 rsv : 4;
};
union timer_chanel_en {
    struct timer_cen bits;
    uint8 all;
};
struct timer_ccer_bits {
    uint16 CC1E : 1;
    uint16 CC1P : 1;
    uint16 CC1NE : 1;
    uint16 CC1NP : 1;

    uint16 CC2E : 1;
    uint16 CC2P : 1;
    uint16 CC2NE : 1;
    uint16 CC2NP : 1;

    uint16 CC3E : 1;
    uint16 CC3P : 1;
    uint16 CC3NE : 1;
    uint16 CC3NP : 1;

    uint16 CC4E : 1;
    uint16 CC4P : 1;
    uint16 rsv3 : 1;
    uint16 CC4NP : 1;
};
union timer_ccer {
    struct timer_ccer_bits bits;
    uint16 all;
};
/*
* TIM中断和死区寄存器 TIMx_BDTR
* 偏移地址: 0x44
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_bdtr_bits {
    uint16 DTG : 8;
    uint16 LOCK : 2;
    uint16 OSSI : 1;
    uint16 OSSR : 1;
    uint16 BKE : 1;
    uint16 BKP : 1;
    uint16 AOE : 1;
    uint16 MOE : 1;
};
union timer_bdtr {
    struct timer_bdtr_bits bits;
    uint16 all;
};
/*
* TIM DMA控制寄存器 TIMx_DCR
* 偏移地址: 0x48
* 复位值: 0x0000
* 访问: 无等待状态, half-word访问
*/
struct timer_dcr_bits {
    uint16 DBA : 5;
    uint16 rsv0 : 3;
    uint16 DBL : 5;
    uint16 rsv1 : 3;
};
union timer_dcr {
    struct timer_dcr_bits bits;
    uint16 all;
};

typedef struct timer_regs {
    volatile union timer_cr1 CR1;       /* TIM控制寄存器1, offset: 0x00 */
    uint16 rsv0;
    volatile union timer_cr2 CR2;       /* TIM控制寄存器2, offset: 0x04 */
    uint16 rsv1;
    volatile union timer_smcr SMCR;     /* TIM从模式控制寄存器, offset: 0x08 */
    uint16 rsv2;
    volatile union timer_dier DIER;     /* TIM DMA/中断使能寄存器, offset: 0x0C */
    uint16 rsv3;
    volatile union timer_sr SR;         /* TIM状态寄存器, offset: 0x10 */
    uint16 rsv4;
    volatile union timer_egr EGR;       /* TIM事件生成寄存器, offset: 0x14 */
    uint16 rsv5;
    volatile union timer_ccmr CCMR1;    /* TIM捕获/比较模式寄存器1, offset: 0x18 */
    uint16 rsv6;
    volatile union timer_ccmr CCMR2;    /* TIM捕获/比较模式寄存器2, offset: 0x1C */
    uint16 rsv7;
    volatile union timer_ccer CCER;     /* TIM捕获/比较使能寄存器, offset: 0x20 */
    uint16 rsv8;
    volatile uint32 CNT;                /* TIM计数寄存器, offset: 0x24 */
    volatile uint16 PSC;                /* TIM预分频寄存器, offset: 0x28 */
    uint16 rsv9;
    volatile uint32 ARR;                /* TIM自动重载寄存器, offset: 0x2C */
    volatile uint16 RCR;                /* TIM repetition counter register, offset: 0x30 */
    uint16 rsv10;
    volatile uint32 CCR1;               /* TIM捕获/对比寄存器1, offset: 0x34 */
    volatile uint32 CCR2;               /* TIM通道2, offset: 0x38 */
    volatile uint32 CCR3;               /* TIM通道3, offset: 0x3C */
    volatile uint32 CCR4;               /* TIM通道4, offset: 0x40 */
    volatile union timer_bdtr BDTR;     /* TIM中断和死区寄存器, offset: 0x44 */
    uint16 rsv11;
    volatile union timer_dcr DCR;       /* TIM DMA控制寄存器, offset: 0x48 */
    uint16 rsv12;
    volatile uint16 DMAR;               /* TIM DMA address for full transfer, offset: 0x4C */
    uint16 rsv13;
    volatile uint16 OR;                 /*!< TIM option register, offset: 0x50 */
    uint16 rsv14;
} timer_regs_t;

/* 串口寄存器地址映射 */
#define TIM1_BASE 0x40010000
#define TIM8_BASE 0x40010400
// APB1
#define TIM2_BASE 0x40000000
#define TIM3_BASE 0x40000400
#define TIM4_BASE 0x40000800
#define TIM5_BASE 0x40000C00
#define TIM6_BASE 0x40001000
#define TIM7_BASE 0x40001400
#define TIM12_BASE 0x40001800
#define TIM13_BASE 0x40001C00
#define TIM14_BASE 0x40002000
/* 串口寄存器指针访问 */
#define TIM1 ((timer_regs_t *) TIM1_BASE)
#define TIM8 ((timer_regs_t *) TIM8_BASE)

#define TIM2 ((timer_regs_t *) TIM2_BASE)
#define TIM3 ((timer_regs_t *) TIM3_BASE)
#define TIM4 ((timer_regs_t *) TIM4_BASE)
#define TIM5 ((timer_regs_t *) TIM5_BASE)
#define TIM6 ((timer_regs_t *) TIM6_BASE)
#define TIM7 ((timer_regs_t *) TIM7_BASE)
#define TIM12 ((timer_regs_t *) TIM12_BASE)
#define TIM13 ((timer_regs_t *) TIM13_BASE)
#define TIM14 ((timer_regs_t *) TIM14_BASE)

/***********************************************************************/

/*
* timer_set_ccmr - 设置计时器通道,工作模式
*
* @tim: 计时器
* @c: 通道
* @cfg: 配置
*/
void timer_set_ccmr(timer_regs_t * tim, uint8 c, union timer_chanel_mode cfg);
/*
* timer_set_ccer - 设置计时器通道,使能和工作电平
*
* @tim: 计时器
* @c: 通道
* @cen: 配置
*/
void timer_set_ccer(timer_regs_t * tim, uint8 c, union timer_chanel_en cen);


