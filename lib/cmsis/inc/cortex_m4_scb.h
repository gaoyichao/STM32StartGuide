/********************************************************************
 *
 *  System Control Block, SCB
 *
 *  ����SCB����ϸ���ݲμ�ST��˾��Cortex-M4 programming manual(PM0214)�ĵ�
 *  http://gaoyichao.com/Xiaotu/?book=mcu_stm32f407&title=cortex_m4_scb
 *
 *	���ҳ�
 *  gaoyichao_2016@126.com
 *
 *******************************************************************/
#ifndef CORTEX_M4_SCB_H
#define CORTEX_M4_SCB_H

#include <types.h>

/*
 * scb0_regs_t - ����SCB�ڵ�SCB�Ĵ���
 */
typedef struct scb0_regs {
	uint32 RESERVED0[2];  	/* ����,0x00-0x07 */
	volatile uint32 ACTLR;			/* �������ƼĴ���, offset: 0x08 */
} scb0_regs_t;
#define SCB0_BASE 0xE000E000
/* SCB0(����SCB�д󲿷ּĴ�����һ��Ĵ���)�Ĵ���ָ����� */
#define SCB0 ((scb0_regs_t *) SCB0_BASE)

/*
 * �������ƼĴ��� SCB_ACTLR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_ACTLR_RESET_VALUE	((uint32)0x00000000)        /* ��λֵ           */
#define SCB_ACTLR_DISMCYCINT	((uint32)0x00000001)        /* �ر� Multi-Cycle Interruptions */
#define SCB_ACTLR_DISDEFWBUF	((uint32)0x00000002)        /* �ر�д���� */
#define SCB_ACTLR_DISFOLD		((uint32)0x00000004)		/* �ر�IT folding */
#define SCB_ACTLR_FPCA			((uint32)0x00000100)
#define SCB_ACTLR_OOFP			((uint32)0x00000200)

