/***********************************************************
 *
 * stm32f4xx_rcc - 复位和时钟控制,Reset and Clock Control
 *
 ************************************** 高乙超.2016.1224 ***/
#ifndef STM32F4XX_RCC_H
#define STM32F4XX_RCC_H

#include <types.h>


/*
 * 锁相环配置寄存器 RCC_PLLCFGR
 * 偏移地址: 0x04
 * 复位值: 0x2400 3010
 * 访问: 无等待状态, word/half-word/byte访问
 *
 * 系统时钟计算方法：
 * f(VCO clock) = f(PLL clock input) * PLLN / PLLM
 * f(PLL general clock output) = f(VCO clock) / PLLP
 * f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
 */
#define RCC_PLLSRC_HSI 0
#define RCC_PLLSRC_HSE 1
struct rcc_pllcfgr_bits {
    uint32 pllm : 6;
    uint32 plln : 9;
    uint32 rsv0 : 1;
    uint32 pllp : 2;
    uint32 rsv1 : 4;
    uint32 pllsrc : 1;
    uint32 rsv2 : 1;
    uint32 pllq : 4;
    uint32 rsv3 : 4;
};

union rcc_pllcfgr {
    struct rcc_pllcfgr_bits bits;
    uint32 all;
};

/*
 * 时钟配置寄存器 RCC_CFGR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: 当访问发生在时钟切换时会有1或者两个等待周期, word/half-word/byte访问
 */
#define RCC_HPRE_DIV1       0x0 /* 1分频 */
#define RCC_HPRE_DIV2       0x8 /* 2分频 */
#define RCC_HPRE_DIV4       0x9 /* 4分频 */
#define RCC_HPRE_DIV8       0xa /* 8分频 */
#define RCC_HPRE_DIV16      0xb /* 16分频 */
#define RCC_HPRE_DIV64      0xc/* 64分频 */
#define RCC_HPRE_DIV128     0xd/* 128分频 */
#define RCC_HPRE_DIV256     0xe/* 256分频 */
#define RCC_HPRE_DIV512     0xf/* 512分频 */

#define RCC_PPRE_DIV1       0x0 /* 1分频 */
#define RCC_PPRE_DIV2       0x4 /* 2分频 */
#define RCC_PPRE_DIV4       0x5 /* 4分频 */
#define RCC_PPRE_DIV8       0x6 /* 8分频 */
#define RCC_PPRE_DIV16      0x7 /* 16分频 */

#define RCC_SW_HSI  ((uint32)0x00000000)    /* 内部高速时钟 */
#define RCC_SW_HSE  ((uint32)0x00000001)    /* 外部高速时钟 */
#define RCC_SW_PLL  ((uint32)0x00000002)   /* PLL */
struct rcc_cfgr_bits {
    // sw - 设置系统时钟源
    uint32 sw : 2;
    // sws - 只读,获取系统时钟源信息
    uint32 sws : 2;
    // hpre - AHB时钟分频器
    uint32 hpre : 4;
    uint32 rsv0 : 2;
    // ppre1 - 低速APB1分频器
    uint32 ppre1 : 3;
    // ppre2 - 高速APB2分频器
    uint32 ppre2 : 3;
    // rtcpre - RTC分频器
    uint32 rtcpre : 5;
    // mco - Microcontroller clock output 1
    uint32 mco1 : 2;
    // i2ssrc - I2S时钟源
    uint32 i2ssrc : 1;
    // mco1pre - mco1分频器
    uint32 mco1pre : 3;
    // mco2pre - mco2分频器
    uint32 mco2pre : 3;
    // mco2 - Microcontroller clock output 2
    uint32 mco2 : 2;
};

union rcc_cfgr {
    struct rcc_cfgr_bits bits;
    uint32 all;
};

