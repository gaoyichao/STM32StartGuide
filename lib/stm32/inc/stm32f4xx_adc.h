/***********************************************************
 *
 * stm32f4xx_adc - 模拟/数字转换
 *
 ************************************** 高乙超.2017.0618 ***/
#pragma once

#include <types.h>

/*
 * ADC状态寄存器 ADCx_SR
 * 偏移地址: 0x00
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct adc_sr_bits {
    /* Analog WatchDog flag */
    uint32 AWD : 1;
    /* regular channel End Of Conversion */
    uint32 EOC : 1;
    /* inJected channel End of Conversion */
    uint32 JEOC : 1;
    /* inJected channel Start flag */
    uint32 JSTART : 1;
    /* regular channel Start flag */
    uint32 START : 1;
    /* Overrun */
    uint32 OVR : 1;
    uint32 rsv : 26;
};
union adc_sr {
    struct adc_sr_bits bits;
    uint32 all;
};
/*
 * ADC控制寄存器1 ADCx_CR1
 * 偏移地址: 0x04
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
#define ADC_RES_12Bits 0
#define ADC_RES_10Bits 1
#define ADC_RES_8Bits 2
#define ADC_RES_6Bits 3
struct adc_cr1_bits {
    /* Analog WatchDog CHannel select bits */
    uint32 AWDCH : 5;
    /* EOC中断使能 */
    uint32 EOCIE : 1;
    /* Analog WatchDog中断使能 */
    uint32 AWDIE : 1;
    /* JEOC中断使能 */
    uint32 JEOCIE : 1;
    /* 使能扫描模式 */
    uint32 SCAN : 1;
    /* 0:使能所有通道的AWD, 1:使能AWDCH指定通道的AWD */
    uint32 AWDSGL : 1;
    /* 使能Automatic inJected group conversion */
    uint32 JAUTO : 1;
    /* Discontinue mode on regular channels enable */
    uint32 DISCEN : 1;
    /* Discontinue mode on injected channels enable */
    uint32 JDISCEN : 1;
    /* Discontinue mode channel count */
    uint32 DISCNUM : 3;
    uint32 rsv0 : 6;
    /* 使能JAWD */
    uint32 JAWDEN : 1;
    /* 使能AWD */
    uint32 AWDEN : 1;
    /* 分辨率 */
    uint32 RES : 2;
    /* Overrun中断使能 */
    uint32 OVRIE : 1;
    uint32 rsv1 : 5;
};
union adc_cr1 {
    struct adc_cr1_bits bits;
    uint32 all;
};
/*
 * ADC控制寄存器2 ADCx_CR2
 * 偏移地址: 0x08
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
/* TODO: #define EXTSEL */
#define ADC_ExtTrigger_Dis             0
#define ADC_ExtTrigger_Rising          1
#define ADC_ExtTrigger_Failing         2
#define ADC_ExtTrigger_RisingFailing   3

#define ADC_Align_Right 0
#define ADC_Align_Left 1

