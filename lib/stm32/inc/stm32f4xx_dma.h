/***********************************************************
 *
 * stm32f407_dma - ֱ���ڴ����
 *
 ************************************** ���ҳ�.2017.0618 ***/

#pragma once

#include <types.h>

#define DMA_LISR_TCIF0      ((uint32)0x00000020)
#define DMA_LISR_HTIF0      ((uint32)0x00000010)
#define DMA_LISR_TEIF0      ((uint32)0x00000008)
#define DMA_LISR_DMEIF0     ((uint32)0x00000004)
#define DMA_LISR_FEIF0      ((uint32)0x00000001)

#define DMA_Stream0_IT_MASK     (uint32)(DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 | \
                                         DMA_LISR_TEIF0 | DMA_LISR_HTIF0 | \
                                         DMA_LISR_TCIF0)

#define DMA_Stream1_IT_MASK     (uint32)(DMA_Stream0_IT_MASK << 6)
#define DMA_Stream2_IT_MASK     (uint32)(DMA_Stream0_IT_MASK << 16)
#define DMA_Stream3_IT_MASK     (uint32)(DMA_Stream0_IT_MASK << 22)
#define DMA_Stream4_IT_MASK     (uint32)(DMA_Stream0_IT_MASK | (uint32)0x20000000)
#define DMA_Stream5_IT_MASK     (uint32)(DMA_Stream1_IT_MASK | (uint32)0x20000000)
#define DMA_Stream6_IT_MASK     (uint32)(DMA_Stream2_IT_MASK | (uint32)0x20000000)
#define DMA_Stream7_IT_MASK     (uint32)(DMA_Stream3_IT_MASK | (uint32)0x20000000)

/*
 * ��λ������Ӳ�������������DMA_LIFCRд1���
 */
struct dma_lir_bits {
    uint32 FEIF0 : 1;   /* FIFO���� */
    uint32 rsv0 : 1;
    uint32 DMEIF0 : 1;  /* Direct Mode���� */
    uint32 TEIF0 : 1;   /* Transfer���� */
    uint32 HTIF0 : 1;   /* Half Transfer */
    uint32 TCIF0 : 1;   /* Transfer Complete */

    uint32 FEIF1 : 1;   /* FIFO���� */
    uint32 rsv1 : 1;
    uint32 DMEIF1 : 1;  /* Direct Mode���� */
    uint32 TEIF1 : 1;   /* Transfer���� */
    uint32 HTIF1 : 1;   /* Half Transfer */
    uint32 TCIF1 : 1;   /* Transfer Complete */
    uint32 rsv2 : 4;

    uint32 FEIF2 : 1;   /* FIFO���� */
    uint32 rsv3 : 1;
    uint32 DMEIF2 : 1;  /* Direct Mode���� */
    uint32 TEIF2 : 1;   /* Transfer���� */
    uint32 HTIF2 : 1;   /* Half Transfer */
    uint32 TCIF2 : 1;   /* Transfer Complete */

    uint32 FEIF3 : 1;   /* FIFO���� */
    uint32 rsv4 : 1;
    uint32 DMEIF3 : 1;  /* Direct Mode���� */
    uint32 TEIF3 : 1;   /* Transfer���� */
    uint32 HTIF3 : 1;   /* Half Transfer */
    uint32 TCIF3 : 1;   /* Transfer Complete */
    uint32 rsv5 : 4;
};

union dma_lir {
    struct dma_lir_bits bits;
    uint32 all;
};

/*
 * ��λ������Ӳ�������������DMA_HIFCRд1���
 */
struct dma_hir_bits {
    uint32 FEIF4 : 1;   /* FIFO���� */
    uint32 rsv0 : 1;
    uint32 DMEIF4 : 1;  /* Direct Mode���� */
    uint32 TEIF4 : 1;   /* Transfer���� */
    uint32 HTIF4 : 1;   /* Half Transfer */
    uint32 TCIF4 : 1;   /* Transfer Complete */

    uint32 FEIF5 : 1;   /* FIFO���� */
    uint32 rsv1 : 1;
    uint32 DMEIF5 : 1;  /* Direct Mode���� */
    uint32 TEIF5 : 1;   /* Transfer���� */
    uint32 HTIF5 : 1;   /* Half Transfer */
    uint32 TCIF5 : 1;   /* Transfer Complete */
    uint32 rsv2 : 4;

    uint32 FEIF6 : 1;   /* FIFO���� */
    uint32 rsv3 : 1;
    uint32 DMEIF6 : 1;  /* Direct Mode���� */
    uint32 TEIF6 : 1;   /* Transfer���� */
    uint32 HTIF6 : 1;   /* Half Transfer */
    uint32 TCIF6 : 1;   /* Transfer Complete */

