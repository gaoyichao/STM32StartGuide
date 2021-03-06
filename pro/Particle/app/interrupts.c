#include <cortex_m4_nvic.h>
#include <cortex_m4_scb.h>

void config_interruts(void) {
    SCB->AIRCR = SCB_AIRCR_KEY_VALUE | NVIC_PGroup_1;
    
    NVIC->IPR.bits.USART1_Irq = 0x80;
    NVIC->ISER.bits.USART1_Irq = 1;
    
    NVIC->IPR.bits.CAN1_RX0_Irq = 0x80;
    NVIC->ISER.bits.CAN1_RX0_Irq = 1;

    NVIC->IPR.bits.CAN1_RX1_Irq = 0x80;
    NVIC->ISER.bits.CAN1_RX1_Irq = 1;
}
