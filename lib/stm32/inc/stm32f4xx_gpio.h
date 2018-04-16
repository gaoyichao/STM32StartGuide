/***********************************************************
 *
 * stm32f407_gpio - ͨ��IO
 *
 ************************************** ���ҳ�.2016.1224 ***/
#ifndef STM32F407_GPIO_H
#define STM32F407_GPIO_H

#include <types.h>

/*
 * �˿�ģʽ�Ĵ��� GPIO_MODER
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0xA800 0000(GPIOA), 0x0000 0280(GPIOB), 0x0000 0000(����)
 * ����: word/half-word/byte����
 */
struct gpio_moder_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_moder {
    struct gpio_moder_bits bits;
    uint32 all;
};
/*
 * �˿�������ͼĴ��� GPIO_OTYPER
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000 0000
 * ����: word/half-word/byte����
 */
struct gpio_otyper_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_otyper {
    struct gpio_otyper_bits bits;
    uint32 all;
};
/*
 * �˿�����ٶȼĴ��� GPIO_OSPEEDR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0C00 0000(GPIOA), 0x0000 00C0(GPIOB), 0x0000 0000(����)
 * ����: word/half-word/byte����
 */
struct gpio_ospeedr_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_ospeedr {
    struct gpio_ospeedr_bits bits;
    uint32 all;
};
/*
 * �˿�������������Ĵ��� GPIO_PUPDR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x6400 0000(GPIOA), 0x0000 0100(GPIOB), 0x0000 0000(����)
 * ����: word/half-word/byte����
 */
struct gpio_pupdr_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_pupdr {
    struct gpio_pupdr_bits bits;
    uint32 all;
};
/*
 * �˿��������ݼĴ��� GPIO_IDR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x0000 XXXX
 * ����: word/half-word/byte����
 */
struct gpio_idr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_idr {
    struct gpio_idr_bits bits;
    uint32 all;
};
/*
 * �˿��������ݼĴ��� GPIO_ODR
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0000 0000
 * ����: word/half-word/byte����
 */
struct gpio_odr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_odr {
    struct gpio_odr_bits bits;
    uint32 all;
};
/*
 * �˿�Set/Reset�Ĵ��� GPIO_BSRR
 * ƫ�Ƶ�ַ: 0x18
 * ��λֵ: 0x0000 0000
 * ����: word/half-word/byte����
 */
struct gpio_bsrrl_bits {
    uint16 pin0 : 1;
    uint16 pin1 : 1;
    uint16 pin2 : 1;
    uint16 pin3 : 1;

    uint16 pin4 : 1;
    uint16 pin5 : 1;
    uint16 pin6 : 1;
    uint16 pin7 : 1;

    uint16 pin8 : 1;
    uint16 pin9 : 1;
    uint16 pin10 : 1;
    uint16 pin11 : 1;

    uint16 pin12 : 1;
    uint16 pin13 : 1;
    uint16 pin14 : 1;
    uint16 pin15 : 1;
};
union gpio_bsrrl {
    struct gpio_bsrrl_bits bits;
    uint16 all;
};
struct gpio_bsrrh_bits {
    uint16 pin0 : 1;
    uint16 pin1 : 1;
    uint16 pin2 : 1;
    uint16 pin3 : 1;

    uint16 pin4 : 1;
    uint16 pin5 : 1;
    uint16 pin6 : 1;
    uint16 pin7 : 1;

    uint16 pin8 : 1;
    uint16 pin9 : 1;
    uint16 pin10 : 1;
    uint16 pin11 : 1;

    uint16 pin12 : 1;
    uint16 pin13 : 1;
    uint16 pin14 : 1;
    uint16 pin15 : 1;
};
union gpio_bsrrh {
    struct gpio_bsrrh_bits bits;
    uint16 all;
};
struct gpio_bsrr_hws {
    union gpio_bsrrl set;
    union gpio_bsrrh reset;
};
union gpio_bsrr {
    struct gpio_bsrr_hws hwords;
    uint32 all;
};
/*
 * �˿����������Ĵ��� GPIO_LCKR
 * ƫ�Ƶ�ַ: 0x1C
 * ��λֵ: 0x0000 0000
 * ����: word����
 *
 * ������101������дkey�󣬶˿ڵ����ý���������ֱ����һ��MCU������������ʱ����
 * ÿ��pin���������˿ڵ�һ�����ŵ�����
 * ��дkeyʱ��pin��ֵ��Ӧ���䶯���üĴ���ֻ��32λ����
 */
struct gpio_lckr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 key : 1;
    uint32 reserved : 15;
};
union gpio_lckr {
    struct gpio_lckr_bits bits;
    uint32 all;
};

