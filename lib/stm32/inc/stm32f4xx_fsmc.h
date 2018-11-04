/***********************************************************
 *
 * stm32f4xx_fsmc - 静态存储控制器,Flexible Static Memory Controller
 *
 ************************************** 高乙超.2018.0911 ***/
#ifndef STM32F4XX_FSMC_H
#define STM32F4XX_FSMC_H

#include <types.h>

#define FSMC_BCR_MWID_8b 0
#define FSMC_BCR_MWID_16b 1
struct fsmc_bcr_bits {
    // MBKEN - 使能memory bank
    // 访问一个未使能的bank将导致AHB总线产生一个ERROR
    uint32 MBKEN : 1;
    // MUXEN - 地址/数据线混合使能位
    uint32 MUXEN : 1;
    // MTYP - 内存类型
    // 00: SRAM
    // 01: PSRAM(CRAM)
    // 10: NOR Flash/OneNAND Flash
    // 11: 保留
    uint32 MTYP : 2;
    // MWID - 数据总线宽度
    // 00: 8bits
    // 01: 16bits
    // 10,11: 保留
    uint32 MWID : 2;
    // FACCEN - 使能闪存访问
    uint32 FACCEN : 1;
    uint32 r7 : 1;
    // BURSTEN - 突发访问使能(Burst enable)
    uint32 BURSETN : 1;
    // WAITPOL - 反应NWAIT电平逻辑
    // 只在burst模式下的内存访问才有效
    uint32 WAITPOL : 1;
    // WRAPMOD - 定义了是否拆分一个AHB burst wrap访问位两个linear访问
    // 只在burst模式下的内存访问才有效
    uint32 WRAPMOD : 1;
    // NWAIT信号标识这来自内存的数据是否有效
    // 或者访问一个同步模式(synchronous mode)的闪存需要插入一个等待状态.
    uint32 WAITCFG : 1;
    // WREN - 写使能
    // 0: 关闭FSMC的写操作
    // 1: 打开FSMC的写操作
    uint32 WREN : 1;
    // WAITEN - 等待使能, NWAIT信号控制
    uint32 WAITEN : 1;
    // EXTMOD - 扩展模式使能,是否考虑FSMC_BWTR寄存器的配置
    uint32 EXTMOD : 1;
    // NWAIT信号
    uint32 ASYNCWAIT : 1;
    // CPSIZE - CRAM页大小
    // 000: No burst split when crossing page boundary
    // 001: 128 bytes
    // 010: 256 bytes
    // 011: 512 bytes
    // 100: 1024 bytes;
    // 其它: 保留
    uint32 CPSIZE : 3;
    // CBURSTRW - 写burst使能
    uint32 CBURSTRW : 1;
    uint32 r20_31 : 12;
};
union fsmc_bcr {
    struct fsmc_bcr_bits bits;
    uint32 all;
};

#define FSMC_BTR_ACCMOD_A 0
#define FSMC_BTR_ACCMOD_B 1
#define FSMC_BTR_ACCMOD_C 2
#define FSMC_BTR_ACCMOD_D 3

struct fsmc_btr_bits {
    // 地址建立时间,x个HCLK周期
    uint32 ADDSET : 4;
    // 地址保持时间,x个HCLK周期
    uint32 ADDHLD : 4;
    // 数据建立时间, x个HCLK周期
    uint32 DATAST : 8;
    // 总线turnaround
    // 在write-to-read(和read-to-write)事务的结束部分添加一个延迟, x个HCLK周期
    uint32 BUSTURN : 4;
    // 时钟分频系数
    // 0000: 保留
    // 0001: FSMC_CLK = 2 * HCLK
    // 0010: FSMC_CLK = 3 * HCLK
    // 1111: FSMC_CLK = 16 * HCLK
    uint32 CLKDIV : 4;
    // Data latency for synchronous memory
    // 0000: 2 CLK clock cycles for first burst access
    // 1111: 17 CLK clock cycles for first burst access
    uint32 DATLAT : 4;
    // 访问模式
    // 00: 访问模式A
    // 01: 访问模式B
    // 10: 访问模式C
    // 11: 访问模式D
    uint32 ACCMOD : 2;
    uint32 r30_31 : 2;
};
union fsmc_btr {
    struct fsmc_btr_bits bits;
    uint32 all;
};

typedef struct fsmc_bank1 {
    volatile union fsmc_bcr bcr1;
    volatile union fsmc_btr btr1;
    volatile union fsmc_bcr bcr2;
    volatile union fsmc_btr btr2;
    volatile union fsmc_bcr bcr3;
    volatile union fsmc_btr btr3;
    volatile union fsmc_bcr bcr4;
    volatile union fsmc_btr btr4;
} fsmc_bank1_regs_t;

