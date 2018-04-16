#include <i2c1.h>
#include <stm32f407.h>


/*
* i2c_init - 初始化i2c端口
*
* @i2c: I2C端口
*/
void i2c1_init(void) {
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->APB1ENR.bits.i2c1 = 1;
    //
    GPIOB->AFR.bits.pin8 = GPIO_AF_I2C1;
    GPIOB->AFR.bits.pin9 = GPIO_AF_I2C1;
    //
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_OD;
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_High;
    gpio_init(GPIOB, GPIO_Pin_8 | GPIO_Pin_9, &pincof);
    // 开启
    i2c_init(I2C1);
}

