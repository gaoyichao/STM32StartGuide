/***********************************************************
 *
 * led.h - LED������
 *
 ************************************** ���ҳ�.2017.0201 ***/
#ifndef LED_H
#define LED_H

#include <stm32f4xx_gpio.h>

#define LED_0 (PFout(9))
#define LED_1 (PFout(10))

#define LED_ON 0
#define LED_OFF 1

/*
 * led_init - ��ʼ��LED��
 */
void led_init(void);


#endif