struct fsmc_bwtr_bits {
    // 地址建立时间,x个HCLK周期
    uint32 ADDSET : 4;
    // 地址保持时间,x个HCLK周期
    uint32 ADDHLD : 4;
    // 数据建立时间, x个HCLK周期
    uint32 DATAST : 8;
    // 总线turnaround
    // 在write-to-read(和read-to-write)事务的结束部分添加一个延迟, x个HCLK周期
    uint32 BUSTURN : 4;
    uint32 r20_27 : 8;
    // 访问模式
    // 00: 访问模式A
    // 01: 访问模式B
    // 10: 访问模式C
    // 11: 访问模式D
    uint32 ACCMOD : 2;
    uint32 r30_31 : 2;
};

union fsmc_bwtr {
    struct fsmc_bwtr_bits bits;
    uint32 all;
};

typedef struct fsmc_bank1e {
    volatile union fsmc_bwtr bwtr1;
    uint32 r1;
    volatile union fsmc_bwtr bwtr2;
    uint32 r2;
    volatile union fsmc_bwtr bwtr3;
    uint32 r3;
    volatile union fsmc_bwtr bwtr4;
    uint32 r4;
} fsmc_bank1e_regs_t;

struct fsmc_pcr_bits {
    uint32 r0 : 1;
    uint32 PWAITEN : 1;
    uint32 PBKEN : 1;
    uint32 PTYP : 1;
    uint32 PWID : 2;
    uint32 ECCEN : 1;
    uint32 r7_8 : 2;
    uint32 TCLR : 4;
    uint32 TAR : 4;
    uint32 ECCPS : 3;
    uint32 r20_31 : 12;
};

union fsmc_pcr {
    struct fsmc_pcr_bits bits;
    uint32 all;
};

struct fsmc_sr_bits {
    uint32 IRS : 1;
    uint32 ILS : 1;
    uint32 IFS : 1;
    uint32 IREN : 1;
    uint32 ILEN : 1;
    uint32 IFEN : 1;
    uint32 FEMPT : 1;
    uint32 r7_31 : 25;
};

union fsmc_sr {
    struct fsmc_sr_bits bits;
    uint32 all;
};

struct fsmc_pmem_bits {
    uint32 MEMSET : 8;
    uint32 MEMWAIT : 8;
    uint32 MEMHOLD : 8;
    uint32 MEMHIZ : 8;
};

union fsmc_pmem {
    struct fsmc_pmem_bits bits;
    uint32 all;
};

struct fsmc_patt_bits {
    uint32 ATTSET : 8;
    uint32 ATTWAIT : 8;
    uint32 ATTHOLD : 8;
    uint32 ATTHIZ : 8;
};

union fsmc_patt {
    struct fsmc_patt_bits bits;
    uint32 all;
};

struct fsmc_pio_bits {
    uint32 IOSET : 8;
    uint32 IOWAIT : 8;
    uint32 IOHOLD : 8;
    uint32 IOHIZ : 8;
};

union fsmc_pio {
    struct fsmc_pio_bits bits;
    uint32 all;
};

typedef struct fsmc_bank2_3 {
    volatile union fsmc_pcr PCR;       /*!< NAND Flash control register 2,                       Address offset: 0x60 */
    volatile union fsmc_sr SR;        /*!< NAND Flash FIFO status and interrupt register 2,     Address offset: 0x64 */
    volatile union fsmc_pmem PMEM;      /*!< NAND Flash Common memory space timing register 2,    Address offset: 0x68 */
    volatile union fsmc_patt PATT;      /*!< NAND Flash Attribute memory space timing register 2, Address offset: 0x6C */
    uint32 RESERVED0;  /*!< Reserved, 0x70                                                            */
    volatile uint32 ECCR;      /*!< NAND Flash ECC result registers 2,                   Address offset: 0x74 */
} fsmc_bank2_3_regs_t;

typedef struct fsmc_bank4 {
    volatile union fsmc_pcr PCR;       /*!< NAND Flash control register 2,                       Address offset: 0x60 */
    volatile union fsmc_sr SR;        /*!< NAND Flash FIFO status and interrupt register 2,     Address offset: 0x64 */
    volatile union fsmc_pmem PMEM;      /*!< NAND Flash Common memory space timing register 2,    Address offset: 0x68 */
    volatile union fsmc_patt PATT;      /*!< NAND Flash Attribute memory space timing register 2, Address offset: 0x6C */
    volatile union fsmc_pio PIO;
} fsmc_bank4_regs_t;



/* FSMC寄存器地址映射 */
#define FSMC_BANK1_BASE 0xA0000000
#define FSMC_BANK1E_BASE 0xA0000104
#define FSMC_BANK2_BASE 0xA0000060
#define FSMC_BANK3_BASE  0xA0000080
#define FSMC_BANK4_BASE  0xA00000A0
/* FSMC寄存器指针访问 */
#define FSMC_Bank1 ((fsmc_bank1_regs_t *) FSMC_BANK1_BASE)
#define FSMC_Bank1E ((fsmc_bank1e_regs_t *) FSMC_BANK1E_BASE)
#define FSMC_Bank2 ((fsmc_bank2_3_regs_t *) FSMC_BANK2_BASE)
#define FSMC_Bank3 ((fsmc_bank2_3_regs_t *) FSMC_BANK3_BASE)
#define FSMC_Bank4 ((fsmc_bank4_regs_t *) FSMC_BANK4_BASE)

#endif
