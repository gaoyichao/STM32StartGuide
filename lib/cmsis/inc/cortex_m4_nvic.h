/********************************************************************
 *
 *  Nested Vectored Interrupt Controller, NVIC
 *
 *  关于NVIC的详细内容参见ST公司的Cortex-M4 programming manual(PM0214)文档
 *  http://gaoyichao.com/Xiaotu/?book=mcu_stm32f407&title=cortex_m4_nvic
 *
 *	高乙超
 *  gaoyichao_2016@126.com
 *
 *******************************************************************/
#ifndef CORTEX_M4_NVIC_H
#define CORTEX_M4_NVIC_H

#include <types.h>

#define NVIC_PGroup_0           ((uint32)0x700) /*!< 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PGroup_1           ((uint32)0x600) /*!< 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PGroup_2           ((uint32)0x500) /*!< 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PGroup_3           ((uint32)0x400) /*!< 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PGroup_4           ((uint32)0x300) /*!< 4 bits for pre-emption priority 0 bits for subpriority */

/*
 * vector_table_1bit - 向量表的位定义,3个32bit
 */
struct vector_table_1bit {
    uint32 WWDG_Irq : 1;            /* 0 */
    uint32 PVD_Iqr : 1;             /* 1 */
    uint32 TAMP_STAMP_Irq : 1;      /* 2 */
    uint32 RTC_WKUP_Irq : 1;        /* 3 */
    uint32 FLASH_Irq : 1;           /* 4 */
    uint32 RCC_Irq : 1;             /* 5 */
    uint32 EXTI0_Irq : 1;           /* 6 */
    uint32 EXTI1_Irq : 1;           /* 7 */
    
    uint32 EXTI2_Irq : 1;           /* 8 */
    uint32 EXTI3_Irq : 1;           /* 9 */
    uint32 EXTI4_Irq : 1;           /* 10 */
    uint32 DMA1_Stream0_Irq : 1;    /* 11 */
    uint32 DMA1_Stream1_Irq : 1;    /* 12 */
    uint32 DMA1_Stream2_Irq : 1;    /* 13 */
    uint32 DMA1_Stream3_Irq : 1;    /* 14 */
    uint32 DMA1_Stream4_Irq : 1;    /* 15 */
    
    uint32 DMA1_Stream5_Irq : 1;    /* 16 */
    uint32 DMA1_Stream6_Irq : 1;    /* 17 */
    uint32 ADC_Irq : 1;             /* 18 */
    uint32 CAN1_TX_Irq : 1;         /* 19 */
    uint32 CAN1_RX0_Irq : 1;        /* 20 */
    uint32 CAN1_RX1_Irq : 1;        /* 21 */
    uint32 CAN1_SCE_Irq : 1;        /* 22 */
    uint32 EXTI9_5_Irq : 1;         /* 23 */
    
    uint32 TIM1_BRK_TIM9_Irq : 1;   /* 24 */
    uint32 TIM1_UP_TIM10_Irq : 1;   /* 25 */
    uint32 TIM1_TRG_COM_TIM11_Irq : 1; /* 26 */
    uint32 TIM1_CC_Irq : 1;         /* 27 */
    uint32 TIM2_Irq : 1;            /* 28 */
    uint32 TIM3_Irq : 1;            /* 29 */
    uint32 TIM4_Irq : 1;            /* 30 */
    uint32 I2C1_EV_Irq : 1;         /* 31 */
    // 1
    uint32 I2C1_ER_Irq : 1;         /* 32 */
    uint32 I2C2_EV_Irq : 1;         /* 33 */
    uint32 I2C2_ER_Irq : 1;         /* 34 */
    uint32 SPI1_Irq : 1;            /* 35 */
    uint32 SPI2_Irq : 1;            /* 36 */
    uint32 USART1_Irq : 1;          /* 37 */
    uint32 USART2_Irq : 1;          /* 38 */
    uint32 USART3_Irq : 1;          /* 39 */
    
    uint32 EXTI15_10_Irq : 1;       /* 40 */
    uint32 RTC_Alarm_Irq : 1;       /* 41 */
    uint32 OTG_FS_WKUP_Irq : 1;     /* 42 */
    uint32 TIM8_BRK_TIM12_Irq : 1;  /* 43 */
    uint32 TIM8_UP_TIM13_Irq : 1;   /* 44 */
    uint32 TIM8_TRG_COM_TIM14_Irq : 1; /* 45 */
    uint32 TIM8_CC_Irq : 1;         /* 46 */
    uint32 DMA1_Stream7_Irq : 1;    /* 47 */
    
