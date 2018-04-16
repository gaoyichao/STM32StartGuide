#include <stm32f4xx_spi.h>

/*
 * spi_exchange - 交换一个字节
 *
 * @spi: 目标SPI设备
 * @data: 字节数据
 */
uint8 spi_exchange(spi_regs_t *spi, uint8 data) {
    while (0 == spi->SR.bits.TXE);
    spi->DR = data;
    while (0 == spi->SR.bits.RXNE);
    return spi->DR;
}
/*
 * spi_exchange_bytes - 交换一堆字节
 *
 * @spi: 目标SPI设备
 * @buf: 缓存数据
 * @len: 数据长度
 */
void spi_exchange_bytes(spi_regs_t *spi, uint8 *buf, uint16 len) {
    for (int i = 0; i < len; i++) {
        while (0 == spi->SR.bits.TXE);
        spi->DR = buf[i];
        while (0 == spi->SR.bits.RXNE);
        buf[i] = spi->DR;
    }
}
/*
 * spi_send_bytes - 发送一堆字节
 *
 * @spi: 目标SPI设备
 * @buf: 缓存数据
 * @len: 数据长度
 */
void spi_send_bytes(spi_regs_t *spi, const uint8 *buf, uint16 len) {
    for (int i = 0; i < len; i++) {
        while (0 == spi->SR.bits.TXE);
        spi->DR = buf[i];
        while (0 == spi->SR.bits.RXNE);
        spi->DR;
    }
}