    uint32 FEIF7 : 1;   /* FIFO���� */
    uint32 rsv4 : 1;
    uint32 DMEIF7 : 1;  /* Direct Mode���� */
    uint32 TEIF7 : 1;   /* Transfer���� */
    uint32 HTIF7 : 1;   /* Half Transfer */
    uint32 TCIF7 : 1;   /* Transfer Complete */
    uint32 rsv5 : 4;
};

union dma_hir {
    struct dma_hir_bits bits;
    uint32 all;
};

#define DMA_DIR_P2M 0x0
#define DMA_DIR_M2P 0x1
#define DMA_DIR_M2M 0x2

#define DMA_PSIZE_8Bits 0x00
#define DMA_PSIZE_16Bits 0x01
#define DMA_PSIZE_32Bits 0x02

#define DMA_Priority_Low 0x0
#define DMA_Priority_Medium 0x1
#define DMA_Priority_High 0x2
#define DMA_Priority_Very_High 0x3

#define DMA_Burst_0 0x0
#define DMA_Burst_4 0x1
#define DMA_Burst_8 0x2
#define DMA_Burst_16 0x3

struct dma_sxcr_bits {
    // ʹ��ͨ�����������λ�͸�λ
    // ��һЩ��������£�Ҳ����ΪӲ����λ
    // ֻ���ڹر�ͨ��������£����ܹ����Configuration��FIFO
    uint32 EN : 1;
    // Direct Mode�����ж�ʹ��
    uint32 DMEIE : 1;
    // Transfer�����ж�ʹ��
    uint32 TEIE : 1;
    // Half Transfer�ж�ʹ��
    uint32 HTIE : 1;
    // Transfer Complete�ж�ʹ��
    uint32 TCIE : 1;
    // ������������
    // 0: DMAΪ����������1: ����Ϊ��������
    // ֻ����ENλΪ'0'ʱ���ſ����޸�
    uint32 PFCTRL : 1;
    // ���ݴ��ͷ���
    uint32 DIR : 2;
    // Circularģʽ
    // ��������Ϊ������ʱ��ѭ��ģʽ��ǿ�ƹر�
    uint32 CIRC : 1;
    // �����ַ����ģʽ
    // 0: ��ַ�̶���1: ÿ�����ݷ��ͺ�����
    uint32 PINC : 1;
    // �ڴ��ַ����ģʽ
    // 0: ��ַ�̶���1:����
    uint32 MINC : 1;
    // �������ݿ��
    uint32 PSIZE : 2;
    // �ڴ����ݿ��
    uint32 MSIZE : 2;
    // �����ַ����ƫ�ƴ�С
    // 0:��ַ�����Ӵ�С��PSIZE����, 1: �̶�Ϊ4
    uint32 PINCOS : 1;
    // ���ȼ�
    uint32 PL : 2;
    // ˫����ģʽ
    uint32 DBM : 1;
    // Current Target,ֻ��˫����ģʽ������
    // 0:����0(��SxM0AR�Ĵ�����¼),1:����1(��SxM1AR��¼)
    uint32 CT : 1;
    uint32 rsv : 1;
    // ����Burst��������
    uint32 PBURST : 2;
    // �ڴ�Burst��������
    uint32 MBURST : 2;
    // ͨ��ѡ��
    uint32 CHSEL : 3;
    uint32 rsv1 : 4;
};

union dma_sxcr {
    struct dma_sxcr_bits bits;
    uint32 all;
};

struct dma_sxndtr_bits {
    // Number of Data items to Transfer
    // ֻ����Stream�رյ�ʱ����ܹ�������Ĵ���д����
    // Stream������ʱ��üĴ�����ֻ���ģ�����Ż���Ҫ���Ͷ�������
    // ��ÿ�δ��ͺ�üĴ�����ֵ�����С
    uint32 NDT : 16;
    uint32 rsv : 16;
};

union dma_sxndtr {
    struct dma_sxndtr_bits bits;
    uint32 all;
};

#define DMA_FIFO_1 0x0
#define DMA_FIFO_2 0x1
#define DMA_FIFO_3 0x2
#define DMA_FIFO_4 0x3
#define DMA_FIFO_Is_Empty 0x4
#define DMA_FIFO_Is_Full 0x5

struct dma_sxfcr_bits {
    // FIFO��ֵѡ��
    uint32 FTH : 2;
    // �ر�Directģʽ
    uint32 DMDIS : 1;
    // FIFO״̬
    uint32 FS : 3;
    uint32 rsv : 1;
    // FIFO�����ж�ʹ��
    uint32 FEIE : 1;
    uint32 rsv1 : 24;
};