typedef struct scb_regs {
	volatile uint32 CPUID;		/* Offset: 0x000 (R/ )  CPUID�����˴������İ汾�ŵ���Ϣ */
	volatile uint32 ICSR;       /* Offset: 0x004 (R/W)  �жϿ�����״̬�Ĵ��� */
	volatile uint32 VTOR;       /* Offset: 0x008 (R/W)  �ж�������ƫ�Ƶ�ַ�Ĵ��� */
	volatile uint32 AIRCR;      /* Offset: 0x00C (R/W)  Ӧ���жϺ͸�λ���ƼĴ��� */
	volatile uint32 SCR;        /* Offset: 0x010 (R/W)  ϵͳ���ƼĴ��� */
	volatile uint32 CCR;        /* Offset: 0x014 (R/W)  ���ÿ��ƼĴ��� */
	volatile uint8  SHP[12];    /* Offset: 0x018 (R/W)  ϵͳ�쳣�������ȼ��Ĵ��� */
	volatile uint32 SHCSR;      /* Offset: 0x024 (R/W)  ϵͳ�쳣������ƺ�״̬�Ĵ��� */
	volatile uint32 CFSR;       /* Offset: 0x028 (R/W)  �����ô���״̬�Ĵ��� */
	volatile uint32 HFSR;       /* Offset: 0x02C (R/W)  Ӳ������״̬�Ĵ��� */
	volatile uint32 DFSR;       /* Offset: 0x030 (R/W)  ��δ����δ����  Debug Fault Status Register */
	volatile uint32 MMFAR;      /* Offset: 0x034 (R/W)  �ڴ���ʴ����ַ�Ĵ��� */
	volatile uint32 BFAR;       /* Offset: 0x038 (R/W)  ���ߴ����ַ�Ĵ��� */
	volatile uint32 AFSR;       /* Offset: 0x03C (R/W)  ��������Ĵ���Auxiliary Fault Status Register                       */
	volatile uint32 PFR[2];     /* Offset: 0x040 (R/ )  Processor Feature Register                            */
	volatile uint32 DFR;        /* Offset: 0x048 (R/ )  Debug Feature Register                                */
	volatile uint32 ADR;        /* Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	volatile uint32 MMFR[4];    /* Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	volatile uint32 ISAR[5];    /* Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
	uint32 RESERVED0[5];
	volatile uint32 CPACR;      /* Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} scb_regs_t;
/* SCB�Ĵ�����ַӳ�� */
#define SCB_BASE  0xE000ED00
/* SCB�Ĵ���ָ����� */
#define SCB ((scb_regs_t *) SCB_BASE)

/*
 * CPU��Ϣ�Ĵ��� SCB_CPUID
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x410F C241
 * ����: Privileged
 */
#define SCB_CPUID_RESET_VALUE	((uint32)0x410FC241)        /* ��λֵ           */
#define SCB_CPUID_REVISION		((uint32)0x0000000F)        /* 0x1 �����汾��r0p1 */
#define SCB_CPUID_PARTNO		((uint32)0x0000FFF0)        /* 0xC24 Corterx-M4 */
#define SCB_CPUID_CONSTANT		((uint32)0x000F0000)		/* 0xF ������ò��ûɶ�� */
#define SCB_CPUID_VARIANT		((uint32)0x00F00000)		/* 0x0 �汾��r0p1 */
#define SCB_CPUID_IMPLEMENTER	((uint32)0xFF000000)		/* 0x41 ARM*/

/*
 * �жϿ�����״̬�Ĵ��� SCB_ICSR
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_ICSR_RESET_VALUE	((uint32)0x00000000)        /* ��λֵ           */
#define SCB_ICSR_VECTACTIVE		((uint32)0x000001FF)        /* ���ڴ�����쳣��� */
#define SCB_ICSR_RETTOBASE		((uint32)0x00000800)        /* �жϷ������Ƿ񷵻ص�base level��Ϊ0ʱ��־���Ƿ����жϱ����� */
#define SCB_ICSR_VECTPENDING	((uint32)0x0007F000)        /* ��Ҫ��������жϱ�ţ��ܵ�BASEPRI��FAULTMASK��Ӱ�죬����PRIMASK�޹� */
#define SCB_ICSR_ISRPENDING		((uint32)0x00400000)        /* ��־�ų���NMI��FAULT֮����ж��Ƿ���� */
#define SCB_ICSR_PENDSTCLR		((uint32)0x02000000)        /* �����ʱ��SysTick���жϱ�־ */
#define SCB_ICSR_PENDSTSET		((uint32)0x04000000)        /* ��λ��ʱ��SysTick���жϱ�־ */
#define SCB_ICSR_PENDSVCLR		((uint32)0x08000000)        /* ���PendSV���жϱ�־ */
#define SCB_ICSR_PENDSVSET		((uint32)0x10000000)        /* ��λPendSV���жϱ�־ */
#define SCB_ICSR_NMIPENDSET		((uint32)0x80000000)        /* ��־��NMI���� */

/*
 * �ж�������ƫ�ƼĴ��� SCB_VTOR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_VTOP_RESET_VALUE	((uint32)0x00000000)        /* ��λֵ           */
#define SCB_VTOP_TBLOFF			((uint32)0x3FFFE000)        /* ƫ�Ƶ�ַ */

/*
 * Ӧ���жϺ͸�λ���ƼĴ��� SCB_AIRCR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0xFA05 0000
 * ����: Privileged
 */
#define SCB_AIRCR_RESET_VALUE	((uint32)0xFA050000)        /* ��λֵ           */
#define SCB_AIRCR_VECTRESET		((uint32)0x00000001)        /*  */
#define SCB_AIRCR_VECTCLRACTIVE	((uint32)0x00000002)        /*  */
#define SCB_AIRCR_SYSRESETREQ	((uint32)0x00000004)        /* ϵͳ��λ���� */
#define SCB_AIRCR_PRIGROUP		((uint32)0x00000700)        /* �жϷ�������� */
#define SCB_AIRCR_ENDIANESS		((uint32)0x00008000)        /* ���ݴ�С�˴洢,Ϊ0С�˴洢 */
#define SCB_AIRCR_VECTKEY		((uint32)0xFFFF0000)        /* �ԸüĴ�����д�������뱣֤VECTKEY�ֶ�д��0x5FA,����������0xFA05 */
#define SCB_AIRCR_KEY_VALUE     ((uint32)0x05FA0000)

/*
 * ϵͳ���ƼĴ��� SCB_SCR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_SCR_RESET_VALUE		((uint32)0x00000000)        /* ��λֵ           */
#define SCB_SCR_SLEEPONEXIT		((uint32)0x00000002)        /* ���жϷ������˳��󣬿���ϵͳ����sleep����deep sleep״̬ */
#define SCB_SCR_SLEEPDEEP		((uint32)0x00000004)        /* ���ƴ�����ʹ��sleep����deep sleep״̬��Ϊ�͵�ѹģʽ��Ϊ0ʱʹ��sleepģʽ */
#define SCB_SCR_SEVEONPEND		((uint32)0x00000010)        /* Ϊ0ʱֻ��ʹ�ܵ��жϿ��Ի���ϵͳ��Ϊ1ʱ���е��ж϶����Ի���ϵͳ */

/*
 * ���ÿ��ƼĴ��� SCB_CCR
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0000 0200
 * ����: Privileged
 */
#define SCB_CCR_RESET_VALUE		((uint32)0x00000000)        /* ��λֵ           */
#define SCB_CCR_NONBASETHRDENA	((uint32)0x00000001)        /* 0:ֻ�е�û���쳣������ʱ,�ſ��Է��ص�threadģʽ;1:�κ�ʱ�򶼿���ͨ��EXC_RETURN���� */
#define SCB_CCR_USERSETMPEND	((uint32)0x00000002)		/* �Ƿ�����unprivileged�������STIR */
#define SCB_CCR_UNALIGN_TRP		((uint32)0x00000008)		/* �Ƿ�����unaligned trap */
#define SCB_CCR_DIV_0_TRP		((uint32)0x00000010)		/* �Ƿ��������trap */
#define SCB_CCR_BFHFNMIGN		((uint32)0x00000100)		/* SysTick��PendSV�ж��Ƿ������load��storeָ��������ж� */
#define SCB_CCR_STKALIGN		((uint32)0x00000200)		/* �����ж�ʱջ�ռ���뷽ʽ */

/*
 * ϵͳ�쳣������ƺ�״̬�Ĵ��� SCB_SHCSR
 * ƫ�Ƶ�ַ: 0x24
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_SHCSR_RESET_VALUE		((uint32)0x00000000)        /* ��λֵ           */
#define SCB_SHCSR_MEMFAULTACT		((uint32)0x00000001)        /* ����Memory Management Fault */
#define SCB_SHCSR_BUSFAULTACT       ((uint32)0x00000002)        /* ����Bus Fault */
#define SCB_SHCSR_USGFAULTACT		((uint32)0x00000008)        /* ����Usage Fault */
#define SCB_SHCSR_SVCALLACT			((uint32)0x00000080)        /* ����SVC Call */
#define SCB_SHCSR_MONITORACT		((uint32)0x00000100)        /* ����Debug monitor */
#define SCB_SHCSR_PENDSVACT			((uint32)0x00000400)        /* ����PendSV�ж� */
#define SCB_SHCSR_SYSTICKACT		((uint32)0x00000800)        /* ����SysTick�ж� */
#define SCB_SHCSR_USGFAULTPENDED	((uint32)0x00001000)        /* ������Usage Fault�쳣 */
#define SCB_SHCSR_MEMFAULTPENDED	((uint32)0x00002000)        /* ������Memory Management Fault�쳣 */
#define SCB_SHCSR_BUSFAULTPENDED	((uint32)0x00004000)        /* ������Bus Fault�쳣 */
#define SCB_SHCSR_SVCALLPENDED		((uint32)0x00008000)        /* ������SV Call */
#define SCB_SHCSR_MEMFAULTENA		((uint32)0x00010000)        /* ʹ��Memory management fault */
#define SCB_SHCSR_BUSFAULTENA		((uint32)0x00020000)        /* ʹ��Bus fault */
#define SCB_SHCSR_USGFAULTENA		((uint32)0x00040000)        /* ʹ��Usage fault */

/*
 * �����ô���״̬�Ĵ��� SCB_CFSR
 * ƫ�Ƶ�ַ: 0x28
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_CFSR_RESET_VALUE	((uint32)0x00000000)        /* ��λֵ           */
#define SCB_CFSR_IACCVIOL       ((uint32)0x00000001)        /* Instruction access violation. */
#define SCB_CFSR_DACCVIOL       ((uint32)0x00000002)        /* Data access violation */
#define SCB_CFSR_MUNSTKERR      ((uint32)0x00000008)        /* �˳��쳣ʱû����������ջָ�� */
#define SCB_CFSR_MSTKERR        ((uint32)0x00000010)        /* �����쳣ʱû����������ջָ�� */
#define SCB_CFSR_MLSPERR        ((uint32)0x00000020)        /* ��floating-point lazy״̬�²������ڴ���� */
#define SCB_CFSR_MMARVALID      ((uint32)0x00000080)        /* MMAR�м�¼��һ���쳣���ʵ�ַ */
#define SCB_CFSR_IBUSERR        ((uint32)0x00000100)        /* Instruction Bus Error */
#define SCB_CFSR_PRECISEERR     ((uint32)0x00000200)        /* Precise data bus error */
#define SCB_CFSR_IMPRECISEERR   ((uint32)0x00000400)        /* Imprecise data bus error */
#define SCB_CFSR_UNSTKERR       ((uint32)0x00000800)        /* ��Ϊ�˳��ж�ʱû�лָ�ջ�ռ䵼�µ����ߴ��� */
#define SCB_CFSR_STKERR         ((uint32)0x00001000)        /* ��Ϊ�����ж�ʱû�лָ�ջ�ռ䵼�µ����ߴ��� */
#define SCB_CFSR_LSPERR         ((uint32)0x00002000)        /* ��floating-point lazy״̬�²��������ߴ��� */
#define SCB_CFSR_BFARERR        ((uint32)0x00008000)        /* BFAR�м�¼�������쳣��ַ */
#define SCB_CFSR_UNDEFINERR     ((uint32)0x00010000)        /* ����������ִ��δ�����ָ�� */
#define SCB_CFSR_INVSTATE       ((uint32)0x00020000)        /* �Ƿ�����EPSR */
#define SCB_CFSR_INVPC          ((uint32)0x00040000)        /* �Ƿ�װ��PC */
#define SCB_CFSR_NOCP           ((uint32)0x00080000)        /* û��Э������ */
#define SCB_CFSR_UNALIGNED      ((uint32)0x01000000)        /* ����û�ж���ĵ�ַ */
#define SCB_CFSR_DIVBYZERO      ((uint32)0x02000000)        /* ���� */

/*
 * Ӳ������״̬�Ĵ��� SCB_HFSR
 * ƫ�Ƶ�ַ: 0x2C
 * ��λֵ: 0x0000 0000
 * ����: Privileged
 */
#define SCB_HFSR_RESET_VALUE	((uint32)0x00000000)        /* ��λֵ           */
#define SCB_HFSR_VECTTBL        ((uint32)0x00000002)        /* ��������� */
#define SCB_HFSR_FORCED         ((uint32)0x40000000)        /* ��������fault���µ�hard fault */
#define SCB_HFSR_DEBUG_VT       ((uint32)0x80000000)        /* ������Debug */







#endif
