/***********************************************************
 *
 * stm32f4xx_rcc - ��λ��ʱ�ӿ���,Reset and Clock Control
 *
 ************************************** ���ҳ�.2016.1224 ***/
#ifndef STM32F4XX_RCC_H
#define STM32F4XX_RCC_H

#include <types.h>


/*
 * ���໷���üĴ��� RCC_PLLCFGR
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x2400 3010
 * ����: �޵ȴ�״̬, word/half-word/byte����
 *
 * ϵͳʱ�Ӽ��㷽����
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
 * ʱ�����üĴ��� RCC_CFGR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: �����ʷ�����ʱ���л�ʱ����1���������ȴ�����, word/half-word/byte����
 */
#define RCC_HPRE_DIV1       0x0 /* 1��Ƶ */
#define RCC_HPRE_DIV2       0x8 /* 2��Ƶ */
#define RCC_HPRE_DIV4       0x9 /* 4��Ƶ */
#define RCC_HPRE_DIV8       0xa /* 8��Ƶ */
#define RCC_HPRE_DIV16      0xb /* 16��Ƶ */
#define RCC_HPRE_DIV64      0xc/* 64��Ƶ */
#define RCC_HPRE_DIV128     0xd/* 128��Ƶ */
#define RCC_HPRE_DIV256     0xe/* 256��Ƶ */
#define RCC_HPRE_DIV512     0xf/* 512��Ƶ */

#define RCC_PPRE_DIV1       0x0 /* 1��Ƶ */
#define RCC_PPRE_DIV2       0x4 /* 2��Ƶ */
#define RCC_PPRE_DIV4       0x5 /* 4��Ƶ */
#define RCC_PPRE_DIV8       0x6 /* 8��Ƶ */
#define RCC_PPRE_DIV16      0x7 /* 16��Ƶ */

#define RCC_SW_HSI  ((uint32)0x00000000)    /* �ڲ�����ʱ�� */
#define RCC_SW_HSE  ((uint32)0x00000001)    /* �ⲿ����ʱ�� */
#define RCC_SW_PLL  ((uint32)0x00000002)   /* PLL */
struct rcc_cfgr_bits {
    // sw - ����ϵͳʱ��Դ
    uint32 sw : 2;
    // sws - ֻ��,��ȡϵͳʱ��Դ��Ϣ
    uint32 sws : 2;
    // hpre - AHBʱ�ӷ�Ƶ��
    uint32 hpre : 4;
    uint32 rsv0 : 2;
    // ppre1 - ����APB1��Ƶ��
    uint32 ppre1 : 3;
    // ppre2 - ����APB2��Ƶ��
    uint32 ppre2 : 3;
    // rtcpre - RTC��Ƶ��
    uint32 rtcpre : 5;
    // mco - Microcontroller clock output 1
    uint32 mco1 : 2;
    // i2ssrc - I2Sʱ��Դ
    uint32 i2ssrc : 1;
    // mco1pre - mco1��Ƶ��
    uint32 mco1pre : 3;
    // mco2pre - mco2��Ƶ��
    uint32 mco2pre : 3;
    // mco2 - Microcontroller clock output 2
    uint32 mco2 : 2;
};

union rcc_cfgr {
    struct rcc_cfgr_bits bits;
    uint32 all;
};

