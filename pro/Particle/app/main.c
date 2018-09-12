#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>

void config_interruts(void);

void led_pwmio_init(void) {
    RCC->AHB1ENR.bits.gpiof = 1;
    // 功能选择, TIM14的通道1
    GPIOF->AFR.bits.pin9 = 0x09;
    GPIOF->MODER.bits.pin9 = GPIO_Mode_Af;
    GPIOF->OTYPER.bits.pin9 = GPIO_OType_PP;
    GPIOF->PUPDR.bits.pin9 = GPIO_Pull_Up;
    GPIOF->OSPEEDR.bits.pin9 = GPIO_OSpeed_Very_High;
}

/*
* led_pwm_init - 初始化PWM控制的三色灯
*/
void led_pwm_init(void) {
    RCC->APB1ENR.bits.tim14 = 1;

    TIM14->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM14->PSC = 4999;
    TIM14->ARR = 255;
    TIM14->CR1.bits.ARPE = 1;

    union timer_chanel_mode cfg;
    cfg.oc.OCxM = TIM_OCMode_PWM2;
    cfg.oc.OCxPE = 1;
    union timer_chanel_en cen;
    cen.bits.CCxE = 1;
    cen.bits.CCxNE = 0;
    cen.bits.CCxP = 0;
    cen.bits.CCxNP = 0;

    timer_set_ccmr(TIM14, 1, cfg);
    timer_set_ccer(TIM14, 1, cen);

    TIM14->CCR1 = 0;
    TIM14->CR1.bits.CEN = 1;
}

void led_set_bright(uint8 r) {
    TIM14->CCR1 = r;
}


int main(void) {
    led_pwmio_init();
    led_pwm_init();

    config_interruts();
    
    led_set_bright(2);

    while (1) {

    }
}





