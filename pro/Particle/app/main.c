#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>

void config_interruts(void);


/*
* tim3_init - ��ʼ��TIM3, ������������APB1��,����Ƶ�����Ϊ42MHz
*
* @pres: Ԥ��Ƶϵ��
* @period: ��������
*/
void tim3_init(uint16 pres, uint16 period) {
    RCC->APB1ENR.bits.tim3 = 1;
    TIM3->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM3->PSC = pres;
    TIM3->ARR = period;
    TIM3->EGR.bits.UG = 1;

    TIM3->DIER.bits.UIE = 1;
    TIM3->CR1.bits.CEN = 1;
}

void TIM3_IRQHandler(void) {
    if (1 == TIM3->SR.bits.UIF) {
        LED_0 = ~LED_0;
    }
    TIM3->SR.bits.UIF = 0;
}

int main(void) {
    tim3_init(42000, 1000);
    led_init();

    config_interruts();
    
    LED_0 = LED_ON;
    LED_1 = LED_ON;

    while (1) {

    }
}