/*
 * AHB1外设时钟使能寄存器 RCC_AHB1ENR
 * 偏移地址: 0x30
 * 复位值: 0x0010 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
struct rcc_ahb1enr_bits {
    uint32 gpioa : 1;
    uint32 gpiob : 1;
    uint32 gpioc : 1;
    uint32 gpiod : 1;
    uint32 gpioe : 1;
    uint32 gpiof : 1;
    uint32 gpiog : 1;
    uint32 gpioh : 1;
    uint32 gpioi : 1;
    uint32 r1 : 3;
    uint32 crc : 1;
    uint32 r2 : 5;
    uint32 bkpsram : 1;
    uint32 r3 : 1;
    uint32 ccmdataram : 1;
    uint32 dma1 : 1;
    uint32 dma2 : 1;
    uint32 r4 : 2;
    uint32 ethmac : 1;
    uint32 ethmac_tx : 1;
    uint32 ethmac_rx : 1;
    uint32 ethmac_ptp : 1;
    uint32 otg_hs : 1;
    uint32 otg_hs_ulpi : 1;
    uint32 r5 : 1;
};
union rcc_ahb1enr {
    struct rcc_ahb1enr_bits bits;
    uint32 all;
};
/*
 * AHB1外设时钟使能寄存器 RCC_AHB2ENR
 * 偏移地址: 0x34
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
struct rcc_ahb2enr_bits {
    uint32 dcmi : 1; /* Camera Interface */
    uint32 r0 : 3;
    uint32 cryp : 1; /* Cryptographic module */
    uint32 hash : 1; /* Hash */
    uint32 rng : 1; /* random number */
    uint32 otgfs : 1; /* usb otg fs */
    uint32 r1 : 24;
};
union rcc_ahb2enr {
    struct rcc_ahb2enr_bits bits;
    uint32 all;
};

struct rcc_apb1r_bits {
    uint32 tim2 : 1;
    uint32 tim3 : 1;
    uint32 tim4 : 1;
    uint32 tim5 : 1;
    uint32 tim6 : 1;
    uint32 tim7 : 1;
    uint32 tim12 : 1;
    uint32 tim13 : 1;

    uint32 tim14 : 1;
    uint32 rsv0 : 2;
    uint32 wwdg : 1;
    uint32 rsv1 : 2;
    uint32 spi2 : 1;
    uint32 spi3 : 1;

    uint32 rsv2 : 1;
    uint32 usart2 : 1;
    uint32 usart3 : 1;
    uint32 uart4 : 1;
    uint32 uart5 : 1;
    uint32 i2c1 : 1;
    uint32 i2c2 : 1;
    uint32 i2c3 : 1;

