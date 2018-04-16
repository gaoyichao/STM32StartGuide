#pragma once

#include <types.h>

/*
 * ���ƼĴ��� SPI_CR1
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x0000
 * ����: word/half-word����
 */
#define SPI_MASTER  1
#define SPI_SLAVE   0

#define SPI_Data_Size_8b 0
#define SPI_Data_Size_16b 1

#define SPI_Prescaler_2         0
#define SPI_Prescaler_4         1
#define SPI_Prescaler_8         2
#define SPI_Prescaler_16        3
#define SPI_Prescaler_32        4
#define SPI_Prescaler_64        5
#define SPI_Prescaler_128       6
#define SPI_Prescaler_256       7
struct spi_cr1_bits {
    uint16 CPHA : 1;
    uint16 CPOL : 1;
    /* 1:Master */
    uint16 MSTR : 1;
    /* �����ʿ����� */
    uint16 BR : 3;
    /* ʹ��SPI */
    uint16 SPE : 1;
    /* �ȷ��͵�λ */
    uint16 LSBFIRST : 1;
    /* ����λSSMʱ,��λ��ֱ�ӿ���NSSλ����� */
    uint16 SSI : 1;
    /* ����Slave�豸 */
    uint16 SSM : 1;
    /* ֻ�� */
    uint16 RXONLY : 1;
    /* 0:8λ����; 1:16λ���� */
    uint16 DFF : 1;
    /* ��������ΪCRCУ�� */
    uint16 CRCNEXT : 1;
    /* ʹ��Ӳ��CRCУ�� */
    uint16 CRCEN : 1;
    /* û�� */
    uint16 BIDIE : 1;
    uint16 BIDIMODE : 1;
};
union spi_cr1 {
    struct spi_cr1_bits bits;
    uint16 all;
};
/*
 * ���ƼĴ��� SPI_CR2
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000
 * ����: word/half-word����
 */
struct spi_cr2_bits {
    uint16 RXDMAEN : 1;
    uint16 TXDMAEN : 1;
    uint16 SSOE : 1;
    uint16 rsv0 : 1;
    /* ֡��ʽ��ʽ:0,Motorolaģʽ,1,TIģʽ */
    uint16 FRF : 1;
    uint16 ERRIE : 1;
    /* ���ջ���ǿ��ж� */
    uint16 RXNEIE : 1;
    uint16 TXEIE : 1;
    uint16 rsv1 : 8;
};
union spi_cr2 {
    struct spi_cr2_bits bits;
    uint16 all;
};
/*
 * ״̬�Ĵ��� SPI_SR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000
 * ����: word/half-word����
 */
struct spi_sr_bits {
    /* ���ջ���ǿ� */
    uint16 RXNE : 1;
    /* ���ͻ���� */
    uint16 TXE : 1;
    /* SPI���� */
    uint16 CHSIDE : 1;
    /* Underrun SPI���� */
    uint16 UDR : 1;
    /* CRCУ����� */
    uint16 CRCERR : 1;
    /* SPI����ģʽ���� */
    uint16 MODF : 1;
    /* Overrun */
    uint16 OVR : 1;
    /* Busy */
    uint16 BSY : 1;
    /* ֡��ʽ���� */
    uint16 FRE : 1;
    uint16 rsv : 7;
};
union spi_sr {
    struct spi_sr_bits bits;
    uint16 all;
};
/*
 * I2S���üĴ��� I2SCFGR
 * ƫ�Ƶ�ַ: 0x1C
 * ��λֵ: 0x0000
 * ����: word/half-word����
 */
struct i2s_cfgr_bits {
    uint16 CHLEN : 1;
    uint16 DATLEN : 2;
    uint16 CKPOL : 1;
    uint16 I2SSTD : 2;
    uint16 rsv0 : 1;
    uint16 PCMSYNC : 1;
    uint16 I2SCFG : 2;
    uint16 I2SE : 1;
    uint16 I2SMOD : 1;
    uint16 rsv1 : 4;
};
union i2s_cfgr {
    struct i2s_cfgr_bits bits;
    uint16 all;
};
/*
 * I2SԤ��Ƶ�Ĵ��� I2SPR
 * ƫ�Ƶ�ַ: 0x20
 * ��λֵ: 0x0000
 * ����: word/half-word����
 */
struct i2s_pr_bits {
    uint16 I2SDIV : 8;
    uint16 ODD : 1;
    uint16 MCKOE : 1;
    uint16 rsv0 : 6;
};
union i2s_pr {
    struct i2s_pr_bits bits;
    uint16 all;
};

typedef struct spi_regs {
    volatile union spi_cr1 CR1;         /* SPI���ƼĴ���1, offset: 0x00 */
    uint16 rsv0;
    volatile union spi_cr2 CR2;         /* SPI���ƼĴ���2, offset: 0x04 */
    uint16 rsv1;
    volatile union spi_sr SR;           /* SPI״̬�Ĵ���, offset: 0x08 */
    uint16 rsv2;
    volatile uint16 DR;                 /* SPI���ݼĴ���, offset: 0x0C */
    uint16 rsv3;
    volatile uint16 CRCPR;              /* SPI CRC polynomial register, offset: 0x10 */
    uint16 rsv4;
    volatile uint16 RXCRCR;             /* SPI RX CRC register, offset: 0x14 */
    uint16 rsv5;
    volatile uint16 TXCRCR;             /* SPI TX CRC register, offset: 0x18 */
    uint16 rsv6;
    volatile union i2s_cfgr I2SCFGR;    /* I2S���üĴ���, offset: 0x1C */
    uint16 rsv7;
    volatile union i2s_pr I2SPR;        /* I2S��Ƶ�Ĵ���, offset: 0x20 */
    uint16 rsv8;
} spi_regs_t;

/* SDIO�Ĵ�����ַӳ�� */
#define SPI1_BASE 0x40013000
#define SPI2_BASE 0x40003800
#define SPI3_BASE 0x40003C00

/* SDIO�Ĵ���ָ����� */
#define SPI1 ((spi_regs_t *) SPI1_BASE)
#define SPI2 ((spi_regs_t *) SPI2_BASE)
#define SPI3 ((spi_regs_t *) SPI3_BASE)

/*
 * spi_exchange - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @data: �ֽ�����
 */
uint8 spi_exchange(spi_regs_t *spi, uint8 data);
/*
 * spi_exchange - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @buf: ��������
 * @len: ���ݳ���
 */
void spi_exchange_bytes(spi_regs_t *spi, uint8 *buf, uint16 len);
/*
 * spi_send_bytes - ����һ���ֽ�
 *
 * @spi: Ŀ��SPI�豸
 * @buf: ��������
 * @len: ���ݳ���
 */
void spi_send_bytes(spi_regs_t *spi, const uint8 *buf, uint16 len);