/*
 * �˿ڸ�ѡ���ܼĴ��� GPIO_AFR
 * ƫ�Ƶ�ַ: 0x20
 * ��λֵ: 0x0000 0000
 * ����: word/half-word/byte����
 */
#include <stm32f4xx_ioafmap.h>
struct gpio_afr_bits {
    uint32 pin0 : 4;
    uint32 pin1 : 4;
    uint32 pin2 : 4;
    uint32 pin3 : 4;

    uint32 pin4 : 4;
    uint32 pin5 : 4;
    uint32 pin6 : 4;
    uint32 pin7 : 4;

    uint32 pin8 : 4;
    uint32 pin9 : 4;
    uint32 pin10 : 4;
    uint32 pin11 : 4;

    uint32 pin12 : 4;
    uint32 pin13 : 4;
    uint32 pin14 : 4;
    uint32 pin15 : 4;
};
union gpio_afr {
    struct gpio_afr_bits bits;
    uint32 afr[2];
};

typedef struct gpio_regs {
    volatile union gpio_moder MODER;        /* �˿�ģʽ�Ĵ���, offset: 0x00 */
    volatile union gpio_otyper OTYPER;      /* �˿�������ͼĴ���, offset: 0x04 */
    volatile union gpio_ospeedr OSPEEDR;    /* �˿�����ٶȼĴ���, offset: 0x08 */
    volatile union gpio_pupdr PUPDR;        /* �˿�������������Ĵ���, offset: 0x0C */
    volatile union gpio_idr IDR;            /* �˿��������ݼĴ���, offset: 0x10 */
    volatile union gpio_odr ODR;            /* �˿�������ݼĴ���, offset: 0x14 */
    volatile union gpio_bsrr BSRR;          /* �˿�Set/Reset�Ĵ���, offset: 0x18 */
    volatile union gpio_lckr LCKR;          /* �˿����������Ĵ���, offset: 0x1C */
    volatile union gpio_afr AFR;            /* �˿ڸ�ѡ���ܼĴ���, offset: 0x20-0x24 */
} gpio_regs_t;

/* GPIO�Ĵ�����ַӳ�� */
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00
#define GPIOI_BASE 0x40022000
/* GPIO�Ĵ���ָ����� */
#define GPIOA ((gpio_regs_t *) GPIOA_BASE)
#define GPIOB ((gpio_regs_t *) GPIOB_BASE)
#define GPIOC ((gpio_regs_t *) GPIOC_BASE)
#define GPIOD ((gpio_regs_t *) GPIOD_BASE)
#define GPIOE ((gpio_regs_t *) GPIOE_BASE)
#define GPIOF ((gpio_regs_t *) GPIOF_BASE)
#define GPIOG ((gpio_regs_t *) GPIOG_BASE)
#define GPIOH ((gpio_regs_t *) GPIOH_BASE)
#define GPIOI ((gpio_regs_t *) GPIOI_BASE)

/****************************************************************************************/

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_Addr(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_Addr(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //����

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //����

typedef unsigned long gpio_pin_t;
/****************************************************************************************/

#define GPIO_Mode_In 0x00
#define GPIO_Mode_Out 0x01
#define GPIO_Mode_Af 0x02
#define GPIO_Mode_Analog 0x03

#define GPIO_OType_PP 0
#define GPIO_OType_OD 1

#define GPIO_OSpeed_Low 0x00
#define GPIO_OSpeed_Medium 0x01
#define GPIO_OSpeed_High 0x02
#define GPIO_OSpeed_Very_High 0x03

#define GPIO_Pull_No 0x00
#define GPIO_Pull_Up 0x01
#define GPIO_Pull_Down 0x02

#define Gen_Gpio_Pin_Mode(id, mode) ((uint32)((mode) << 2 * (id)))
#define Gen_Gpio_Pin_OType(id, otype) ((uint32)((otype) << (id)))
#define Gen_Gpio_Pin_OSpeed(id, speed) ((uint32)((speed) << 2 * (id)))
#define Gen_Gpio_Pin_PuPd(id, pupd) ((uint32)((pupd) << 2 * (id)))

#define GPIO_Pin_0  ((uint16)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1  ((uint16)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2  ((uint16)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3  ((uint16)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4  ((uint16)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5  ((uint16)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6  ((uint16)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7  ((uint16)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8  ((uint16)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9  ((uint16)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10 ((uint16)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11 ((uint16)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12 ((uint16)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13 ((uint16)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14 ((uint16)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15 ((uint16)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All ((uint16)0xFFFF)  /* All pins selected */

struct gpio_pin_conf {
    uint8 mode;
    uint8 speed;
    uint8 otype;
    uint8 pull;
};

void gpio_init(gpio_regs_t *GPIOx, const uint16 pins, const struct gpio_pin_conf *conf);

#endif