/*
 * AHB1����ʱ��ʹ�ܼĴ��� RCC_AHB1ENR
 * ƫ�Ƶ�ַ: 0x30
 * ��λֵ: 0x0010 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
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
 * AHB1����ʱ��ʹ�ܼĴ��� RCC_AHB2ENR
 * ƫ�Ƶ�ַ: 0x34
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
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
 * AHB1����ʱ��ʹ�ܼĴ��� RCC_APB2R
 * ƫ�Ƶ�ַ: 0x44
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
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
    volatile uint32 CR;            /* ʱ�ӿ��ƼĴ���, offset: 0x00 */
    volatile union rcc_pllcfgr PLLCFGR;       /* ���໷���üĴ���, offset: 0x04 */
    volatile union rcc_cfgr CFGR;          /* ʱ�����üĴ���, offset: 0x08 */
    volatile uint32 CIR;           /* ʱ���жϼĴ���, offset: 0x0C */
    volatile uint32 AHB1RSTR;      /* AHB1���踴λ�Ĵ���, offset: 0x10 */
    volatile uint32 AHB2RSTR;      /* AHB2���踴λ�Ĵ���, offset: 0x14 */
    volatile uint32 AHB3RSTR;      /* AHB3���踴λ�Ĵ���, offset: 0x18 */
    uint32 RESERVED0;               /* ����, 0x1C */
    volatile union rcc_apb1r APB1RSTR;      /* APB1���踴λ�Ĵ���, offset: 0x20 */
    volatile union rcc_apb2r APB2RSTR;      /* APB2���踴λ�Ĵ���, offset: 0x24 */
    uint32  RESERVED1[2];           /* ����, 0x28-0x2C */
    volatile union rcc_ahb1enr AHB1ENR;       /* AHB1����ʱ��ʹ�ܼĴ���, offset: 0x30 */
    volatile union rcc_ahb2enr AHB2ENR;       /* AHB2����ʱ��ʹ�ܼĴ���, offset: 0x34 */
    volatile uint32 AHB3ENR;       /* AHB3����ʱ��ʹ�ܼĴ���, offset: 0x38 */
    uint32 RESERVED2;               /* ����, 0x3C */
    volatile union rcc_apb1r APB1ENR;       /* APB1����ʱ��ʹ�ܼĴ���, offset: 0x40 */
    volatile union rcc_apb2r APB2ENR;       /* APB2����ʱ��ʹ�ܼĴ���, offset: 0x44 */
    uint32 RESERVED3[2];            /* ����, 0x48-0x4C */
    volatile uint32 AHB1LPENR;     /* AHB1�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x50 */
    volatile uint32 AHB2LPENR;     /* AHB2�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x54 */
    volatile uint32 AHB3LPENR;     /* AHB3�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x58 */
    uint32 RESERVED4;               /* ����, 0x5C */
    volatile union rcc_apb1r APB1LPENR;     /* APB1�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x60 */
    volatile union rcc_apb2r APB2LPENR;     /* APB2�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x64 */
    uint32 RESERVED5[2];            /* ����, 0x68-0x6C */
    volatile uint32 BDCR;          /* Backup domain���ƼĴ���, offset: 0x70 */
    volatile uint32 CSR;           /* ʱ�ӿ��ƺ�״̬�Ĵ���, offset: 0x74 */
    uint32 RESERVED6[2];            /* ����, 0x78-0x7C */
    volatile uint32 SSCGR;         /* ��Ƶʱ�ӷ������Ĵ���(�������ܸߴ��ϣ���ʲô����ʱ��֪�����Ժ����ϸ����) offset: 0x80 */
    volatile uint32 PLLI2SCFGR;    /* ���໷PLLI2S���üĴ���, offset: 0x84 */
} rcc_regs_t;

/* RCC�Ĵ�����ַӳ�� */
#define RCC_BASE 0x40023800
/* RCC�Ĵ���ָ����� */
#define RCC ((rcc_regs_t *) RCC_BASE)

/*
 * ʱ�ӿ��ƼĴ��� RCC_CR
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x0000 XX83
 * ����: �޵ȴ�״̬, word/half-word/byte����
 */
#define RCC_CR_RESET_VALUE  ((uint32)0x00000083)        /* ��λֵ           */
#define RCC_CR_HSION        ((uint32)0x00000001)        /* �ڲ�����ʱ�� ʹ�� */
#define RCC_CR_HSIRDY       ((uint32)0x00000002)        /* �ڲ�����ʱ�� ���� */
#define RCC_CR_HSITRIM      ((uint32)0x000000F8)        /* �ڲ�����ʱ�� ���� */
#define RCC_CR_HSICAL       ((uint32)0x0000FF00)        /* �ڲ�����ʱ�� У׼ */
#define RCC_CR_HSEON        ((uint32)0x00010000)        /* �ⲿ����ʱ�� ʹ�� */
#define RCC_CR_HSERDY       ((uint32)0x00020000)        /* �ⲿ����ʱ�� ���� */
#define RCC_CR_HSEBYP       ((uint32)0x00040000)        /* �ⲿ����ʱ�� ��· */
#define RCC_CR_CSSON        ((uint32)0x00080000)        /* ʱ�Ӱ�ȫϵͳ ʹ�� */
#define RCC_CR_PLLON        ((uint32)0x01000000)        /* PLL         ʹ�� */
#define RCC_CR_PLLRDY       ((uint32)0x02000000)        /* PLL         ���� */
#define RCC_CR_PLLI2SON     ((uint32)0x04000000)        /* PLLI2S      ���� */
#define RCC_CR_PLLI2SRDY    ((uint32)0x08000000)        /* PLLI2S      ���� */

/*
 * ʱ���жϼĴ��� RCC_CIR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_CIR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_CIR_LSIRDYF         ((uint32)0x00000001)        /* LSIʱ�Ӿ����ж�,LSIRDYIE=1ʱ��Ӳ����1,���д1��LSIRDYCλ��� */