struct adc_cr2_bits {
    /* 开启AD转换 */
    uint32 ADON : 1;
    /* 连续转换模式开启 */
    uint32 CONT : 1;
    uint32 rsv0 : 6;
    /* 开启DMA模式 */
    uint32 DMA : 1;
    /* 1: 当DMA=1时只要转换结束就产生一个DMA请求 */
    uint32 DDS : 1;
    /* EOC selection */
    uint32 EOCS : 1;
    /* 1:左对齐; 0:右对齐 */
    uint32 ALIGN : 1;
    uint32 rsv1 : 4;
    /* injected group的外部信号选择 */
    uint32 JEXTSEL : 4;
    /* injected group的外部触发方式 */
    uint32 JEXTEN : 2;
    /* injected channels开始转换,软件触发硬件复位 */
    uint32 JSWSTART : 1;
    uint32 rsv2 : 1;
    /* regular group的外部信号选择 */
    uint32 EXTSEL : 4;
    /* regular group的外部触发方式 */
    uint32 EXTEN : 2;
    /* regular channels开始转换,软件触发硬件复位 */
    uint32 SWSTART : 1;
    uint32 rsv3 : 1;
};
union adc_cr2 {
    struct adc_cr2_bits bits;
    uint32 all;
};
/*
 * ADC采样时间寄存器1 ADCx_SMPR1
 * 偏移地址: 0x0C
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
#define ADC_Sample_Time_3Cycles     0
#define ADC_Sample_Time_15Cycles    1
#define ADC_Sample_Time_28Cycles    2
#define ADC_Sample_Time_56Cycles    3
#define ADC_Sample_Time_84Cycles    4
#define ADC_Sample_Time_112Cycles   5
#define ADC_Sample_Time_144Cycles   6
#define ADC_Sample_Time_480Cycles   7
struct adc_smpr_bits {
    uint32 SMP0 : 3;
    uint32 SMP1 : 3;
    uint32 SMP2 : 3;
    uint32 SMP3 : 3;
    uint32 SMP4 : 3;
    uint32 SMP5 : 3;
    uint32 SMP6 : 3;
    uint32 SMP7 : 3;
    uint32 SMP8 : 3;
    uint32 SMP9 : 3;
    uint32 rsv0 : 2;
};
union adc_smpr {
    struct adc_smpr_bits bits;
    uint32 all;
};
/*
 * ADC regular sequence寄存器1 ADCx_SQR1
 * 偏移地址: 0x2C
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
#define ADC_SQR_LOffset 1
struct adc_sqr1_bits {
    uint32 SQ13 : 5;
    uint32 SQ14 : 5;
    uint32 SQ15 : 5;
    uint32 SQ16 : 5;
    uint32 L : 4;
    uint32 rsv0 : 8;
};
union adc_sqr1 {
    struct adc_sqr1_bits bits;
    uint32 all;
};
struct adc_sqrt23_bits {
    uint32 SQ1 : 5;
    uint32 SQ2 : 5;
    uint32 SQ3 : 5;
    uint32 SQ4 : 5;
    uint32 SQ5 : 5;
    uint32 SQ6 : 5;
    uint32 rsv0 : 2;
};
union adc_sqrt23 {
    struct adc_sqrt23_bits bits;
    uint32 all;
};
/*
 * ADC injected sequence寄存器 ADCx_JSQR
 * 偏移地址: 0x38
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct adc_jsqr_bits {
    uint32 JSQ1 : 5;
    uint32 JSQ2 : 5;
    uint32 JSQ3 : 5;
    uint32 JSQ4 : 5;
    uint32 L : 2;
    uint32 rsv0 : 10;
};
union adc_jsqr {
    struct adc_jsqr_bits bits;
    uint32 all;
};

typedef struct adc_regs {
    volatile union adc_sr SR;       /* ADC状态寄存器, offset: 0x00 */
    volatile union adc_cr1 CR1;     /* ADC控制寄存器1, offset: 0x04 */
    volatile union adc_cr2 CR2;     /* ADC控制寄存器2, offset: 0x08 */
    volatile union adc_smpr SMPR1;  /* ADC采样时间寄存器1, offset: 0x0C */
    volatile union adc_smpr SMPR2;  /* ADC采样时间寄存器2, offset: 0x10 */
    volatile uint32 JOFR1;          /* ADC injected channel数据偏移寄存器1(12位), offset: 0x14 */
    volatile uint32 JOFR2;          /* ADC injected channel数据偏移寄存器2(12位), offset: 0x18 */
    volatile uint32 JOFR3;          /* ADC injected channel数据偏移寄存器3(12位), offset: 0x1C */
    volatile uint32 JOFR4;          /* ADC injected channel数据偏移寄存器4(12位), offset: 0x20 */
    volatile uint32 HTR;            /* ADC watchdog 上阈值寄存器(12位), offset: 0x24 */
    volatile uint32 LTR;            /* ADC watchdog 下阈值寄存器(12位), offset: 0x28 */
    volatile union adc_sqr1 SQR1;   /* ADC regular sequence register 1, offset: 0x2C */
    volatile union adc_sqrt23 SQR2; /* ADC regular sequence register 2, offset: 0x30 */
    volatile union adc_sqrt23 SQR3; /* ADC regular sequence register 3, offset: 0x34 */
    volatile union adc_jsqr JSQR;   /* ADC injected sequence register, offset: 0x38*/
    volatile uint32 JDR1;           /* ADC injected data register 1(16位), offset: 0x3C */
    volatile uint32 JDR2;           /* ADC injected data register 2(16位), offset: 0x40 */
    volatile uint32 JDR3;           /* ADC injected data register 3(16位), offset: 0x44 */
    volatile uint32 JDR4;           /* ADC injected data register 4(16位), offset: 0x48 */
    volatile uint32 DR;             /* ADC regular data register(16位), offset: 0x4C */
} adc_regs_t;

/* ADC寄存器地址映射 */
#define ADC1_BASE 0x40012000
#define ADC2_BASE 0x40012100
#define ADC3_BASE 0x40012200
/* ADC寄存器指针访问 */
#define ADC1 ((adc_regs_t *) ADC1_BASE)
#define ADC2 ((adc_regs_t *) ADC2_BASE)
#define ADC3 ((adc_regs_t *) ADC3_BASE)

