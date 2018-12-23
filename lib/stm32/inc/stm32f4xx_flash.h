#ifndef STM32F407_FLASH_H
#define STM32F407_FLASH_H

#include <types.h>


/*
 * FLASH密钥寄存器 FLASH_KEYR
 * 偏移地址: 0x04
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word访问
 */
#define FLASH_KEYR_KEY1         ((uint32)0x45670123)
#define FLASH_KEYR_KEY2         ((uint32)0xCDEF89AB)

/*
 * FLASH状态寄存器 FLASH_SR
 * 偏移地址: 0x0C
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word/half-word/byte访问
 */
struct flash_sr_bits {
    uint32 EOP : 1;     /* End Of oPeration */
    uint32 OPERR : 1;   /* OPeration  ERRor */
    uint32 r2_3: 2;
    uint32 WRPERR : 1;  /* WRite Protection ERRor */
    uint32 PAGERR : 1;  /* ProGramming Alignment ERRor */
    uint32 PGPERR : 1;  /* ProGramming Parallelism ERRor */
    uint32 PGSERR : 1;  /* ProGramming Sequence ERRor */
    uint32 r8_15 : 8;
    uint32 BSY : 1;     /* Busy, 有操作正在进行 */
    uint32 r17_31 : 15;
};

union flash_sr {
    struct flash_sr_bits bits;
    uint32 all;
}; 

/*
 * FLASH控制寄存器 FLASH_CR
 * 偏移地址: 0x10
 * 复位值: 0x8000 0000
 * 访问: 无Flash操作时无等待状态, word/half-word/byte访问
 */
#define FLASH_CR_PSIZE_X8   (0)
#define FLASH_CR_PSIZE_X16  (1)
#define FLASH_CR_PSIZE_X32  (2)
#define FLASH_CR_PSIZE_X64  (3)

struct flash_cr_bits {
    uint32 PG : 1;      /* ProGramming activated */
    uint32 SER : 1;     /* Sector ERase activated */
    uint32 MER : 1;     /* Mess ERase activated */
    uint32 SNB : 4;     /* 操作Sector Number */
    uint32 r7 : 1;
    uint32 PSIZE : 2;   /* 选择编程数据宽度 */
    uint32 r10_15: 6;
    uint32 STRT : 1;    /* 触发擦写操作,只能软件置1,当SR.BSY位清除时清除 */
    uint32 r17_23 : 7;
    uint32 EOIPE : 1;   /* 使能End Of Operation中断 */
    uint32 ERRIE : 1;   /* 使能错误中断 */
    uint32 r26_30: 5;
    uint32 LOCK : 1;    /* 写1锁定CR */
};
union flash_cr {
    struct flash_cr_bits bits;
    uint32 all;
};



typedef struct flash_regs {
    volatile uint32 ACR;      /* FLASH访问控制寄存器,开关各种访问加速功能,配置等待周期, offset: 0x00 */
    volatile uint32 KEYR;     /* FLASH密钥寄存器,用于对解锁对控制寄存器的访问,进而执行编程和擦写操作, offset: 0x04 */
    volatile uint32 OPTKEYR;  /* FLASH选项密钥寄存器,可以在用户配置扇区中进行编程和擦写操作, offset: 0x08 */
    volatile union flash_sr SR;       /* FLASH状态寄存器, 提供正在执行的编程和擦写操作的执行信息, offset: 0x0C */
    volatile union flash_cr CR;       /* FLASH控制寄存器, 配置和启动Flash操作, offset: 0x10 */
    volatile uint32 OPTCR;    /* FLASH选项控制寄存器, 修改用户选项字节, offset: 0x14 */
} flash_regs_t;

/* FLASH寄存器地址映射 */
#define FLASH_BASE 0x40023C00
/* FLASH寄存器指针访问 */
#define FLASH ((flash_regs_t *) FLASH_BASE)

/*
 * FLASH访问控制寄存器 FLASH_ACR
 * 偏移地址: 0x00
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word/half-word/byte访问
 */
#define FLASH_ACR_RESET_VALUE   ((uint32)0x00000000)    /* 复位值 */

#define FLASH_ACR_LATENCY       ((uint32)0x00000007)    /* 访问等待CPU周期数LATENCY[2:0]*/
#define FLASH_ACR_LATENCY_0     ((uint32)0x00000000)    /* 0 Wait state */
#define FLASH_ACR_LATENCY_1     ((uint32)0x00000001)    /* 1 Wait state */
#define FLASH_ACR_LATENCY_2     ((uint32)0x00000002)    /* 2 Wait state */
#define FLASH_ACR_LATENCY_3     ((uint32)0x00000003)    /* 3 Wait state */
#define FLASH_ACR_LATENCY_4     ((uint32)0x00000004)    /* 4 Wait state */
#define FLASH_ACR_LATENCY_5     ((uint32)0x00000005)    /* 5 Wait state */
#define FLASH_ACR_LATENCY_6     ((uint32)0x00000006)    /* 6 Wait state */
#define FLASH_ACR_LATENCY_7     ((uint32)0x00000007)    /* 7 Wait state */