union dma_sxfcr {
    struct dma_sxfcr_bits bits;
    uint32 all;
};

typedef struct dma_stream_regs {
    union dma_sxcr CR;      /* DMA stream x ���üĴ���      */
    union dma_sxndtr NDTR;  /* DMA stream x ���������ݼĴ��� */
    uint32 PAR;             /* DMA stream x �����ַ�Ĵ���(32bit) */
    uint32 M0AR;            /* DMA stream x �ڴ�0��ַ�Ĵ���(32bit) */
    uint32 M1AR;            /* DMA stream x �ڴ�1��ַ�Ĵ���(32bit),ֻ��double bufferʱ���� */
    union dma_sxfcr FCR;    /* DMA stream x FIFO���ƼĴ��� */
} dma_stream_regs_t;

typedef struct dma_regs {
    volatile union dma_lir LISR;   /* DMA�ж�״̬�Ĵ���Low, offset: 0x00 */
    volatile union dma_hir HISR;   /* DMA�ж�״̬�Ĵ���High, offset: 0x04 */
    volatile union dma_lir LIFCR;  /* DMA�жϱ�ʶ����Ĵ���Low, offset: 0x08 */
    volatile union dma_hir HIFCR;  /* DMA�жϱ�ʶ����Ĵ���High, offset: 0x0C */
    volatile dma_stream_regs_t stregs[8];   /* Stream Regs, offset: 0x10 */
} dma_regs_t;

#define DMA1_BASE 0x40026000
#define DMA2_BASE 0x40026400
#define DMA1 ((dma_regs_t *) DMA1_BASE)
#define DMA2 ((dma_regs_t *) DMA2_BASE)

#define DMA1_Stream0_BASE (DMA1_BASE + 0x10)
#define DMA1_Stream1_BASE (DMA1_BASE + 0x28)
#define DMA1_Stream2_BASE (DMA1_BASE + 0x40)
#define DMA1_Stream3_BASE (DMA1_BASE + 0x58)
#define DMA1_Stream4_BASE (DMA1_BASE + 0x70)
#define DMA1_Stream5_BASE (DMA1_BASE + 0x88)
#define DMA1_Stream6_BASE (DMA1_BASE + 0xA0)
#define DMA1_Stream7_BASE (DMA1_BASE + 0xB8)
#define DMA1_Stream0 ((dma_stream_regs_t *)DMA1_Stream0_BASE)
#define DMA1_Stream1 ((dma_stream_regs_t *)DMA1_Stream1_BASE)
#define DMA1_Stream2 ((dma_stream_regs_t *)DMA1_Stream2_BASE)
#define DMA1_Stream3 ((dma_stream_regs_t *)DMA1_Stream3_BASE)
#define DMA1_Stream4 ((dma_stream_regs_t *)DMA1_Stream4_BASE)
#define DMA1_Stream5 ((dma_stream_regs_t *)DMA1_Stream5_BASE)
#define DMA1_Stream6 ((dma_stream_regs_t *)DMA1_Stream6_BASE)
#define DMA1_Stream7 ((dma_stream_regs_t *)DMA1_Stream7_BASE)

#define DMA2_Stream0_BASE (DMA2_BASE + 0x10)
#define DMA2_Stream1_BASE (DMA2_BASE + 0x28)
#define DMA2_Stream2_BASE (DMA2_BASE + 0x40)
#define DMA2_Stream3_BASE (DMA2_BASE + 0x58)
#define DMA2_Stream4_BASE (DMA2_BASE + 0x70)
#define DMA2_Stream5_BASE (DMA2_BASE + 0x88)
#define DMA2_Stream6_BASE (DMA2_BASE + 0xA0)
#define DMA2_Stream7_BASE (DMA2_BASE + 0xB8)
#define DMA2_Stream0 ((dma_stream_regs_t *)DMA2_Stream0_BASE)
#define DMA2_Stream1 ((dma_stream_regs_t *)DMA2_Stream1_BASE)
#define DMA2_Stream2 ((dma_stream_regs_t *)DMA2_Stream2_BASE)
#define DMA2_Stream3 ((dma_stream_regs_t *)DMA2_Stream3_BASE)
#define DMA2_Stream4 ((dma_stream_regs_t *)DMA2_Stream4_BASE)
#define DMA2_Stream5 ((dma_stream_regs_t *)DMA2_Stream5_BASE)
#define DMA2_Stream6 ((dma_stream_regs_t *)DMA2_Stream6_BASE)
#define DMA2_Stream7 ((dma_stream_regs_t *)DMA2_Stream7_BASE)

void DMA_ResetStream(dma_stream_regs_t *ds);



