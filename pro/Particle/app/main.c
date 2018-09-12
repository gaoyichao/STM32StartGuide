#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>

void config_interruts(void);

void tim8_ch1_pwmio(void) {
    RCC->AHB1ENR.bits.gpioc = 1;

    GPIOC->AFR.bits.pin6 = GPIO_AF_TIM8;
    GPIOC->MODER.bits.pin6 = GPIO_Mode_Af;
    GPIOC->OTYPER.bits.pin6 = GPIO_OType_PP;
    GPIOC->PUPDR.bits.pin6 = GPIO_Pull_Up;
    GPIOC->OSPEEDR.bits.pin6 = GPIO_OSpeed_Very_High;
}

/*
* led_pwm_init - 初始化PWM控制的三色灯
*/
void tim8_ch1_pwm(void) {
    RCC->APB2ENR.bits.tim8 = 1;
    TIM8->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM8->PSC = 167;
    TIM8->ARR = 999;
    TIM8->EGR.bits.UG = 1;
    TIM8->DIER.bits.UIE = 1;

    TIM8->CR1.bits.ARPE = 1;

    union timer_chanel_mode cfg;
    cfg.oc.OCxM = TIM_OCMode_PWM2;
    cfg.oc.OCxPE = 1;
    union timer_chanel_en cen;
    cen.bits.CCxE = 1;
    cen.bits.CCxNE = 0;
    cen.bits.CCxP = 0;
    cen.bits.CCxNP = 0;

    timer_set_ccmr(TIM8, 1, cfg);
    timer_set_ccmr(TIM8, 2, cfg);
    timer_set_ccmr(TIM8, 3, cfg);

    timer_set_ccer(TIM8, 1, cen);
    timer_set_ccer(TIM8, 2, cen);
    timer_set_ccer(TIM8, 3, cen);

    TIM8->CR2.bits.OIS1 = 0;
    TIM8->CR2.bits.OIS2 = 0;
    TIM8->CR2.bits.OIS3 = 0;

    TIM8->CCR1 = 0;
    TIM8->CCR2 = 0;
    TIM8->CCR3 = 0;
    TIM8->CR1.bits.CEN = 1;
    TIM8->BDTR.bits.MOE = 1;
}

void tim1_init(void) {
    RCC->APB2ENR.bits.tim1 = 1;
    // 时机单元
    TIM1->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM1->PSC = 167;
    TIM1->ARR = 65535;
    TIM1->EGR.all |= 0x02;
    TIM1->CR1.bits.ARPE = 1;
    // PA8 : TIM1CH1
    RCC->AHB1ENR.bits.gpioa = 1;
    GPIOA->AFR.bits.pin8 = GPIO_AF_TIM1;
    GPIOA->MODER.bits.pin8 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin8 = GPIO_Pull_No;
    GPIOA->OSPEEDR.bits.pin8 = GPIO_OType_OD;
    // 输入通道
    union timer_chanel_mode cfg;
    cfg.ic.CCxS = TIM_Channel_Mode_Input1;
    cfg.ic.ICxPSC = TIM_ICMode_PSC_0;
    cfg.ic.ICxF = 0xF;
    union timer_chanel_en cen;
    cen.bits.CCxE = 1;
    cen.bits.CCxP = 0;
    cen.bits.CCxNP = 0;
    timer_set_ccmr(TIM1, 1, cfg);
    timer_set_ccer(TIM1, 1, cen);
    // 使能中断
    TIM1->DIER.bits.CC1IE = 1;
    TIM1->CR1.bits.CEN = 1;
}

uint32 gDuring = 0;
void TIM1_CC_IRQHandler(void) {
    if (1 == TIM1->SR.bits.CC1IF) {
        gDuring = TIM1->CCR1;
        TIM1->CNT = 0;
    }
    TIM1->SR.bits.CC1IF = 0;
}

uint8 gUartByte = 0;

void USART1_IRQHandler(void) {
    if (0 != USART1->SR.bits.RXNE) {
        gUartByte = USART1->DR.bits.byte;
        uart_send_byte(USART1, gUartByte);
    }
}

int main(void) {
    usart1_init(115200);
    USART1->CR1.bits.RXNEIE = 1; // 开启接收中断

    tim8_ch1_pwmio();
    tim8_ch1_pwm();
    tim1_init();

    TIM8->CCR1 = 100;

    config_interruts();
    
    uart_send_bytes(USART1, "wuhaha\r\n", 8);

    while (1) {
        switch (gUartByte) {
        case 'a':
            uart_send_bytes(USART1, (uint8*)&gDuring, 4);
            gUartByte = 0;
            break;
        }
    }
}