    uint32 FSMC_Irq : 1;            /* 48 */
    uint32 SDIO_Irq : 1;            /* 49 */
    uint32 TIM5_Irq : 1;            /* 50 */
    uint32 SPI3_Irq : 1;            /* 51 */
    uint32 UART4_Irq : 1;           /* 52 */
    uint32 UART5_Irq : 1;           /* 53 */
    uint32 TIM6_DAC_Irq : 1;        /* 54 */
    uint32 TIM7_Irq : 1;            /* 55 */
    
    uint32 DMA2_Stream0_Irq : 1;    /* 56 */
    uint32 DMA2_Stream1_Irq : 1;    /* 57 */
    uint32 DMA2_Stream2_Irq : 1;    /* 58 */
    uint32 DMA2_Stream3_Irq : 1;    /* 59 */
    uint32 DMA2_Stream4_Irq : 1;    /* 60 */
    uint32 ETH_Irq : 1;             /* 61 */
    uint32 ETH_WKUP_Irq : 1;        /* 62 */
    uint32 CAN2_TX_Irq : 1;         /* 63 */
    // 2
    uint32 CAN2_RX0_Irq : 1;        /* 64 */
    uint32 CAN2_RX1_Irq : 1;        /* 65 */
    uint32 CAN2_SCE_Irq : 1;        /* 66 */
    uint32 OTG_FS_Irq : 1;          /* 67 */
    uint32 DMA2_Stream5_Irq : 1;    /* 68 */
    uint32 DMA2_Stream6_Irq : 1;    /* 69 */
    uint32 DMA2_Stream7_Irq : 1;    /* 70 */
    uint32 USART6_Irq : 1;          /* 71 */
    
    uint32 I2C3_EV_Irq : 1;         /* 72 */
    uint32 I2C3_ER_Irq : 1;         /* 73 */
    uint32 OTG_HS_EP1_OUT_Irq : 1;  /* 74 */
    uint32 OTG_HS_EP1_IN_Irq : 1;   /* 75 */
    uint32 OTG_HS_WKUP_Irq : 1;     /* 76 */
    uint32 OTG_HS_Irq : 1;          /* 77 */
    uint32 DCMI_Irq : 1;            /* 78 */
    uint32 CRYP_Irq : 1;            /* 79 */
    
    uint32 HASH_RNG_Irq : 1;        /* 80 */
    uint32 FPU_Irq : 1;             /* 81 */
    uint32 reserved : 14;
    // 3
};

union nvic_1bit_register {
    struct vector_table_1bit bits;
    uint32 words[3];
};


/*
 * vector_table_1bit - 向量表的位定义,3个32bit
 */
