#ifndef STM32F407_FLASH_H
#define STM32F407_FLASH_H

#include <types.h>


/*
 * FLASH��Կ�Ĵ��� FLASH_KEYR
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word����
 */
#define FLASH_KEYR_KEY1         ((uint32)0x45670123)
#define FLASH_KEYR_KEY2         ((uint32)0xCDEF89AB)

/*
 * FLASH״̬�Ĵ��� FLASH_SR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word/half-word/byte����
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
    uint32 BSY : 1;     /* Busy, �в������ڽ��� */
    uint32 r17_31 : 15;
};

union flash_sr {
    struct flash_sr_bits bits;
    uint32 all;
}; 

/*
 * FLASH���ƼĴ��� FLASH_CR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x8000 0000
 * ����: ��Flash����ʱ�޵ȴ�״̬, word/half-word/byte����
 */
#define FLASH_CR_PSIZE_X8   (0)
#define FLASH_CR_PSIZE_X16  (1)
#define FLASH_CR_PSIZE_X32  (2)
#define FLASH_CR_PSIZE_X64  (3)

struct flash_cr_bits {
    uint32 PG : 1;      /* ProGramming activated */
    uint32 SER : 1;     /* Sector ERase activated */
    uint32 MER : 1;     /* Mess ERase activated */
    uint32 SNB : 4;     /* ����Sector Number */
    uint32 r7 : 1;
    uint32 PSIZE : 2;   /* ѡ�������ݿ�� */
    uint32 r10_15: 6;
    uint32 STRT : 1;    /* ������д����,ֻ�������1,��SR.BSYλ���ʱ��� */
    uint32 r17_23 : 7;
    uint32 EOIPE : 1;   /* ʹ��End Of Operation�ж� */
    uint32 ERRIE : 1;   /* ʹ�ܴ����ж� */
    uint32 r26_30: 5;
    uint32 LOCK : 1;    /* д1����CR */
};
union flash_cr {
    struct flash_cr_bits bits;
    uint32 all;
};



typedef struct flash_regs {
    volatile uint32 ACR;      /* FLASH���ʿ��ƼĴ���,���ظ��ַ��ʼ��ٹ���,���õȴ�����, offset: 0x00 */
    volatile uint32 KEYR;     /* FLASH��Կ�Ĵ���,���ڶԽ����Կ��ƼĴ����ķ���,����ִ�б�̺Ͳ�д����, offset: 0x04 */
    volatile uint32 OPTKEYR;  /* FLASHѡ����Կ�Ĵ���,�������û����������н��б�̺Ͳ�д����, offset: 0x08 */
    volatile union flash_sr SR;       /* FLASH״̬�Ĵ���, �ṩ����ִ�еı�̺Ͳ�д������ִ����Ϣ, offset: 0x0C */
    volatile union flash_cr CR;       /* FLASH���ƼĴ���, ���ú�����Flash����, offset: 0x10 */
    volatile uint32 OPTCR;    /* FLASHѡ����ƼĴ���, �޸��û�ѡ���ֽ�, offset: 0x14 */
} flash_regs_t;

/* FLASH�Ĵ�����ַӳ�� */
#define FLASH_BASE 0x40023C00
/* FLASH�Ĵ���ָ����� */
#define FLASH ((flash_regs_t *) FLASH_BASE)

/*
 * FLASH���ʿ��ƼĴ��� FLASH_ACR
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word/half-word/byte����
 */
#define FLASH_ACR_RESET_VALUE   ((uint32)0x00000000)    /* ��λֵ */

#define FLASH_ACR_LATENCY       ((uint32)0x00000007)    /* ���ʵȴ�CPU������LATENCY[2:0]*/
#define FLASH_ACR_LATENCY_0     ((uint32)0x00000000)    /* 0 Wait state */
#define FLASH_ACR_LATENCY_1     ((uint32)0x00000001)    /* 1 Wait state */
#define FLASH_ACR_LATENCY_2     ((uint32)0x00000002)    /* 2 Wait state */
#define FLASH_ACR_LATENCY_3     ((uint32)0x00000003)    /* 3 Wait state */
#define FLASH_ACR_LATENCY_4     ((uint32)0x00000004)    /* 4 Wait state */
#define FLASH_ACR_LATENCY_5     ((uint32)0x00000005)    /* 5 Wait state */
#define FLASH_ACR_LATENCY_6     ((uint32)0x00000006)    /* 6 Wait state */
#define FLASH_ACR_LATENCY_7     ((uint32)0x00000007)    /* 7 Wait state */

#define FLASH_ACR_PRFTEN        ((uint32)0x00000010)    /* ʹ��ָ��Ԥȡ���� */
#define FLASH_ACR_ICEN          ((uint32)0x00000020)    /* ʹ��ָ��湦�� */
#define FLASH_ACR_DCEN          ((uint32)0x00000040)    /* ʹ�����ݻ��湦�� */
#define FLASH_ACR_ICRST         ((uint32)0x00000080)    /* Instruction Cache reset��ֻ�ڹر���ָ����ʱ��ſ���д�� */
#define FLASH_ACR_DCRST         ((uint32)0x00000100)    /* Data Cache reset, ֻ�ڹر������ݻ����ʱ��ſ���д�� */

/*
 * FLASHѡ����Կ�Ĵ��� FLASH_OPTKEYR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word����
 */
#define FLASH_OPTKEYR_KEY1         ((uint32)0x08192A3B)
#define FLASH_OPTKEYR_KEY2         ((uint32)0x4C5D6E7F)

/*
 * FLASHѡ����ƼĴ��� FLASH_OPTCR
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0FFF AAED
 * ����: ��Flash����ʱ�޵ȴ�״̬, word/half-word/byte����
 */
#define FLASH_OPTCR_RESET_VALUE     ((uint32)0x0FFFAAED)
#define FLASH_OPTCR_OPTLOCK         ((uint32)0x00000001)    /* д1����OPTCR */
#define FLASH_OPTCR_OPTSTRT         ((uint32)0x00000002)    /* ����һ���û�ѡ����� */

#define FLASH_OPTCR_BOR_LEV         ((uint32)0x0000000C)    /* BOR�ȼ��趨 */
#define FLASH_OPTCR_BOR_LEV_3       ((uint32)0x00000000)    /* Level 3 */
#define FLASH_OPTCR_BOR_LEV_2       ((uint32)0x00000004)    /* Level 2 */
#define FLASH_OPTCR_BOR_LEV_1       ((uint32)0x00000008)    /* Level 1 */
#define FLASH_OPTCR_BOR_LEV_OFF     ((uint32)0x0000000C)    /* BOR OFF */

#define FLASH_OPTCR_USER            ((uint32)0x000000E0)    /* �û�ѡ���ֽ� */
#define FLASH_OPTCR_USER_nRST_STDBY ((uint32)0x00000080)
#define FLASH_OPTCR_USER_nRST_STOP  ((uint32)0x00000040)
#define FLASH_OPTCR_USER_WDG_SW     ((uint32)0x00000020)

#define FLASH_OPTCR_RDP             ((uint32)0x0000FF00)    /* Read protect*/
#define FLASH_OPTCR_RDP_Lev0        ((uint32)0x0000AA00)    /* read protection not avtive */
#define FLASH_OPTCR_RDP_Lev1        ((uint32)0x0000BB00)    /* read protection of memories active */
#define FLASH_OPTCR_RDP_Lev2        ((uint32)0x0000CC00)    /* chip read protection active */

#define FLASH_OPTCR_nWRP            ((uint32)0x0FFF0000)    /* ��Ӧλд1�ر�sector��д���� */

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

