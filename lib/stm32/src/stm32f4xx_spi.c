#include <stm32f4xx_spi.h>

/*
 * spi_exchange - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @data: �ֽ�����
 */
uint8 spi_exchange(spi_regs_t *spi, uint8 data) {
    while (0 == spi->SR.bits.TXE);
    spi->DR = data;
    while (0 == spi->SR.bits.RXNE);
    return spi->DR;
}
/*
 * spi_exchange_bytes - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @buf: ��������
 * @len: ���ݳ���
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
 * spi_send_bytes - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @buf: ��������
 * @len: ���ݳ���
 */
void spi_send_bytes(spi_regs_t *spi, const uint8 *buf, uint16 len) {
    for (int i = 0; i < len; i++) {
        while (0 == spi->SR.bits.TXE);
        spi->DR = buf[i];
        while (0 == spi->SR.bits.RXNE);
        spi->DR;
    }
}