    uint32 rsv3 : 1;
    uint32 can1 : 1;
    uint32 can2 : 1;
    uint32 rsv4 : 1;
    uint32 pwr : 1;
    uint32 dac : 1;
    uint32 rsv5 : 2;
};
union rcc_apb1r {
    struct rcc_apb1r_bits bits;
    uint32 all;
};
/*
 * AHB1外设时钟使能寄存器 RCC_APB2R
 * 偏移地址: 0x44
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
struct rcc_apb2r_bits {
    uint32 tim1 : 1;
    uint32 tim8 : 1;
    uint32 r0 : 2;
    uint32 usart1 : 1;
    uint32 usart6 : 1;
    uint32 r1 : 2;
    uint32 adc1 : 1;
    uint32 adc2 : 1;
    uint32 adc3 : 1;
    uint32 sdio : 1;
    uint32 spi1 : 1;
    uint32 r2 : 1;
    uint32 syscfg : 1;
    uint32 r3 : 1;
    uint32 tim9 : 1;
    uint32 tim10 : 1;
    uint32 tim11 : 1;
    uint32 r4 : 13;
};
union rcc_apb2r {
    struct rcc_apb2r_bits bits;
    uint32 all;
};


typedef struct rcc_regs {
    volatile uint32 CR;            /* 时钟控制寄存器, offset: 0x00 */
    volatile union rcc_pllcfgr PLLCFGR;       /* 锁相环配置寄存器, offset: 0x04 */
    volatile union rcc_cfgr CFGR;          /* 时钟配置寄存器, offset: 0x08 */
    volatile uint32 CIR;           /* 时钟中断寄存器, offset: 0x0C */
    volatile uint32 AHB1RSTR;      /* AHB1外设复位寄存器, offset: 0x10 */
    volatile uint32 AHB2RSTR;      /* AHB2外设复位寄存器, offset: 0x14 */
    volatile uint32 AHB3RSTR;      /* AHB3外设复位寄存器, offset: 0x18 */
    uint32 RESERVED0;               /* 保留, 0x1C */
    volatile union rcc_apb1r APB1RSTR;      /* APB1外设复位寄存器, offset: 0x20 */
    volatile union rcc_apb2r APB2RSTR;      /* APB2外设复位寄存器, offset: 0x24 */
    uint32  RESERVED1[2];           /* 保留, 0x28-0x2C */
    volatile union rcc_ahb1enr AHB1ENR;       /* AHB1外设时钟使能寄存器, offset: 0x30 */
    volatile union rcc_ahb2enr AHB2ENR;       /* AHB2外设时钟使能寄存器, offset: 0x34 */
    volatile uint32 AHB3ENR;       /* AHB3外设时钟使能寄存器, offset: 0x38 */
    uint32 RESERVED2;               /* 保留, 0x3C */
    volatile union rcc_apb1r APB1ENR;       /* APB1外设时钟使能寄存器, offset: 0x40 */
    volatile union rcc_apb2r APB2ENR;       /* APB2外设时钟使能寄存器, offset: 0x44 */
    uint32 RESERVED3[2];            /* 保留, 0x48-0x4C */
    volatile uint32 AHB1LPENR;     /* AHB1低电压模式下外设时钟使能寄存器, offset: 0x50 */
    volatile uint32 AHB2LPENR;     /* AHB2低电压模式下外设时钟使能寄存器, offset: 0x54 */
    volatile uint32 AHB3LPENR;     /* AHB3低电压模式下外设时钟使能寄存器, offset: 0x58 */
    uint32 RESERVED4;               /* 保留, 0x5C */
    volatile union rcc_apb1r APB1LPENR;     /* APB1低电压模式下外设时钟使能寄存器, offset: 0x60 */
    volatile union rcc_apb2r APB2LPENR;     /* APB2低电压模式下外设时钟使能寄存器, offset: 0x64 */
    uint32 RESERVED5[2];            /* 保留, 0x68-0x6C */
    volatile uint32 BDCR;          /* Backup domain控制寄存器, offset: 0x70 */
    volatile uint32 CSR;           /* 时钟控制和状态寄存器, offset: 0x74 */
    uint32 RESERVED6[2];            /* 保留, 0x78-0x7C */
    volatile uint32 SSCGR;         /* 扩频时钟发生器寄存器(听起来很高大上，有什么用暂时不知道，以后会详细解析) offset: 0x80 */
    volatile uint32 PLLI2SCFGR;    /* 锁相环PLLI2S配置寄存器, offset: 0x84 */
} rcc_regs_t;

/* RCC寄存器地址映射 */
#define RCC_BASE 0x40023800
/* RCC寄存器指针访问 */
#define RCC ((rcc_regs_t *) RCC_BASE)

/*
 * 时钟控制寄存器 RCC_CR
 * 偏移地址: 0x00
 * 复位值: 0x0000 XX83
 * 访问: 无等待状态, word/half-word/byte访问
 */
#define RCC_CR_RESET_VALUE  ((uint32)0x00000083)        /* 复位值           */
#define RCC_CR_HSION        ((uint32)0x00000001)        /* 内部高速时钟 使能 */
#define RCC_CR_HSIRDY       ((uint32)0x00000002)        /* 内部高速时钟 就绪 */
#define RCC_CR_HSITRIM      ((uint32)0x000000F8)        /* 内部高速时钟 调整 */
#define RCC_CR_HSICAL       ((uint32)0x0000FF00)        /* 内部高速时钟 校准 */
#define RCC_CR_HSEON        ((uint32)0x00010000)        /* 外部高速时钟 使能 */
#define RCC_CR_HSERDY       ((uint32)0x00020000)        /* 外部高速时钟 就绪 */
#define RCC_CR_HSEBYP       ((uint32)0x00040000)        /* 外部高速时钟 旁路 */
#define RCC_CR_CSSON        ((uint32)0x00080000)        /* 时钟安全系统 使能 */
#define RCC_CR_PLLON        ((uint32)0x01000000)        /* PLL         使能 */
#define RCC_CR_PLLRDY       ((uint32)0x02000000)        /* PLL         就绪 */
#define RCC_CR_PLLI2SON     ((uint32)0x04000000)        /* PLLI2S      就绪 */
#define RCC_CR_PLLI2SRDY    ((uint32)0x08000000)        /* PLLI2S      就绪 */

