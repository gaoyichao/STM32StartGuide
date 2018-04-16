#include <stm32f4xx_gpio.h>

void gpio_init(gpio_regs_t *GPIOx, const uint16 pins, const struct gpio_pin_conf *conf) {
    for (uint8 i = 0; i < 0x10; i++) {
        uint16 pin = ((uint16)0x01) << i;
        if (pin & pins) {
            GPIOx->MODER.all &= ~((uint32)(0x03) << (2 * i));
            GPIOx->MODER.all |= ((uint32)((conf->mode) << (2 * i)));

            GPIOx->PUPDR.all &= ~((uint32)(0x03) << (2 * i));
            GPIOx->PUPDR.all |= ((uint32)((conf->pull) << (2 * i)));

            if (GPIO_Mode_Af == conf->mode || GPIO_Mode_Out == conf->mode) {
                GPIOx->OSPEEDR.all &= ~((uint32)(0x03) << (2 * i));
                GPIOx->OSPEEDR.all |= ((uint32)((conf->speed) << (2 *i)));

                GPIOx->OTYPER.all &= ~((uint32)(0x01) << i);
                GPIOx->OTYPER.all |= ((uint32)((conf->otype) << i));
            }
        }
    }
}