/*
 * ADC通用状态寄存器 ADC_CSR
 * 偏移地址: ADC1_BASE + 0x300
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct adc_csr_bits {
    uint32 AWD1 : 1;
    uint32 EOC1 : 1;
    uint32 JEOC1 : 1;
    uint32 JSTRT1 : 1;
    uint32 STRT1 : 1;
    uint32 OVR1 : 1;
    uint32 rsv0 : 2;

    uint32 AWD2 : 1;
    uint32 EOC2 : 1;
    uint32 JEOC2 : 1;
    uint32 JSTRT2 : 1;
    uint32 STRT2 : 1;
    uint32 OVR2 : 1;
    uint32 rsv1 : 2;

    uint32 AWD3 : 1;
    uint32 EOC3 : 1;
    uint32 JEOC3 : 1;
    uint32 JSTRT3 : 1;
    uint32 STRT3 : 1;
    uint32 OVR3 : 1;
    uint32 rsv10 : 2;

};
union adc_csr {
    struct adc_csr_bits bits;
    uint32 all;
};
/*
 * ADC通用控制寄存器 ADC_CCR
 * 偏移地址: ADC1_BASE + 0x304
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
#define ADC_Mode_Independent                       0x00

#define ADC_DualMode_RegSimult_InjecSimult         0x01
#define ADC_DualMode_RegSimult_AlterTrig           0x02
#define ADC_DualMode_InjecSimult                   0x05
#define ADC_DualMode_RegSimult                     0x06
#define ADC_DualMode_Interl                        0x07
#define ADC_DualMode_AlterTrig                     0x09

#define ADC_TripleMode_RegSimult_InjecSimult       0x11
#define ADC_TripleMode_RegSimult_AlterTrig         0x12
#define ADC_TripleMode_InjecSimult                 0x15
#define ADC_TripleMode_RegSimult                   0x16
#define ADC_TripleMode_Interl                      0x17
#define ADC_TripleMode_AlterTrig                   0x19

#define ADC_SamplingDelay_5Cycles       0x00
#define ADC_SamplingDelay_6Cycles       0x01
#define ADC_SamplingDelay_7Cycles       0x02
#define ADC_SamplingDelay_8Cycles       0x03
#define ADC_SamplingDelay_9Cycles       0x04
#define ADC_SamplingDelay_10Cycles      0x05
#define ADC_SamplingDelay_11Cycles      0x06
#define ADC_SamplingDelay_12Cycles      0x07
#define ADC_SamplingDelay_13Cycles      0x08
#define ADC_SamplingDelay_14Cycles      0x09
#define ADC_SamplingDelay_15Cycles      0x0A
#define ADC_SamplingDelay_16Cycles      0x0B
#define ADC_SamplingDelay_17Cycles      0x0C
#define ADC_SamplingDelay_18Cycles      0x0D
#define ADC_SamplingDelay_19Cycles      0x0E
#define ADC_SamplingDelay_20Cycles      0x0F

#define ADC_Prescaler_Div2      0x0
#define ADC_Prescaler_Div4      0x1
#define ADC_Prescaler_Div6      0x2
#define ADC_Prescaler_Div8      0x3


struct adc_ccr_bits {
    uint32 MULTI : 5;
    uint32 rsv0 : 3;
    uint32 DELAY : 4;
    uint32 rsv1 : 1;
    uint32 DDS : 1;
    uint32 DMA : 2;
    uint32 ADCPRE : 1;
    uint32 rsv2 : 4;
    uint32 VBATE : 1;
    uint32 TSVREFE : 1;
    uint32 rsv3 : 8;
};
union adc_ccr {
    struct adc_ccr_bits bits;
    uint32 all;
};

struct adc_cdr_bits {
    uint32 data1 : 16;
    uint32 data2 : 16;
};
union adc_cdr {
    struct adc_cdr_bits bits;
    uint32 all;
};

typedef struct adc_com_regs {
    volatile union adc_csr CSR;    /* ADC通用状态寄存器, offset: ADC1_BASE + 0x300 */
    volatile union adc_ccr CCR;    /* ADC通用控制寄存器, offset: ADC1_BASE + 0x304 */
    volatile union adc_cdr CDR;    /* ADC通用regular数据寄存器for dual AND triple modes, offset: ADC1_BASE + 0x308 */
} adc_com_regs_t;

/* ADC通用寄存器地址映射 */
#define ADC_COM_BASE (ADC1_BASE + 0x300)
/* ADC通用寄存器指针访问 */
#define ADC_COM ((adc_com_regs_t *) ADC_COM_BASE)