struct vector_table_8bit {
    uint8 WWDG_Irq;            /* 0 */
    uint8 PVD_Irq;             /* 1 */
    uint8 TAMP_STAMP_Irq;      /* 2 */
    uint8 RTC_WKUP_Irq;        /* 3 */
    // 1
    uint8 FLASH_Irq;           /* 4 */
    uint8 RCC_Irq;             /* 5 */
    uint8 EXTI0_Irq;           /* 6 */
    uint8 EXTI1_Irq;           /* 7 */
    // 2
    uint8 EXTI2_Irq;           /* 8 */
    uint8 EXTI3_Irq;           /* 9 */
    uint8 EXTI4_Irq;           /* 10 */
    uint8 DMA1_Stream0_Irq;    /* 11 */
    // 3
    uint8 DMA1_Stream1_Irq;    /* 12 */
    uint8 DMA1_Stream2_Irq;    /* 13 */
    uint8 DMA1_Stream3_Irq;    /* 14 */
    uint8 DMA1_Stream4_Irq;    /* 15 */
    // 4
    uint8 DMA1_Stream5_Irq;    /* 16 */
    uint8 DMA1_Stream6_Irq;    /* 17 */
    uint8 ADC_Irq;             /* 18 */
    uint8 CAN1_TX_Irq;         /* 19 */
    // 5
    uint8 CAN1_RX0_Irq;        /* 20 */
    uint8 CAN1_RX1_Irq;        /* 21 */
    uint8 CAN1_SCE_Irq;        /* 22 */
    uint8 EXTI9_5_Irq;         /* 23 */
    // 6
    uint8 TIM1_BRK_TIM9_Irq;   /* 24 */
    uint8 TIM1_UP_TIM10_Irq;   /* 25 */
    uint8 TIM1_TRG_COM_TIM11_Irq; /* 26 */
    uint8 TIM1_CC_Irq;         /* 27 */
    // 7
    uint8 TIM2_Irq;            /* 28 */
    uint8 TIM3_Irq;            /* 29 */
    uint8 TIM4_Irq;            /* 30 */
    uint8 I2C1_EV_Irq;         /* 31 */
    // 8
    uint8 I2C1_ER_Irq;         /* 32 */
    uint8 I2C2_EV_Irq;         /* 33 */
    uint8 I2C2_ER_Irq;         /* 34 */
    uint8 SPI1_Irq;            /* 35 */
    // 9
    uint8 SPI2_Irq;            /* 36 */
    uint8 USART1_Irq;          /* 37 */
    uint8 USART2_Irq;          /* 38 */
    uint8 USART3_Irq;          /* 39 */
    // 10
    uint8 EXTI15_10_Irq;       /* 40 */
    uint8 RTC_Alarm_Irq;       /* 41 */
    uint8 OTG_FS_WKUP_Irq;     /* 42 */
    uint8 TIM8_BRK_TIM12_Irq;  /* 43 */
    // 11
    uint8 TIM8_UP_TIM13_Irq;   /* 44 */
    uint8 TIM8_TRG_COM_TIM14_Irq; /* 45 */
    uint8 TIM8_CC_Irq;         /* 46 */
    uint8 DMA1_Stream7_Irq;    /* 47 */
    // 12
    uint8 FSMC_Irq;            /* 48 */
    uint8 SDIO_Irq;            /* 49 */
    uint8 TIM5_Irq;            /* 50 */
    uint8 SPI3_Irq;            /* 51 */
    // 13
    uint8 UART4_Irq;           /* 52 */
    uint8 UART5_Irq;           /* 53 */
    uint8 TIM6_DAC_Irq;        /* 54 */
    uint8 TIM7_Irq;            /* 55 */
    // 14
    uint8 DMA2_Stream0_Irq;    /* 56 */
    uint8 DMA2_Stream1_Irq;    /* 57 */
    uint8 DMA2_Stream2_Irq;    /* 58 */
    uint8 DMA2_Stream3_Irq;    /* 59 */
    // 15
    uint8 DMA2_Stream4_Irq;    /* 60 */
    uint8 ETH_Irq;             /* 61 */
    uint8 ETH_WKUP_Irq;        /* 62 */
    uint8 CAN2_TX_Irq;         /* 63 */
    // 16
    uint8 CAN2_RX0_Irq;        /* 64 */
    uint8 CAN2_RX1_Irq;        /* 65 */
    uint8 CAN2_SCE_Irq;        /* 66 */
    uint8 OTG_FS_Irq;          /* 67 */
    // 17
    uint8 DMA2_Stream5_Irq;    /* 68 */
    uint8 DMA2_Stream6_Irq;    /* 69 */
    uint8 DMA2_Stream7_Irq;    /* 70 */
    uint8 USART6_Irq;          /* 71 */
    // 18
    uint8 I2C3_EV_Irq;         /* 72 */
    uint8 I2C3_ER_Irq;         /* 73 */
    uint8 OTG_HS_EP1_OUT_Irq;  /* 74 */
    uint8 OTG_HS_EP1_IN_Irq;   /* 75 */
    // 19
    uint8 OTG_HS_WKUP_Irq;     /* 76 */
    uint8 OTG_HS_Irq;          /* 77 */
    uint8 DCMI_Irq;            /* 78 */
    uint8 CRYP_Irq;            /* 79 */
    // 20
    uint8 HASH_RNG_Irq;        /* 80 */
    uint8 FPU_Irq;             /* 81 */
};

union nvic_8bit_register {
    struct vector_table_8bit bits;
    uint8 bytes[82];
};

struct nvic_stir_bits {
    uint32 intid : 8;
    uint32 r0 : 24;
};

union nvic_stir {
    struct nvic_stir_bits bits;
    uint32 all;
};

typedef struct nvic_regs {
    /* 中断使能寄存器 */
    volatile union nvic_1bit_register ISER;
    uint32 r0[29];
    /* 清除中断使能寄存器 */
    volatile union nvic_1bit_register ICER;
    uint32 r1[29];
    /* 中断Pending置位寄存器 */
    volatile union nvic_1bit_register ISPR;
    uint32 r2[29];
    /* 中断Pending清除寄存器 */
    volatile union nvic_1bit_register ICPR;
    uint32 r3[29];
    /* 中断Active状态寄存器, 只读 */
    volatile union nvic_1bit_register IABR;
    uint32 r4[61];
    /* 中断优先级寄存器 */
    volatile union nvic_8bit_register IPR;
    uint8 r5[2];
    uint32 r6[683];
    /* 软件触发中断寄存器(Software Trigger Interrupt Register) */
    volatile union nvic_stir STIR;
} nvic_regs_t;
/* SCB寄存器地址映射 */
#define NVIC_BASE  0xE000E100
/* SCB寄存器指针访问 */
#define NVIC ((nvic_regs_t *) NVIC_BASE)


void NVIC_SetPriorityGroup(uint32 group);

#endif
