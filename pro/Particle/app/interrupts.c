#include <cortex_m4_nvic.h>
#include <cortex_m4_scb.h>

void config_interruts(void) {
    SCB->AIRCR = SCB_AIRCR_KEY_VALUE | NVIC_PGroup_1;

    NVIC->IPR.bits.TIM3_Irq = 0x00;
    NVIC->ISER.bits.TIM3_Irq = 1;
}