/*
 * 时钟中断寄存器 RCC_CIR
 * 偏移地址: 0x0C
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_CIR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_CIR_LSIRDYF         ((uint32)0x00000001)        /* LSI时钟就绪中断,LSIRDYIE=1时由硬件置1,软件写1到LSIRDYC位清除 */
#define RCC_CIR_LSERDYF         ((uint32)0x00000002)        /* LSE时钟就绪中断,LSERDYIE=1时由硬件置1,软件写1到LSERDYC位清除 */
#define RCC_CIR_HSIRDYF         ((uint32)0x00000004)        /* HSI时钟就绪中断,HSIRDYIE=1时由硬件置1,软件写1到HSIRDYC位清除 */
#define RCC_CIR_HSERDYF         ((uint32)0x00000008)        /* HSE时钟就绪中断,HSERDYIE=1时由硬件置1,软件写1到HSERDYC位清除 */
#define RCC_CIR_PLLRDYF         ((uint32)0x00000010)        /* PLL时钟就绪中断,PLLRDYIE=1时由硬件置1,软件写1到PLLRDYC位清除 */
#define RCC_CIR_PLLI2SRDYF      ((uint32)0x00000020)        /* PLLI2S时钟就绪中断,PLLRDYIE=1时由硬件置1,软件写1到PLLRDYC位清除 */
#define RCC_CIR_CSSF            ((uint32)0x00000080)        /* 时钟安全系统中断标志,HSE失效时硬件置1,软件写1到CSSC位清除 */
#define RCC_CIR_LSIRDYIE        ((uint32)0x00000100)        /* LSI就绪中断使能 */
#define RCC_CIR_LSERDYIE        ((uint32)0x00000200)        /* LSE就绪中断使能 */
#define RCC_CIR_HSIRDYIE        ((uint32)0x00000400)        /* HSI就绪中断使能 */
#define RCC_CIR_HSERDYIE        ((uint32)0x00000800)        /* HSE就绪中断使能 */
#define RCC_CIR_PLLRDYIE        ((uint32)0x00001000)        /* PLL就绪中断使能 */
#define RCC_CIR_PLLI2SRDYIE     ((uint32)0x00002000)        /* PLL就绪中断使能 */
#define RCC_CIR_LSIRDYC         ((uint32)0x00010000)        /* 清除LSI就绪中断 */
#define RCC_CIR_LSERDYC         ((uint32)0x00020000)        /* 清除LSE就绪中断 */
#define RCC_CIR_HSIRDYC         ((uint32)0x00040000)        /* 清除HSI就绪中断 */
#define RCC_CIR_HSERDYC         ((uint32)0x00080000)        /* 清除HSE就绪中断 */
#define RCC_CIR_PLLRDYC         ((uint32)0x00100000)        /* 清除PLL就绪中断 */
#define RCC_CIR_PLLI2SRDYC      ((uint32)0x00200000)        /* 清除PLL就绪中断 */
#define RCC_CIR_CSSC            ((uint32)0x00800000)        /* 清除时钟安全系统中断 */