#define RCC_CIR_LSERDYF         ((uint32)0x00000002)        /* LSEʱ�Ӿ����ж�,LSERDYIE=1ʱ��Ӳ����1,���д1��LSERDYCλ��� */
#define RCC_CIR_HSIRDYF         ((uint32)0x00000004)        /* HSIʱ�Ӿ����ж�,HSIRDYIE=1ʱ��Ӳ����1,���д1��HSIRDYCλ��� */
#define RCC_CIR_HSERDYF         ((uint32)0x00000008)        /* HSEʱ�Ӿ����ж�,HSERDYIE=1ʱ��Ӳ����1,���д1��HSERDYCλ��� */
#define RCC_CIR_PLLRDYF         ((uint32)0x00000010)        /* PLLʱ�Ӿ����ж�,PLLRDYIE=1ʱ��Ӳ����1,���д1��PLLRDYCλ��� */
#define RCC_CIR_PLLI2SRDYF      ((uint32)0x00000020)        /* PLLI2Sʱ�Ӿ����ж�,PLLRDYIE=1ʱ��Ӳ����1,���д1��PLLRDYCλ��� */
#define RCC_CIR_CSSF            ((uint32)0x00000080)        /* ʱ�Ӱ�ȫϵͳ�жϱ�־,HSEʧЧʱӲ����1,���д1��CSSCλ��� */
#define RCC_CIR_LSIRDYIE        ((uint32)0x00000100)        /* LSI�����ж�ʹ�� */
#define RCC_CIR_LSERDYIE        ((uint32)0x00000200)        /* LSE�����ж�ʹ�� */
#define RCC_CIR_HSIRDYIE        ((uint32)0x00000400)        /* HSI�����ж�ʹ�� */
#define RCC_CIR_HSERDYIE        ((uint32)0x00000800)        /* HSE�����ж�ʹ�� */
#define RCC_CIR_PLLRDYIE        ((uint32)0x00001000)        /* PLL�����ж�ʹ�� */
#define RCC_CIR_PLLI2SRDYIE     ((uint32)0x00002000)        /* PLL�����ж�ʹ�� */
#define RCC_CIR_LSIRDYC         ((uint32)0x00010000)        /* ���LSI�����ж� */
#define RCC_CIR_LSERDYC         ((uint32)0x00020000)        /* ���LSE�����ж� */
#define RCC_CIR_HSIRDYC         ((uint32)0x00040000)        /* ���HSI�����ж� */
#define RCC_CIR_HSERDYC         ((uint32)0x00080000)        /* ���HSE�����ж� */
#define RCC_CIR_PLLRDYC         ((uint32)0x00100000)        /* ���PLL�����ж� */
#define RCC_CIR_PLLI2SRDYC      ((uint32)0x00200000)        /* ���PLL�����ж� */
#define RCC_CIR_CSSC            ((uint32)0x00800000)        /* ���ʱ�Ӱ�ȫϵͳ�ж� */

#define RCC_CIE_ALLE            ((uint32)0x00003F00)        /* �������ж� */
#define RCC_CIR_ALLC            ((uint32)0x00BF0000)        /* ��������жϱ�־ */
/*
 * AHB1���踴λ�Ĵ��� RCC_AHB1RSTR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * AHB2���踴λ�Ĵ��� RCC_AHB2RSTR
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB2RSTR_DCMI    ((uint32)0x00000001)
#define RCC_AHB2RSTR_CRYP    ((uint32)0x00000010)
#define RCC_AHB2RSTR_HASH    ((uint32)0x00000020)
#define RCC_AHB2RSTR_RNG     ((uint32)0x00000040)
#define RCC_AHB2RSTR_OTGFS   ((uint32)0x00000080)
/*
 * AHB3���踴λ�Ĵ��� RCC_AHB3RSTR
 * ƫ�Ƶ�ַ: 0x18
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB3RSTR_FSMC    ((uint32)0x00000001)
/*
 * APB1���踴λ�Ĵ��� RCC_APB1RSTR
 * ƫ�Ƶ�ַ: 0x20
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * APB2���踴λ�Ĵ��� RCC_APB2RSTR
 * ƫ�Ƶ�ַ: 0x24
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * AHB2����ʱ��ʹ�ܼĴ��� RCC_AHB2ENR
 * ƫ�Ƶ�ַ: 0x34
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB2ENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2ENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2ENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2ENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2ENR_OTGFS      ((uint32)0x00000080)
/*
 * AHB3����ʱ��ʹ�ܼĴ��� RCC_AHB3ENR
 * ƫ�Ƶ�ַ: 0x38
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB3ENR_FSMC       ((uint32)0x00000001)
/*
 * APB1����ʱ��ʹ�ܼĴ��� RCC_APB1ENR
 * ƫ�Ƶ�ַ: 0x40
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * APB2����ʱ��ʹ�ܼĴ��� RCC_APB2ENR
 * ƫ�Ƶ�ַ: 0x44
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * �͵�ѹģʽ��AHB1����ʱ��ʹ�ܼĴ��� RCC_AHB1LPENR
 * ƫ�Ƶ�ַ: 0x50
 * ��λֵ: 0x7E67 91FF
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB1LPENR_RESET_VALUE    ((uint32)0x7E6791FF)    /* ��λֵ */

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
 * �͵�ѹģʽ��AHB2����ʱ��ʹ�ܼĴ��� RCC_AHB2LPENR
 * ƫ�Ƶ�ַ: 0x54
 * ��λֵ: 0x0000 00F1
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2LPENR_RESET_VALUE    ((uint32)0x000000F1)    /* ��λֵ */

