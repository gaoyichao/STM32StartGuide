#include <stm32f407.h>
#include <W25Q128.h>

/*
 * W25Q128_init - 初始化W25Q128
 */
void W25Q128_init(void) {
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->APB2ENR.bits.spi1 = 1;
    // PB14 -> W25Q128片选
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Out;
    pincof.otype = GPIO_OType_PP;
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_High;
    gpio_init(GPIOB, GPIO_Pin_14, &pincof);
    W25Q128_unselect();
    // PB3 -> SPI1_SCK, PB4 -> SPI1_MISO, PB5 -> SPI1_MOSI
    GPIOB->AFR.bits.pin3 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin4 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin5 = GPIO_AF_SPI1;
    pincof.mode = GPIO_Mode_Af;
    gpio_init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5, &pincof);
    // SPI1配置
    SPI1->CR1.bits.SPE = 0;    // 关闭SPI外设
    SPI1->CR1.bits.MSTR = 1;
    SPI1->CR1.bits.DFF = SPI_Data_Size_8b;      // 8位
    SPI1->CR1.bits.CPHA = 1;
    SPI1->CR1.bits.CPOL = 1;
    SPI1->CR1.bits.BR = SPI_Prescaler_4;
    SPI1->CR1.bits.LSBFIRST = 0;
    SPI1->CR1.bits.SSM = 1;
    SPI1->CR1.bits.SSI = 1;
    SPI1->CR1.bits.SPE = 1;     // 开启SPI外设
}

uint16 W25Q128_read_id(void) {
    uint16 re = 0;
    W25Q128_select();
    
    spi_exchange(W25Q128_SPI, 0x90);
    spi_exchange(W25Q128_SPI, 0x00);
    spi_exchange(W25Q128_SPI, 0x00);
    spi_exchange(W25Q128_SPI, 0x00);
    
    re |= spi_exchange(W25Q128_SPI, 0xFF) << 8;
    re |= spi_exchange(W25Q128_SPI, 0xFF);
    
    W25Q128_unselect();
    return re;
}