#define RCC_CIE_ALLE            ((uint32)0x00003F00)        /* 打开所有中断 */
#define RCC_CIR_ALLC            ((uint32)0x00BF0000)        /* 清除所有中断标志 */
/*
 * AHB1外设复位寄存器 RCC_AHB1RSTR
 * 偏移地址: 0x10
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB1RSTR_GPIOA    ((uint32)0x00000001)
#define RCC_AHB1RSTR_GPIOB    ((uint32)0x00000002)
#define RCC_AHB1RSTR_GPIOC    ((uint32)0x00000004)
#define RCC_AHB1RSTR_GPIOD    ((uint32)0x00000008)
#define RCC_AHB1RSTR_GPIOE    ((uint32)0x00000010)
#define RCC_AHB1RSTR_GPIOF    ((uint32)0x00000020)
#define RCC_AHB1RSTR_GPIOG    ((uint32)0x00000040)
#define RCC_AHB1RSTR_GPIOH    ((uint32)0x00000080)
#define RCC_AHB1RSTR_GPIOI    ((uint32)0x00000100)
#define RCC_AHB1RSTR_CRC      ((uint32)0x00001000)
#define RCC_AHB1RSTR_DMA1     ((uint32)0x00200000)
#define RCC_AHB1RSTR_DMA2     ((uint32)0x00400000)
#define RCC_AHB1RSTR_ETHMAC   ((uint32)0x02000000)
#define RCC_AHB1RSTR_OTGHS    ((uint32)0x20000000)
/*
 * AHB2外设复位寄存器 RCC_AHB2RSTR
 * 偏移地址: 0x14
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB2RSTR_DCMI    ((uint32)0x00000001)
#define RCC_AHB2RSTR_CRYP    ((uint32)0x00000010)
#define RCC_AHB2RSTR_HASH    ((uint32)0x00000020)
#define RCC_AHB2RSTR_RNG     ((uint32)0x00000040)
#define RCC_AHB2RSTR_OTGFS   ((uint32)0x00000080)
/*
 * AHB3外设复位寄存器 RCC_AHB3RSTR
 * 偏移地址: 0x18
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB3RSTR_FSMC    ((uint32)0x00000001)
/*
 * APB1外设复位寄存器 RCC_APB1RSTR
 * 偏移地址: 0x20
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB1RSTR_TIM2    ((uint32)0x00000001)
#define RCC_APB1RSTR_TIM3    ((uint32)0x00000002)
#define RCC_APB1RSTR_TIM4    ((uint32)0x00000004)
#define RCC_APB1RSTR_TIM5    ((uint32)0x00000008)
#define RCC_APB1RSTR_TIM6    ((uint32)0x00000010)
#define RCC_APB1RSTR_TIM7    ((uint32)0x00000020)
#define RCC_APB1RSTR_TIM12   ((uint32)0x00000040)
#define RCC_APB1RSTR_TIM13   ((uint32)0x00000080)
#define RCC_APB1RSTR_TIM14   ((uint32)0x00000100)
#define RCC_APB1RSTR_WWDG    ((uint32)0x00000800)
#define RCC_APB1RSTR_SPI2    ((uint32)0x00004000)
#define RCC_APB1RSTR_SPI3    ((uint32)0x00008000)
#define RCC_APB1RSTR_UART2   ((uint32)0x00020000)
#define RCC_APB1RSTR_UART3   ((uint32)0x00040000)
#define RCC_APB1RSTR_UART4   ((uint32)0x00080000)
#define RCC_APB1RSTR_UART5   ((uint32)0x00100000)
#define RCC_APB1RSTR_I2C1    ((uint32)0x00200000)
#define RCC_APB1RSTR_I2C2    ((uint32)0x00400000)
#define RCC_APB1RSTR_I2C3    ((uint32)0x00800000)
#define RCC_APB1RSTR_CAN1    ((uint32)0x02000000)
#define RCC_APB1RSTR_CAN2    ((uint32)0x04000000)
#define RCC_APB1RSTR_PWR     ((uint32)0x10000000)   /* Power Interface */
#define RCC_APB1RSTR_DAC     ((uint32)0x20000000)
/*
 * APB2外设复位寄存器 RCC_APB2RSTR
 * 偏移地址: 0x24
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB2RSTR_TIM1    ((uint32)0x00000001)
#define RCC_APB2RSTR_TIM8    ((uint32)0x00000002)
#define RCC_APB2RSTR_USART1  ((uint32)0x00000010)
#define RCC_APB2RSTR_USART6  ((uint32)0x00000020)
#define RCC_APB2RSTR_ADC     ((uint32)0x00000100)
#define RCC_APB2RSTR_SDIO    ((uint32)0x00000800)
#define RCC_APB2RSTR_SPI1    ((uint32)0x00001000)
#define RCC_APB2RSTR_SYSCFG  ((uint32)0x00004000)
#define RCC_APB2RSTR_TIM9    ((uint32)0x00010000)
#define RCC_APB2RSTR_TIM10   ((uint32)0x00020000)
#define RCC_APB2RSTR_TIM11   ((uint32)0x00040000)

/*
 * AHB2外设时钟使能寄存器 RCC_AHB2ENR
 * 偏移地址: 0x34
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB2ENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2ENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2ENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2ENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2ENR_OTGFS      ((uint32)0x00000080)
/*
 * AHB3外设时钟使能寄存器 RCC_AHB3ENR
 * 偏移地址: 0x38
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB3ENR_FSMC       ((uint32)0x00000001)
/*
 * APB1外设时钟使能寄存器 RCC_APB1ENR
 * 偏移地址: 0x40
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB1ENR_TIM2       ((uint32)0x00000001)
#define RCC_APB1ENR_TIM3       ((uint32)0x00000002)
#define RCC_APB1ENR_TIM4       ((uint32)0x00000004)
#define RCC_APB1ENR_TIM5       ((uint32)0x00000008)
#define RCC_APB1ENR_TIM6       ((uint32)0x00000010)
#define RCC_APB1ENR_TIM7       ((uint32)0x00000020)
#define RCC_APB1ENR_TIM12      ((uint32)0x00000040)
#define RCC_APB1ENR_TIM13      ((uint32)0x00000080)
#define RCC_APB1ENR_TIM14      ((uint32)0x00000100)
#define RCC_APB1ENR_WWDG       ((uint32)0x00000800)
#define RCC_APB1ENR_SPI2       ((uint32)0x00004000)
#define RCC_APB1ENR_SPI3       ((uint32)0x00008000)
#define RCC_APB1ENR_USART2     ((uint32)0x00020000)
#define RCC_APB1ENR_USART3     ((uint32)0x00040000)
#define RCC_APB1ENR_UART4      ((uint32)0x00080000)
#define RCC_APB1ENR_UART5      ((uint32)0x00100000)
#define RCC_APB1ENR_I2C1       ((uint32)0x00200000)
#define RCC_APB1ENR_I2C2       ((uint32)0x00400000)
#define RCC_APB1ENR_I2C3       ((uint32)0x00800000)
#define RCC_APB1ENR_CAN1       ((uint32)0x02000000)
#define RCC_APB1ENR_CAN2       ((uint32)0x04000000)
#define RCC_APB1ENR_PWR        ((uint32)0x10000000)
#define RCC_APB1ENR_DAC        ((uint32)0x20000000)
/*
 * APB2外设时钟使能寄存器 RCC_APB2ENR
 * 偏移地址: 0x44
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB2ENR_TIM1       ((uint32)0x00000001)
#define RCC_APB2ENR_TIM8       ((uint32)0x00000002)
#define RCC_APB2ENR_UART1      ((uint32)0x00000010)
#define RCC_APB2ENR_UART6      ((uint32)0x00000020)
#define RCC_APB2ENR_ADC1       ((uint32)0x00000100)
#define RCC_APB2ENR_ADC2       ((uint32)0x00000200)
#define RCC_APB2ENR_ADC3       ((uint32)0x00000400)
#define RCC_APB2ENR_SDIO       ((uint32)0x00000800)
#define RCC_APB2ENR_SPI1       ((uint32)0x00001000)
#define RCC_APB2ENR_SYSCFG     ((uint32)0x00004000)
#define RCC_APB2ENR_TIM9       ((uint32)0x00010000)
#define RCC_APB2ENR_TIM10      ((uint32)0x00020000)
#define RCC_APB2ENR_TIM11      ((uint32)0x00040000)
/*
 * 低电压模式下AHB1外设时钟使能寄存器 RCC_AHB1LPENR
 * 偏移地址: 0x50
 * 复位值: 0x7E67 91FF
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB1LPENR_RESET_VALUE    ((uint32)0x7E6791FF)    /* 复位值 */