#define RCC_AHB2LPENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2LPENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2LPENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2LPENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2LPENR_OTGFS      ((uint32)0x00000080)
/*
 * �͵�ѹģʽ��AHB3����ʱ��ʹ�ܼĴ��� RCC_AHB3LPENR
 * ƫ�Ƶ�ַ: 0x58
 * ��λֵ: 0x0000 0001
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3LPENR_RESET_VALUE    ((uint32)0x00000001)    /* ��λֵ */

#define RCC_AHB3LPENR_FSMC       ((uint32)0x00000001)
/*
 * �͵�ѹģʽ��APB1����ʱ��ʹ�ܼĴ��� RCC_APB1LPENR
 * ƫ�Ƶ�ַ: 0x60
 * ��λֵ: 0x36FE C9FF
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1LPENR_RESET_VALUE    ((uint32)0x36FEC9FF)    /* ��λֵ */

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
 * �͵�ѹģʽ��APB2����ʱ��ʹ�ܼĴ��� RCC_APB2LPENR
 * ƫ�Ƶ�ַ: 0x64
 * ��λֵ: 0x0407 5F33
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2LPENR_RESET_VALUE    ((uint32)0x04075F33)    /* ��λֵ */

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
 * ƫ�Ƶ�ַ: 0x70
 * ��λֵ: 0x0000 0000, reset by reset domain reset
 * ����: ��0��3��ʱ�ӵĵȴ�״̬, word/half-word/byte����
 *       ��ӵȴ�״̬�Է�ֹ�����ķ��ʸüĴ���
 */
#define RCC_BDCR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_BDCR_LSEON       ((uint32)0x00000001)
#define RCC_BDCR_LSERDY      ((uint32)0x00000002)
#define RCC_BDCR_LSEBYP      ((uint32)0x00000004)
#define RCC_BDCR_RTCSEL      ((uint32)0x00000300)
#define RCC_BDCR_RTCEN       ((uint32)0x00008000)
#define RCC_BDCR_BDRST       ((uint32)0x00010000)
/*
 * ʱ�ӿ��ƺ�״̬�Ĵ��� RCC_CSR
 * ƫ�Ƶ�ַ: 0x74
 * ��λֵ: 0x0E00 0000, reset by system reset except reset  flags by power reset only
 * ����: ��0��3��ʱ�ӵĵȴ�״̬, word/half-word/byte����
 *       ��ӵȴ�״̬�Է�ֹ�����ķ��ʸüĴ���
 */
#define RCC_CSR_RESET_VALUE    ((uint32)0x0E000000)    /* ��λֵ */

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
 * ��Ƶʱ�ӼĴ��� RCC_SSCGR
 * ƫ�Ƶ�ַ: 0x80
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_SSCGR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_SSCGR_MODPER       ((uint32)0x00001FFF)
#define RCC_SSCGR_INCSTEP      ((uint32)0x0FFFE000)
#define RCC_SSCGR_SPREADSEL    ((uint32)0x40000000)
#define RCC_SSCGR_SSCGEN       ((uint32)0x80000000)
/*
 * PLLI2S�Ĵ��� RCC_PLLI2SCFGR
 * ƫ�Ƶ�ַ: 0x84
 * ��λֵ: 0x2000 3000
 * ����: û�еȴ�״̬, word/half-word/byte����
 * PLLI2Sʱ�Ӽ��㷽����
 * f(VCO clock) = f(PLLI2S clock input) * PLLI2SN / PLLM
 * f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
 */
#define RCC_PLLI2SCFGR_RESET_VALUE    ((uint32)0x20003000)    /* ��λֵ */

#define RCC_PLLI2SCFGR_PLLI2SN       ((uint32)0x00007FC0)
#define RCC_PLLI2SCFGR_PLLI2SR       ((uint32)0x70000000)







#endif
