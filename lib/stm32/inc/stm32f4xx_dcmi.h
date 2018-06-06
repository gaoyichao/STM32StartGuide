/***********************************************************
 *
 * stm32f4xx_dcmi - ��������ͷ
 *
 ************************************** ���ҳ�.2018.0604 ***/
#ifndef STM32F4XX_DCMI_H
#define STM32F4XX_DCMI_H

#include <types.h>

#define DCMI_CR_FCRC_All    0   // ��������֡
#define DCMI_CR_FCRC_Half   1   // ����50%֡
#define DCMI_CR_FCRC_Quat   2   // ����25%֡

#define DCMI_CR_EDM_8bit    0
#define DCMI_CR_EDM_10bit   1
#define DCMI_CR_EDM_12bit   2
#define DCMI_CR_EDM_14bit   3

struct dcmi_cr_bits {
    // ʹ�ܲ���,��ʼ�������ݡ�
    // �ڿ���ģʽ��,һ֡ͼ����ս�����,���Զ������λ;
    // ��Ҫ��DMA�Լ�DCMI�����ý�����,����λ��λ,��ʼ��������
    uint32 CAPTURE : 1;
    // Capture Mode - ����ģʽ��
    // 0: ����ץȡģʽ, ���յ�������ͨ��DMA���浽������,������DMA����������
    // 1: ����ģʽ, ֻ����һ֡ͼ��
    uint32 CM : 1;
    // �ü�����
    // 0: ��������ͼ��,��ģʽ��һ֡ͼ��Ĵ�СӦ��4��������
    // 1: ֻ����ü��Ĵ��������Ĵ����ڵ�����
    uint32 CROP : 1;
    // JPEGѹ��ͼ��ģʽ��
    // 0: û��ѹ������Ƶ��ʽ
    // 1: JPEG��ʽ������, HSYNC�źŲ���������ͬ���ź�,ֻ�Ǳ�����ݿ���
    // ��ģʽ��,��֧��ͼ��ü�����Ƕͬ����
    uint32 JPEG : 1;
    // Embedded Synchronization Select,��Ƕͬ���롣
    // 0: ʹ��HSYNC��VSYNCӲ���ź���Ϊ��ͬ����֡ͬ���ź�
    // 1: ���������ڲ�ͨ�������ֽ���Ϊ��ͬ����֡ͬ���ź�
    uint32 ESS : 1;
    // ����ʱ�Ӽ���
    // 0: �½��ز�������
    // 1: �����ز�������
    uint32 PCKPOL : 1;
    // ��ͬ���źż���
    uint32 HSPOL : 1;
    // ֡ͬ���źż���
    uint32 VSPOL : 1;
    // ֡�ʿ���,ֻ�����������ģʽ��������
    uint32 FCRC : 2;
    // �����߿�
    uint32 EDM : 2;
    uint32 rsv0 : 2;
    uint32 ENABLE: 1;
    uint32 rsv1 : 17;
};
union dcmi_cr {
    struct dcmi_cr_bits bits;
    uint32 all;
};

struct dcmi_sr_bits {
    uint32 HSYNC : 1;
    uint32 VSYNC : 1;
    uint32 FNE : 1;
    uint32 rsv0 : 29;
};

union dcmi_sr {
    struct dcmi_sr_bits bits;
    uint32 all;
};

/*
 * dcmi_interrupt_bits - raw interrupt status
 */
struct dcmi_interrupt_bits {
    uint32 FRAME : 1;
    uint32 OVR : 1;
    uint32 ERR : 1;
    uint32 VSYNC : 1;
    uint32 LINE : 1;
    uint32 rsv0 : 27;
};

union dcmi_interrupt {
    struct dcmi_interrupt_bits bits;
    uint32 all;
};

struct dcmi_es_bits {
    uint32 FS : 8;
    uint32 LS : 8;
    uint32 LE : 8;
    uint32 FE : 8;
};

union dcmi_es {
    struct dcmi_es_bits bits;
    uint32 all;
};

struct dcmi_cwstrt_bits {
    // Horizontal Offset Count
    uint32 HOFFCNT : 14;
    uint32 rsv0 : 2;
    // Vertical Start Line Count
    uint32 VST : 13;
    uint32 rsv1 : 3;
};

union dcmi_cwstrt {
    struct dcmi_cwstrt_bits bits;
    uint32 all;
};

struct dcmi_cwsize_bits {
    uint32 CAPCNT : 14;
    uint32 rsv0 : 2;
    uint32 VLINE : 14;
    uint32 rsv1 : 2;
};

union dcmi_cwsize {
    struct dcmi_cwsize_bits bits;
    uint32 all;
};

union dcmi_dr {
    uint8 bytes[4];
    uint32 all;
};

typedef struct dcmi_regs
{
  volatile union dcmi_cr CR;            /* DCMI���ƼĴ���1, offset: 0x00 */
  volatile union dcmi_sr SR;            /* DCMI״̬�Ĵ���, offset: 0x04 */
  volatile union dcmi_interrupt RIS;    /* DCMIԭʼ�ж�״̬�Ĵ���, offset: 0x08 */
  volatile union dcmi_interrupt IER;    /* DCMI�ж�ʹ�ܼĴ���, offset: 0x0C */
  volatile union dcmi_interrupt MIS;    /* DCMI�ж����μĴ���, offset: 0x10 */
  volatile union dcmi_interrupt ICR;    /* DCMI�ж�����Ĵ���, offset: 0x14 */
  volatile union dcmi_es ESCR;          /* DCMI��Ƕͬ���ź�, offset: 0x18 */
  volatile union dcmi_es ESUR;          /* DCMI��Ƕͬ�������ź�, offset: 0x1C */
  volatile union dcmi_cwstrt CWSTRTR;   /* DCMI�ü�������ʼ����, offset: 0x20 */
  volatile union dcmi_cwsize CWSIZER;   /* DCMI�ü����ڴ�С, offset: 0x24 */
  volatile union dcmi_dr DR;            /* DCMI���ݼĴ���, offset: 0x28 */
} dcmi_regs_t;

/* DCMI�Ĵ�����ַӳ�� */
#define DCMI_BASE 0x50050000
/* DCMI�Ĵ���ָ����� */
#define DCMI ((dcmi_regs_t *) DCMI_BASE)

void dcmi_reset(void);


#endif