#define RCC_AHB1LPENR_GPIOA       ((uint32)0x00000001)
#define RCC_AHB1LPENR_GPIOB       ((uint32)0x00000002)
#define RCC_AHB1LPENR_GPIOC       ((uint32)0x00000004)
#define RCC_AHB1LPENR_GPIOD       ((uint32)0x00000008)
#define RCC_AHB1LPENR_GPIOE       ((uint32)0x00000010)
#define RCC_AHB1LPENR_GPIOF       ((uint32)0x00000020)
#define RCC_AHB1LPENR_GPIOG       ((uint32)0x00000040)
#define RCC_AHB1LPENR_GPIOH       ((uint32)0x00000080)
#define RCC_AHB1LPENR_GPIOI       ((uint32)0x00000100)
#define RCC_AHB1LPENR_CRC         ((uint32)0x00001000)
#define RCC_AHB1LPENR_FLITFLP     ((uint32)0x00008000)
#define RCC_AHB1LPENR_SRAM1       ((uint32)0x00010000)
#define RCC_AHB1LPENR_SRAM2       ((uint32)0x00020000)
#define RCC_AHB1LPENR_BKPSRAM     ((uint32)0x00040000)
#define RCC_AHB1LPENR_DMA1        ((uint32)0x00200000)
#define RCC_AHB1LPENR_DMA2        ((uint32)0x00400000)
#define RCC_AHB1LPENR_ETHMAC      ((uint32)0x02000000)
#define RCC_AHB1LPENR_ETHMACTX    ((uint32)0x04000000)
#define RCC_AHB1LPENR_ETHMACRX    ((uint32)0x08000000)
#define RCC_AHB1LPENR_ETHMACPTP   ((uint32)0x10000000)
#define RCC_AHB1LPENR_OTGHS       ((uint32)0x20000000)
#define RCC_AHB1LPENR_OTGHSULPI   ((uint32)0x40000000)
/*
 * 低电压模式下AHB2外设时钟使能寄存器 RCC_AHB2LPENR
 * 偏移地址: 0x54
 * 复位值: 0x0000 00F1
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2LPENR_RESET_VALUE    ((uint32)0x000000F1)    /* 复位值 */

