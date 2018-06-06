#include <cortex_m4_nvic.h>
#include <cortex_m4_scb.h>

void config_interruts(void) {
    SCB->AIRCR = SCB_AIRCR_KEY_VALUE | NVIC_PGroup_1;

//    NVIC->IPR.bits.USART1_Irq = 0x80;
//    NVIC->ISER.bits.USART1_Irq = 1;
    
    NVIC->IPR.bits.DMA2_Stream7_Irq = 0x80;
    NVIC->ISER.bits.DMA2_Stream7_Irq = 1;
    
    NVIC->IPR.bits.DMA2_Stream5_Irq = 0x80;
    NVIC->ISER.bits.DMA2_Stream5_Irq = 1;
    
    
    NVIC->IPR.bits.DCMI_Irq = 0x00;
    NVIC->ISER.bits.DCMI_Irq = 1;
}
