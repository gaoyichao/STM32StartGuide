/***********************************************************
 *
 * led.c - 三色灯驱动
 *
 ************************************** 高乙超.2017.0201 ***/
#include <stm32f407.h>
#include <led.h>
/*
 * led_init - 初始化LED灯
 */
void led_init(void) {
    RCC->AHB1ENR.bits.gpiof = 1;

    GPIOF->MODER.bits.pin9 = GPIO_Mode_Out;
    GPIOF->OTYPER.bits.pin9 = GPIO_OType_PP;    
    GPIOF->PUPDR.bits.pin9 = GPIO_Pull_Up;
    GPIOF->OSPEEDR.bits.pin9 = GPIO_OSpeed_Very_High;
    
    GPIOF->MODER.bits.pin10 = GPIO_Mode_Out;
    GPIOF->OTYPER.bits.pin10 = GPIO_OType_PP;
    GPIOF->PUPDR.bits.pin10 = GPIO_Pull_Up;
    GPIOF->OSPEEDR.bits.pin10 = GPIO_OSpeed_Very_High;

    LED_0 = LED_OFF;
    LED_1 = LED_OFF;
}
