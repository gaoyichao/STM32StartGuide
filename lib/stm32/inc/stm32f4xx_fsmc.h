/***********************************************************
 *
 * stm32f4xx_fsmc - ��̬�洢������,Flexible Static Memory Controller
 *
 ************************************** ���ҳ�.2018.0911 ***/
#ifndef STM32F4XX_FSMC_H
#define STM32F4XX_FSMC_H

#include <types.h>

#define FSMC_BCR_MWID_8b 0
#define FSMC_BCR_MWID_16b 1
struct fsmc_bcr_bits {
    // MBKEN - ʹ��memory bank
    // ����һ��δʹ�ܵ�bank������AHB���߲���һ��ERROR
    uint32 MBKEN : 1;
    // MUXEN - ��ַ/�����߻��ʹ��λ
    uint32 MUXEN : 1;
    // MTYP - �ڴ�����
    // 00: SRAM
    // 01: PSRAM(CRAM)
    // 10: NOR Flash/OneNAND Flash
    // 11: ����
    uint32 MTYP : 2;
    // MWID - �������߿��
    // 00: 8bits
    // 01: 16bits
    // 10,11: ����
    uint32 MWID : 2;
    // FACCEN - ʹ���������
    uint32 FACCEN : 1;
    uint32 r7 : 1;
    // BURSTEN - ͻ������ʹ��(Burst enable)
    uint32 BURSETN : 1;
    // WAITPOL - ��ӦNWAIT��ƽ�߼�
    // ֻ��burstģʽ�µ��ڴ���ʲ���Ч
    uint32 WAITPOL : 1;
    // WRAPMOD - �������Ƿ���һ��AHB burst wrap����λ����linear����
    // ֻ��burstģʽ�µ��ڴ���ʲ���Ч
    uint32 WRAPMOD : 1;
    // NWAIT�źű�ʶ�������ڴ�������Ƿ���Ч
    // ���߷���һ��ͬ��ģʽ(synchronous mode)��������Ҫ����һ���ȴ�״̬.
    uint32 WAITCFG : 1;
    // WREN - дʹ��
    // 0: �ر�FSMC��д����
    // 1: ��FSMC��д����
    uint32 WREN : 1;
    // WAITEN - �ȴ�ʹ��, NWAIT�źſ���
    uint32 WAITEN : 1;
    // EXTMOD - ��չģʽʹ��,�Ƿ���FSMC_BWTR�Ĵ���������
    uint32 EXTMOD : 1;
    // NWAIT�ź�
    uint32 ASYNCWAIT : 1;
    // CPSIZE - CRAMҳ��С
    // 000: No burst split when crossing page boundary
    // 001: 128 bytes
    // 010: 256 bytes
    // 011: 512 bytes
    // 100: 1024 bytes;
    // ����: ����
    uint32 CPSIZE : 3;
    // CBURSTRW - дburstʹ��
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
    // ��ַ����ʱ��,x��HCLK����
    uint32 ADDSET : 4;
    // ��ַ����ʱ��,x��HCLK����
    uint32 ADDHLD : 4;
    // ���ݽ���ʱ��, x��HCLK����
    uint32 DATAST : 8;
    // ����turnaround
    // ��write-to-read(��read-to-write)����Ľ����������һ���ӳ�, x��HCLK����
    uint32 BUSTURN : 4;
    // ʱ�ӷ�Ƶϵ��
    // 0000: ����
    // 0001: FSMC_CLK = 2 * HCLK
    // 0010: FSMC_CLK = 3 * HCLK
    // 1111: FSMC_CLK = 16 * HCLK
    uint32 CLKDIV : 4;
    // Data latency for synchronous memory
    // 0000: 2 CLK clock cycles for first burst access
    // 1111: 17 CLK clock cycles for first burst access
    uint32 DATLAT : 4;
    // ����ģʽ
    // 00: ����ģʽA
    // 01: ����ģʽB
    // 10: ����ģʽC
    // 11: ����ģʽD
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
    // ��ַ����ʱ��,x��HCLK����
    uint32 ADDSET : 4;
    // ��ַ����ʱ��,x��HCLK����
    uint32 ADDHLD : 4;
    // ���ݽ���ʱ��, x��HCLK����
    uint32 DATAST : 8;
    // ����turnaround
    // ��write-to-read(��read-to-write)����Ľ����������һ���ӳ�, x��HCLK����
    uint32 BUSTURN : 4;
    uint32 r20_27 : 8;
    // ����ģʽ
    // 00: ����ģʽA
    // 01: ����ģʽB
    // 10: ����ģʽC
    // 11: ����ģʽD
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



/* FSMC�Ĵ�����ַӳ�� */
#define FSMC_BANK1_BASE 0xA0000000
#define FSMC_BANK1E_BASE 0xA0000104
#define FSMC_BANK2_BASE 0xA0000060
#define FSMC_BANK3_BASE  0xA0000080
#define FSMC_BANK4_BASE  0xA00000A0
/* FSMC�Ĵ���ָ����� */
#define FSMC_Bank1 ((fsmc_bank1_regs_t *) FSMC_BANK1_BASE)
#define FSMC_Bank1E ((fsmc_bank1e_regs_t *) FSMC_BANK1E_BASE)
#define FSMC_Bank2 ((fsmc_bank2_3_regs_t *) FSMC_BANK2_BASE)
#define FSMC_Bank3 ((fsmc_bank2_3_regs_t *) FSMC_BANK3_BASE)
#define FSMC_Bank4 ((fsmc_bank4_regs_t *) FSMC_BANK4_BASE)

#endif
