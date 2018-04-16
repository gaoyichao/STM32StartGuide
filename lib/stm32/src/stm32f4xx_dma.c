#include <stm32f4xx_dma.h>

void DMA_ResetStream(dma_stream_regs_t *ds) {
    ds->CR.bits.EN = 0;

    ds->CR.all = 0;
    ds->NDTR.all = 0;
    ds->PAR = 0;
    ds->M0AR = 0;
    ds->M1AR = 0;
    ds->FCR.all = 0x0021;

    switch ((uint32)ds) {
    case DMA1_Stream0_BASE:
        DMA1->LIFCR.all = DMA_Stream0_IT_MASK;
        break;
    case DMA1_Stream1_BASE:
        DMA1->LIFCR.all = DMA_Stream1_IT_MASK;
        break;
    case DMA1_Stream2_BASE:
        DMA1->LIFCR.all = DMA_Stream2_IT_MASK;
        break;
    case DMA1_Stream3_BASE:
        DMA1->LIFCR.all = DMA_Stream3_IT_MASK;
        break;
    case DMA1_Stream4_BASE:
        DMA1->HIFCR.all = DMA_Stream4_IT_MASK;
        break;
    case DMA1_Stream5_BASE:
        DMA1->HIFCR.all = DMA_Stream5_IT_MASK;
        break;
    case DMA1_Stream6_BASE:
        DMA1->HIFCR.all = DMA_Stream6_IT_MASK;
        break;
    case DMA1_Stream7_BASE:
        DMA1->HIFCR.all = DMA_Stream7_IT_MASK;
        break;
    case DMA2_Stream0_BASE:
        DMA2->LIFCR.all = DMA_Stream0_IT_MASK;
        break;
    case DMA2_Stream1_BASE:
        DMA2->LIFCR.all = DMA_Stream1_IT_MASK;
        break;
    case DMA2_Stream2_BASE:
        DMA2->LIFCR.all = DMA_Stream2_IT_MASK;
        break;
    case DMA2_Stream3_BASE:
        DMA2->LIFCR.all = DMA_Stream3_IT_MASK;
        break;
    case DMA2_Stream4_BASE:
        DMA2->HIFCR.all = DMA_Stream4_IT_MASK;
        break;
    case DMA2_Stream5_BASE:
        DMA2->HIFCR.all = DMA_Stream5_IT_MASK;
        break;
    case DMA2_Stream6_BASE:
        DMA2->HIFCR.all = DMA_Stream6_IT_MASK;
        break;
    case DMA2_Stream7_BASE:
        DMA2->HIFCR.all = DMA_Stream7_IT_MASK;
        break;
    default:
        break;
    }
}

