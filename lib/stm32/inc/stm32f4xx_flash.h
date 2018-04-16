#ifndef STM32F407_FLASH_H
#define STM32F407_FLASH_H

#include <types.h>

typedef struct flash_regs {
    volatile uint32 ACR;      /* FLASH���ʿ��ƼĴ���,���ظ��ַ��ʼ��ٹ���,���õȴ�����, offset: 0x00 */
    volatile uint32 KEYR;     /* FLASH��Կ�Ĵ���,���ڶԽ����Կ��ƼĴ����ķ���,����ִ�б�̺Ͳ�д����, offset: 0x04 */
    volatile uint32 OPTKEYR;  /* FLASHѡ����Կ�Ĵ���,�������û����������н��б�̺Ͳ�д����, offset: 0x08 */
    volatile uint32 SR;       /* FLASH״̬�Ĵ���, �ṩ����ִ�еı�̺Ͳ�д������ִ����Ϣ, offset: 0x0C */
    volatile uint32 CR;       /* FLASH���ƼĴ���, ���ú�����Flash����, offset: 0x10 */
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
 * FLASH��Կ�Ĵ��� FLASH_KEYR
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word����
 */
#define FLASH_KEYR_KEY1         ((uint32)0x45670123)
#define FLASH_KEYR_KEY2         ((uint32)0xCDEF89AB)

/*
 * FLASHѡ����Կ�Ĵ��� FLASH_OPTKEYR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word����
 */
#define FLASH_OPTKEYR_KEY1         ((uint32)0x08192A3B)
#define FLASH_OPTKEYR_KEY2         ((uint32)0x4C5D6E7F)

/*
 * FLASH״̬�Ĵ��� FLASH_SR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x0000 0000
 * ����: �޵ȴ�״̬, word/half-word/byte����
 */
#define FLASH_SR_RESET_VALUE        ((uint32)0x00000000)
#define FLASH_SR_EOP                ((uint32)0x00000001)    /* End Of oPeration */
#define FLASH_SR_OPERR              ((uint32)0x00000002)    /* OPeration  ERRor */
#define FLASH_SR_WRPERR             ((uint32)0x00000010)    /* WRite Protection ERRor */
#define FLASH_SR_PGAERR             ((uint32)0x00000020)    /* ProGramming Alignment ERRor */
#define FLASH_SR_PGPERR             ((uint32)0x00000040)    /* ProGramming Parallelism ERRor */
#define FLASH_SR_PGSERR             ((uint32)0x00000080)    /* ProGramming Sequence ERRor */
#define FLASH_SR_BSY                ((uint32)0x00000100)    /* Busy, �в������ڽ��� */

/*
 * FLASH���ƼĴ��� FLASH_CR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x8000 0000
 * ����: ��Flash����ʱ�޵ȴ�״̬, word/half-word/byte����
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

#define FLASH_CR_PSIZE              ((uint32)0x00000300)    /* ѡ�������ݿ�� */
#define FLASH_CR_PSIZE_X8           ((uint32)0x00000000)
#define FLASH_CR_PSIZE_X16          ((uint32)0x00000100)
#define FLASH_CR_PSIZE_X32          ((uint32)0x00000200)
#define FLASH_CR_PSIZE_X64          ((uint32)0x00000300)

#define FLASH_CR_STRT               ((uint32)0x00010000)    /* ������д����,ֻ�������1,��SR.BSYλ���ʱ��� */
#define FLASH_CR_EOPIE              ((uint32)0x01000000)    /* ʹ��End Of Operation�ж� */
#define FLASH_CR_ERRIE              ((uint32)0x02000000)    /* ʹ�ܴ����ж� */
#define FLASH_CR_LOCK               ((uint32)0x80000000)    /* д1����CR */

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
#endif