#define FLASH_ACR_PRFTEN        ((uint32)0x00000010)    /* 使能指令预取功能 */
#define FLASH_ACR_ICEN          ((uint32)0x00000020)    /* 使能指令缓存功能 */
#define FLASH_ACR_DCEN          ((uint32)0x00000040)    /* 使能数据缓存功能 */
#define FLASH_ACR_ICRST         ((uint32)0x00000080)    /* Instruction Cache reset，只在关闭了指令缓存的时候才可以写入 */
#define FLASH_ACR_DCRST         ((uint32)0x00000100)    /* Data Cache reset, 只在关闭了数据缓存的时候才可以写入 */

/*
 * FLASH选项密钥寄存器 FLASH_OPTKEYR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word访问
 */
#define FLASH_OPTKEYR_KEY1         ((uint32)0x08192A3B)
#define FLASH_OPTKEYR_KEY2         ((uint32)0x4C5D6E7F)

/*
 * FLASH选项控制寄存器 FLASH_OPTCR
 * 偏移地址: 0x14
 * 复位值: 0x0FFF AAED
 * 访问: 无Flash操作时无等待状态, word/half-word/byte访问
 */
#define FLASH_OPTCR_RESET_VALUE     ((uint32)0x0FFFAAED)
#define FLASH_OPTCR_OPTLOCK         ((uint32)0x00000001)    /* 写1锁定OPTCR */
#define FLASH_OPTCR_OPTSTRT         ((uint32)0x00000002)    /* 触发一个用户选项操作 */

#define FLASH_OPTCR_BOR_LEV         ((uint32)0x0000000C)    /* BOR等级设定 */
#define FLASH_OPTCR_BOR_LEV_3       ((uint32)0x00000000)    /* Level 3 */
#define FLASH_OPTCR_BOR_LEV_2       ((uint32)0x00000004)    /* Level 2 */
#define FLASH_OPTCR_BOR_LEV_1       ((uint32)0x00000008)    /* Level 1 */
#define FLASH_OPTCR_BOR_LEV_OFF     ((uint32)0x0000000C)    /* BOR OFF */

#define FLASH_OPTCR_USER            ((uint32)0x000000E0)    /* 用户选项字节 */
#define FLASH_OPTCR_USER_nRST_STDBY ((uint32)0x00000080)
#define FLASH_OPTCR_USER_nRST_STOP  ((uint32)0x00000040)
#define FLASH_OPTCR_USER_WDG_SW     ((uint32)0x00000020)

#define FLASH_OPTCR_RDP             ((uint32)0x0000FF00)    /* Read protect*/
#define FLASH_OPTCR_RDP_Lev0        ((uint32)0x0000AA00)    /* read protection not avtive */
#define FLASH_OPTCR_RDP_Lev1        ((uint32)0x0000BB00)    /* read protection of memories active */
#define FLASH_OPTCR_RDP_Lev2        ((uint32)0x0000CC00)    /* chip read protection active */

#define FLASH_OPTCR_nWRP            ((uint32)0x0FFF0000)    /* 对应位写1关闭sector的写保护 */

/******************************************************************************/

#define FLASH_Sector_Start_0        ((uint32)0x08000000)
#define FLASH_Sector_Start_1        ((uint32)0x08004000)
#define FLASH_Sector_Start_2        ((uint32)0x08008000)
#define FLASH_Sector_Start_3        ((uint32)0x0800C000)
#define FLASH_Sector_Start_4        ((uint32)0x08010000)
#define FLASH_Sector_Start_5        ((uint32)0x08020000)
#define FLASH_Sector_Start_6        ((uint32)0x08040000)
#define FLASH_Sector_Start_7        ((uint32)0x08060000)
#define FLASH_Sector_Start_8        ((uint32)0x08080000)
#define FLASH_Sector_Start_9        ((uint32)0x080A0000)
#define FLASH_Sector_Start_10       ((uint32)0x080C0000)
#define FLASH_Sector_Start_11       ((uint32)0x080E0000)

extern const uint32 flash_sector_start_addr[12];
/******************************************************************************/


void flash_unlock(void);
void flash_lock(void);

#define flash_read_byte(addr)       (*(volatile uint8*)addr)
#define flash_read_halfword(addr)   (*(volatile uint16*)addr)
#define flash_read_word(addr)       (*(volatile uint32*)addr)
void flash_read_bytes(uint32 addr, uint8 *buf, uint32 len);

void flash_write_byte(uint32 addr, uint8 data);
void flash_write_halfword(uint32 addr, uint16 data);
void flash_write_word(uint32 addr, uint32 data);

void flash_mass_erase(void);
void flash_sector_erase(uint8 sector);

#endif

