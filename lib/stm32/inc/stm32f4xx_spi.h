#pragma once

#include <types.h>

/*
 * 控制寄存器 SPI_CR1
 * 偏移地址: 0x00
 * 复位值: 0x0000
 * 访问: word/half-word访问
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
    /* 波特率控制器 */
    uint16 BR : 3;
    /* 使能SPI */
    uint16 SPE : 1;
    /* 先发送低位 */
    uint16 LSBFIRST : 1;
    /* 当置位SSM时,该位将直接控制NSS位的输出 */
    uint16 SSI : 1;
    /* 控制Slave设备 */
    uint16 SSM : 1;
    /* 只读 */
    uint16 RXONLY : 1;
    /* 0:8位数据; 1:16位数据 */
    uint16 DFF : 1;
    /* 下针数据为CRC校验 */
    uint16 CRCNEXT : 1;
    /* 使能硬件CRC校验 */
    uint16 CRCEN : 1;
    /* 没懂 */
    uint16 BIDIE : 1;
    uint16 BIDIMODE : 1;
};
union spi_cr1 {
    struct spi_cr1_bits bits;
    uint16 all;
};
/*
 * 控制寄存器 SPI_CR2
 * 偏移地址: 0x04
 * 复位值: 0x0000
 * 访问: word/half-word访问
 */
struct spi_cr2_bits {
    uint16 RXDMAEN : 1;
    uint16 TXDMAEN : 1;
    uint16 SSOE : 1;
    uint16 rsv0 : 1;
    /* 帧格式形式:0,Motorola模式,1,TI模式 */
    uint16 FRF : 1;
    uint16 ERRIE : 1;
    /* 接收缓存非空中断 */
    uint16 RXNEIE : 1;
    uint16 TXEIE : 1;
    uint16 rsv1 : 8;
};
union spi_cr2 {
    struct spi_cr2_bits bits;
    uint16 all;
};
/*
 * 状态寄存器 SPI_SR
 * 偏移地址: 0x08
 * 复位值: 0x0000
 * 访问: word/half-word访问
 */
struct spi_sr_bits {
    /* 接收缓存非空 */
    uint16 RXNE : 1;
    /* 发送缓存空 */
    uint16 TXE : 1;
    /* SPI不用 */
    uint16 CHSIDE : 1;
    /* Underrun SPI不用 */
    uint16 UDR : 1;
    /* CRC校验错误 */
    uint16 CRCERR : 1;
    /* SPI工作模式错误 */
    uint16 MODF : 1;
    /* Overrun */
    uint16 OVR : 1;
    /* Busy */
    uint16 BSY : 1;
    /* 帧格式错误 */
    uint16 FRE : 1;
    uint16 rsv : 7;
};
union spi_sr {
    struct spi_sr_bits bits;
    uint16 all;
};
/*
 * I2S配置寄存器 I2SCFGR
 * 偏移地址: 0x1C
 * 复位值: 0x0000
 * 访问: word/half-word访问
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
 * I2S预分频寄存器 I2SPR
 * 偏移地址: 0x20
 * 复位值: 0x0000
 * 访问: word/half-word访问
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
    volatile union spi_cr1 CR1;         /* SPI控制寄存器1, offset: 0x00 */
    uint16 rsv0;
    volatile union spi_cr2 CR2;         /* SPI控制寄存器2, offset: 0x04 */
    uint16 rsv1;
    volatile union spi_sr SR;           /* SPI状态寄存器, offset: 0x08 */
    uint16 rsv2;
    volatile uint16 DR;                 /* SPI数据寄存器, offset: 0x0C */
    uint16 rsv3;
    volatile uint16 CRCPR;              /* SPI CRC polynomial register, offset: 0x10 */
    uint16 rsv4;
    volatile uint16 RXCRCR;             /* SPI RX CRC register, offset: 0x14 */
    uint16 rsv5;
    volatile uint16 TXCRCR;             /* SPI TX CRC register, offset: 0x18 */
    uint16 rsv6;
    volatile union i2s_cfgr I2SCFGR;    /* I2S配置寄存器, offset: 0x1C */
    uint16 rsv7;
    volatile union i2s_pr I2SPR;        /* I2S分频寄存器, offset: 0x20 */
    uint16 rsv8;
} spi_regs_t;

/* SDIO寄存器地址映射 */
#define SPI1_BASE 0x40013000
#define SPI2_BASE 0x40003800
#define SPI3_BASE 0x40003C00

/* SDIO寄存器指针访问 */
#define SPI1 ((spi_regs_t *) SPI1_BASE)
#define SPI2 ((spi_regs_t *) SPI2_BASE)
#define SPI3 ((spi_regs_t *) SPI3_BASE)

/*
 * spi_exchange - 交换一个字节
 *
 * @spi: 目标SPI设备
 * @data: 字节数据
 */
uint8 spi_exchange(spi_regs_t *spi, uint8 data);
/*
 * spi_exchange - 交换一个字节
 *
 * @spi: 目标SPI设备
 * @buf: 缓存数据
 * @len: 数据长度
 */
void spi_exchange_bytes(spi_regs_t *spi, uint8 *buf, uint16 len);
/*
 * spi_send_bytes - 发送一堆字节
 *
 * @spi: 目标SPI设备
 * @buf: 缓存数据
 * @len: 数据长度
 */
void spi_send_bytes(spi_regs_t *spi, const uint8 *buf, uint16 len);