#define RCC_AHB2LPENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2LPENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2LPENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2LPENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2LPENR_OTGFS      ((uint32)0x00000080)
/*
 * 低电压模式下AHB3外设时钟使能寄存器 RCC_AHB3LPENR
 * 偏移地址: 0x58
 * 复位值: 0x0000 0001
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3LPENR_RESET_VALUE    ((uint32)0x00000001)    /* 复位值 */

#define RCC_AHB3LPENR_FSMC       ((uint32)0x00000001)
/*
 * 低电压模式下APB1外设时钟使能寄存器 RCC_APB1LPENR
 * 偏移地址: 0x60
 * 复位值: 0x36FE C9FF
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1LPENR_RESET_VALUE    ((uint32)0x36FEC9FF)    /* 复位值 */

#define RCC_APB1LPENR_TIM2       ((uint32)0x00000001)
#define RCC_APB1LPENR_TIM3       ((uint32)0x00000002)
#define RCC_APB1LPENR_TIM4       ((uint32)0x00000004)
#define RCC_APB1LPENR_TIM5       ((uint32)0x00000008)
#define RCC_APB1LPENR_TIM6       ((uint32)0x00000010)
#define RCC_APB1LPENR_TIM7       ((uint32)0x00000020)
#define RCC_APB1LPENR_TIM12      ((uint32)0x00000040)
#define RCC_APB1LPENR_TIM13      ((uint32)0x00000080)
#define RCC_APB1LPENR_TIM14      ((uint32)0x00000100)
#define RCC_APB1LPENR_WWDG       ((uint32)0x00000800)
#define RCC_APB1LPENR_SPI2       ((uint32)0x00004000)
#define RCC_APB1LPENR_SPI3       ((uint32)0x00008000)
#define RCC_APB1LPENR_USART2     ((uint32)0x00020000)
#define RCC_APB1LPENR_USART3     ((uint32)0x00040000)
#define RCC_APB1LPENR_UART4      ((uint32)0x00080000)
#define RCC_APB1LPENR_UART5      ((uint32)0x00100000)
#define RCC_APB1LPENR_I2C1       ((uint32)0x00200000)
#define RCC_APB1LPENR_I2C2       ((uint32)0x00400000)
#define RCC_APB1LPENR_I2C3       ((uint32)0x00800000)
#define RCC_APB1LPENR_CAN1       ((uint32)0x02000000)
#define RCC_APB1LPENR_CAN2       ((uint32)0x04000000)
#define RCC_APB1LPENR_PWR        ((uint32)0x10000000)
#define RCC_APB1LPENR_DAC        ((uint32)0x20000000)
/*
 * 低电压模式下APB2外设时钟使能寄存器 RCC_APB2LPENR
 * 偏移地址: 0x64
 * 复位值: 0x0407 5F33
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2LPENR_RESET_VALUE    ((uint32)0x04075F33)    /* 复位值 */

