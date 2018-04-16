#ifndef STM32F407_FLASH_H
#define STM32F407_FLASH_H

#include <types.h>

typedef struct flash_regs {
    volatile uint32 ACR;      /* FLASH访问控制寄存器,开关各种访问加速功能,配置等待周期, offset: 0x00 */
    volatile uint32 KEYR;     /* FLASH密钥寄存器,用于对解锁对控制寄存器的访问,进而执行编程和擦写操作, offset: 0x04 */
    volatile uint32 OPTKEYR;  /* FLASH选项密钥寄存器,可以在用户配置扇区中进行编程和擦写操作, offset: 0x08 */
    volatile uint32 SR;       /* FLASH状态寄存器, 提供正在执行的编程和擦写操作的执行信息, offset: 0x0C */
    volatile uint32 CR;       /* FLASH控制寄存器, 配置和启动Flash操作, offset: 0x10 */
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
 * FLASH密钥寄存器 FLASH_KEYR
 * 偏移地址: 0x04
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word访问
 */
#define FLASH_KEYR_KEY1         ((uint32)0x45670123)
#define FLASH_KEYR_KEY2         ((uint32)0xCDEF89AB)

/*
 * FLASH选项密钥寄存器 FLASH_OPTKEYR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word访问
 */
#define FLASH_OPTKEYR_KEY1         ((uint32)0x08192A3B)
#define FLASH_OPTKEYR_KEY2         ((uint32)0x4C5D6E7F)

/*
 * FLASH状态寄存器 FLASH_SR
 * 偏移地址: 0x0C
 * 复位值: 0x0000 0000
 * 访问: 无等待状态, word/half-word/byte访问
 */
#define FLASH_SR_RESET_VALUE        ((uint32)0x00000000)
#define FLASH_SR_EOP                ((uint32)0x00000001)    /* End Of oPeration */
#define FLASH_SR_OPERR              ((uint32)0x00000002)    /* OPeration  ERRor */
#define FLASH_SR_WRPERR             ((uint32)0x00000010)    /* WRite Protection ERRor */
#define FLASH_SR_PGAERR             ((uint32)0x00000020)    /* ProGramming Alignment ERRor */
#define FLASH_SR_PGPERR             ((uint32)0x00000040)    /* ProGramming Parallelism ERRor */
#define FLASH_SR_PGSERR             ((uint32)0x00000080)    /* ProGramming Sequence ERRor */
#define FLASH_SR_BSY                ((uint32)0x00000100)    /* Busy, 有操作正在进行 */

/*
 * FLASH控制寄存器 FLASH_CR
 * 偏移地址: 0x10
 * 复位值: 0x8000 0000
 * 访问: 无Flash操作时无等待状态, word/half-word/byte访问
 */
#define FLASH_CR_RESET_VALUE        ((uint32)0x80000000)
#define FLASH_CR_PG                 ((uint32)0x00000001)    /* ProGramming activated */
#define FLASH_CR_SER                ((uint32)0x00000002)    /* Sector ERase activated */
#define FLASH_CR_MER                ((uint32)0x00000004)    /* Mess ERase activated */

#define FLASH_CR_SNB                ((uint32)0x00000078)    /* Sector Number */
#define FLASH_CR_SNB_0              ((uint32)0x00000000)    /* Sector 0 */
#define FLASH_CR_SNB_1              ((uint32)0x00000008)    /* Sector 1 */
#define FLASH_CR_SNB_2              ((uint32)0x00000010)    /* Sector 2 */
#define FLASH_CR_SNB_3              ((uint32)0x00000018)    /* Sector 3 */
#define FLASH_CR_SNB_4              ((uint32)0x00000020)    /* Sector 4 */
#define FLASH_CR_SNB_5              ((uint32)0x00000028)    /* Sector 5 */
#define FLASH_CR_SNB_6              ((uint32)0x00000030)    /* Sector 6 */
#define FLASH_CR_SNB_7              ((uint32)0x00000038)    /* Sector 7 */
#define FLASH_CR_SNB_8              ((uint32)0x00000040)    /* Sector 8 */
#define FLASH_CR_SNB_9              ((uint32)0x00000048)    /* Sector 9 */
#define FLASH_CR_SNB_a              ((uint32)0x00000050)    /* Sector 10 */
#define FLASH_CR_SNB_b              ((uint32)0x00000058)    /* Sector 11 */

#define FLASH_CR_PSIZE              ((uint32)0x00000300)    /* 选择编程数据宽度 */
#define FLASH_CR_PSIZE_X8           ((uint32)0x00000000)
#define FLASH_CR_PSIZE_X16          ((uint32)0x00000100)
#define FLASH_CR_PSIZE_X32          ((uint32)0x00000200)
#define FLASH_CR_PSIZE_X64          ((uint32)0x00000300)

#define FLASH_CR_STRT               ((uint32)0x00010000)    /* 触发擦写操作,只能软件置1,当SR.BSY位清除时清除 */
#define FLASH_CR_EOPIE              ((uint32)0x01000000)    /* 使能End Of Operation中断 */
#define FLASH_CR_ERRIE              ((uint32)0x02000000)    /* 使能错误中断 */
#define FLASH_CR_LOCK               ((uint32)0x80000000)    /* 写1锁定CR */

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
#endif

