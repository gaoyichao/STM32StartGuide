/***********************************************************
 *
 * stm32f407_ioafmap - IO复选功能映射
 *
 * ref: DataSheet, P61
 *
 ************************************** 高乙超.2016.1224 ***/
#ifndef STM32F407_IOIAFMAP
#define STM32F407_IOIAFMAP

#define GPIO_AF_TIM1    0x01
#define GPIO_AF_TIM2    0x01
#define GPIO_AF_TIM8    0x03
#define GPIO_AF_I2C1    0x04

#define GPIO_AF_SPI1    0x05

#define GPIO_AF_USART1  0x07
#define GPIO_AF_USART3  0x07
#define GPIO_AF_CAN1    0x09

#define GPIO_AF_UART4   0x08

#define GPIO_AF_SDIO	0x0C

#endif // !STM32F407_IOIAFMAP