#define RCC_APB2LPENR_TIM1       ((uint32)0x00000001)
#define RCC_APB2LPENR_TIM8       ((uint32)0x00000002)
#define RCC_APB2LPENR_UART1      ((uint32)0x00000010)
#define RCC_APB2LPENR_UART6      ((uint32)0x00000020)
#define RCC_APB2LPENR_ADC1       ((uint32)0x00000100)
#define RCC_APB2LPENR_ADC2       ((uint32)0x00000200)
#define RCC_APB2LPENR_ADC3       ((uint32)0x00000400)
#define RCC_APB2LPENR_SDIO       ((uint32)0x00000800)
#define RCC_APB2LPENR_SPI1       ((uint32)0x00001000)
#define RCC_APB2LPENR_SYSCFG     ((uint32)0x00004000)
#define RCC_APB2LPENR_TIM9       ((uint32)0x00010000)
#define RCC_APB2LPENR_TIM10      ((uint32)0x00020000)
#define RCC_APB2LPENR_TIM11      ((uint32)0x00040000)
/*
 * backup domain controller register RCC_BDCR
 * 偏移地址: 0x70
 * 复位值: 0x0000 0000, reset by reset domain reset
 * 访问: 有0到3个时钟的等待状态, word/half-word/byte访问
 *       添加等待状态以防止连续的访问该寄存器
 */
#define RCC_BDCR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_BDCR_LSEON       ((uint32)0x00000001)
#define RCC_BDCR_LSERDY      ((uint32)0x00000002)
#define RCC_BDCR_LSEBYP      ((uint32)0x00000004)
#define RCC_BDCR_RTCSEL      ((uint32)0x00000300)
#define RCC_BDCR_RTCEN       ((uint32)0x00008000)
#define RCC_BDCR_BDRST       ((uint32)0x00010000)
/*
 * 时钟控制和状态寄存器 RCC_CSR
 * 偏移地址: 0x74
 * 复位值: 0x0E00 0000, reset by system reset except reset  flags by power reset only
 * 访问: 有0到3个时钟的等待状态, word/half-word/byte访问
 *       添加等待状态以防止连续的访问该寄存器
 */
#define RCC_CSR_RESET_VALUE    ((uint32)0x0E000000)    /* 复位值 */

#define RCC_CSR_LSION       ((uint32)0x00000001)
#define RCC_CSR_LSIRDY      ((uint32)0x00000002)
#define RCC_CSR_RMVF        ((uint32)0x01000000)
#define RCC_CSR_BORRSTF     ((uint32)0x02000000)
#define RCC_CSR_PINRSTF     ((uint32)0x04000000)
#define RCC_CSR_PORRSTF     ((uint32)0x08000000)
#define RCC_CSR_SFTRSTF     ((uint32)0x10000000)
#define RCC_CSR_IWDGRSTF    ((uint32)0x20000000)
#define RCC_CSR_WWDGRSTF    ((uint32)0x40000000)
#define RCC_CSR_LPWRRSTF    ((uint32)0x80000000)
/*
 * 扩频时钟寄存器 RCC_SSCGR
 * 偏移地址: 0x80
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_SSCGR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_SSCGR_MODPER       ((uint32)0x00001FFF)
#define RCC_SSCGR_INCSTEP      ((uint32)0x0FFFE000)
#define RCC_SSCGR_SPREADSEL    ((uint32)0x40000000)
#define RCC_SSCGR_SSCGEN       ((uint32)0x80000000)
/*
 * PLLI2S寄存器 RCC_PLLI2SCFGR
 * 偏移地址: 0x84
 * 复位值: 0x2000 3000
 * 访问: 没有等待状态, word/half-word/byte访问
 * PLLI2S时钟计算方法：
 * f(VCO clock) = f(PLLI2S clock input) * PLLI2SN / PLLM
 * f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
 */
#define RCC_PLLI2SCFGR_RESET_VALUE    ((uint32)0x20003000)    /* 复位值 */

#define RCC_PLLI2SCFGR_PLLI2SN       ((uint32)0x00007FC0)
#define RCC_PLLI2SCFGR_PLLI2SR       ((uint32)0x70000000)







#endif
