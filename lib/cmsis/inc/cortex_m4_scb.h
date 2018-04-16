/********************************************************************
 *
 *  System Control Block, SCB
 *
 *  关于SCB的详细内容参见ST公司的Cortex-M4 programming manual(PM0214)文档
 *  http://gaoyichao.com/Xiaotu/?book=mcu_stm32f407&title=cortex_m4_scb
 *
 *	高乙超
 *  gaoyichao_2016@126.com
 *
 *******************************************************************/
#ifndef CORTEX_M4_SCB_H
#define CORTEX_M4_SCB_H

#include <types.h>

/*
 * scb0_regs_t - 不再SCB内的SCB寄存器
 */
typedef struct scb0_regs {
	uint32 RESERVED0[2];  	/* 保留,0x00-0x07 */
	volatile uint32 ACTLR;			/* 辅助控制寄存器, offset: 0x08 */
} scb0_regs_t;
#define SCB0_BASE 0xE000E000
/* SCB0(不与SCB中大部分寄存器在一起寄存器)寄存器指针访问 */
#define SCB0 ((scb0_regs_t *) SCB0_BASE)

/*
 * 辅助控制寄存器 SCB_ACTLR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_ACTLR_RESET_VALUE	((uint32)0x00000000)        /* 复位值           */
#define SCB_ACTLR_DISMCYCINT	((uint32)0x00000001)        /* 关闭 Multi-Cycle Interruptions */
#define SCB_ACTLR_DISDEFWBUF	((uint32)0x00000002)        /* 关闭写缓存 */
#define SCB_ACTLR_DISFOLD		((uint32)0x00000004)		/* 关闭IT folding */
#define SCB_ACTLR_FPCA			((uint32)0x00000100)
#define SCB_ACTLR_OOFP			((uint32)0x00000200)

typedef struct scb_regs {
	volatile uint32 CPUID;		/* Offset: 0x000 (R/ )  CPUID包含了处理器的版本号等信息 */
	volatile uint32 ICSR;       /* Offset: 0x004 (R/W)  中断控制与状态寄存器 */
	volatile uint32 VTOR;       /* Offset: 0x008 (R/W)  中断向量表偏移地址寄存器 */
	volatile uint32 AIRCR;      /* Offset: 0x00C (R/W)  应用中断和复位控制寄存器 */
	volatile uint32 SCR;        /* Offset: 0x010 (R/W)  系统控制寄存器 */
	volatile uint32 CCR;        /* Offset: 0x014 (R/W)  配置控制寄存器 */
	volatile uint8  SHP[12];    /* Offset: 0x018 (R/W)  系统异常服务优先级寄存器 */
	volatile uint32 SHCSR;      /* Offset: 0x024 (R/W)  系统异常服务控制和状态寄存器 */
	volatile uint32 CFSR;       /* Offset: 0x028 (R/W)  可配置错误状态寄存器 */
	volatile uint32 HFSR;       /* Offset: 0x02C (R/W)  硬件错误状态寄存器 */
	volatile uint32 DFSR;       /* Offset: 0x030 (R/W)  暂未看到未定义  Debug Fault Status Register */
	volatile uint32 MMFAR;      /* Offset: 0x034 (R/W)  内存访问错误地址寄存器 */
	volatile uint32 BFAR;       /* Offset: 0x038 (R/W)  总线错误地址寄存器 */
	volatile uint32 AFSR;       /* Offset: 0x03C (R/W)  其它错误寄存器Auxiliary Fault Status Register                       */
	volatile uint32 PFR[2];     /* Offset: 0x040 (R/ )  Processor Feature Register                            */
	volatile uint32 DFR;        /* Offset: 0x048 (R/ )  Debug Feature Register                                */
	volatile uint32 ADR;        /* Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	volatile uint32 MMFR[4];    /* Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	volatile uint32 ISAR[5];    /* Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
	uint32 RESERVED0[5];
	volatile uint32 CPACR;      /* Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} scb_regs_t;
/* SCB寄存器地址映射 */
#define SCB_BASE  0xE000ED00
/* SCB寄存器指针访问 */
#define SCB ((scb_regs_t *) SCB_BASE)

/*
 * CPU信息寄存器 SCB_CPUID
 * 偏移地址: 0x00
 * 复位值: 0x410F C241
 * 访问: Privileged
 */
#define SCB_CPUID_RESET_VALUE	((uint32)0x410FC241)        /* 复位值           */
#define SCB_CPUID_REVISION		((uint32)0x0000000F)        /* 0x1 补丁版本号r0p1 */
#define SCB_CPUID_PARTNO		((uint32)0x0000FFF0)        /* 0xC24 Corterx-M4 */
#define SCB_CPUID_CONSTANT		((uint32)0x000F0000)		/* 0xF 常数，貌似没啥用 */
#define SCB_CPUID_VARIANT		((uint32)0x00F00000)		/* 0x0 版本号r0p1 */
#define SCB_CPUID_IMPLEMENTER	((uint32)0xFF000000)		/* 0x41 ARM*/

/*
 * 中断控制与状态寄存器 SCB_ICSR
 * 偏移地址: 0x04
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_ICSR_RESET_VALUE	((uint32)0x00000000)        /* 复位值           */
#define SCB_ICSR_VECTACTIVE		((uint32)0x000001FF)        /* 正在处理的异常编号 */
#define SCB_ICSR_RETTOBASE		((uint32)0x00000800)        /* 中断服务函数是否返回到base level，为0时标志着是否有中断被抢断 */
#define SCB_ICSR_VECTPENDING	((uint32)0x0007F000)        /* 将要被处理的中断编号，受到BASEPRI和FAULTMASK的影响，但与PRIMASK无关 */
#define SCB_ICSR_ISRPENDING		((uint32)0x00400000)        /* 标志着除了NMI和FAULT之外的中断是否产生 */
#define SCB_ICSR_PENDSTCLR		((uint32)0x02000000)        /* 清除计时器SysTick的中断标志 */
#define SCB_ICSR_PENDSTSET		((uint32)0x04000000)        /* 置位计时器SysTick的中断标志 */
#define SCB_ICSR_PENDSVCLR		((uint32)0x08000000)        /* 清除PendSV的中断标志 */
#define SCB_ICSR_PENDSVSET		((uint32)0x10000000)        /* 置位PendSV的中断标志 */
#define SCB_ICSR_NMIPENDSET		((uint32)0x80000000)        /* 标志着NMI产生 */

/*
 * 中断向量表偏移寄存器 SCB_VTOR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_VTOP_RESET_VALUE	((uint32)0x00000000)        /* 复位值           */
#define SCB_VTOP_TBLOFF			((uint32)0x3FFFE000)        /* 偏移地址 */

/*
 * 应用中断和复位控制寄存器 SCB_AIRCR
 * 偏移地址: 0x0C
 * 复位值: 0xFA05 0000
 * 访问: Privileged
 */
#define SCB_AIRCR_RESET_VALUE	((uint32)0xFA050000)        /* 复位值           */
#define SCB_AIRCR_VECTRESET		((uint32)0x00000001)        /*  */
#define SCB_AIRCR_VECTCLRACTIVE	((uint32)0x00000002)        /*  */
#define SCB_AIRCR_SYSRESETREQ	((uint32)0x00000004)        /* 系统复位请求 */
#define SCB_AIRCR_PRIGROUP		((uint32)0x00000700)        /* 中断分组控制器 */
#define SCB_AIRCR_ENDIANESS		((uint32)0x00008000)        /* 数据大小端存储,为0小端存储 */
#define SCB_AIRCR_VECTKEY		((uint32)0xFFFF0000)        /* 对该寄存器的写操作必须保证VECTKEY字段写入0x5FA,读操作返回0xFA05 */
#define SCB_AIRCR_KEY_VALUE     ((uint32)0x05FA0000)

/*
 * 系统控制寄存器 SCB_SCR
 * 偏移地址: 0x10
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_SCR_RESET_VALUE		((uint32)0x00000000)        /* 复位值           */
#define SCB_SCR_SLEEPONEXIT		((uint32)0x00000002)        /* 从中断服务函数退出后，控制系统进入sleep或者deep sleep状态 */
#define SCB_SCR_SLEEPDEEP		((uint32)0x00000004)        /* 控制处理器使用sleep还是deep sleep状态作为低电压模式，为0时使用sleep模式 */
#define SCB_SCR_SEVEONPEND		((uint32)0x00000010)        /* 为0时只有使能的中断可以唤醒系统，为1时所有的中断都可以唤醒系统 */

/*
 * 配置控制寄存器 SCB_CCR
 * 偏移地址: 0x14
 * 复位值: 0x0000 0200
 * 访问: Privileged
 */
#define SCB_CCR_RESET_VALUE		((uint32)0x00000000)        /* 复位值           */
#define SCB_CCR_NONBASETHRDENA	((uint32)0x00000001)        /* 0:只有当没有异常被处理时,才可以返回到thread模式;1:任何时候都可以通过EXC_RETURN返回 */
#define SCB_CCR_USERSETMPEND	((uint32)0x00000002)		/* 是否允许unprivileged软件访问STIR */
#define SCB_CCR_UNALIGN_TRP		((uint32)0x00000008)		/* 是否允许unaligned trap */
#define SCB_CCR_DIV_0_TRP		((uint32)0x00000010)		/* 是否允许除零trap */
#define SCB_CCR_BFHFNMIGN		((uint32)0x00000100)		/* SysTick和PendSV中断是否忽略由load和store指令产生的中断 */
#define SCB_CCR_STKALIGN		((uint32)0x00000200)		/* 进入中断时栈空间对齐方式 */

/*
 * 系统异常服务控制和状态寄存器 SCB_SHCSR
 * 偏移地址: 0x24
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_SHCSR_RESET_VALUE		((uint32)0x00000000)        /* 复位值           */
#define SCB_SHCSR_MEMFAULTACT		((uint32)0x00000001)        /* 激活Memory Management Fault */
#define SCB_SHCSR_BUSFAULTACT       ((uint32)0x00000002)        /* 激活Bus Fault */
#define SCB_SHCSR_USGFAULTACT		((uint32)0x00000008)        /* 激活Usage Fault */
#define SCB_SHCSR_SVCALLACT			((uint32)0x00000080)        /* 激活SVC Call */
#define SCB_SHCSR_MONITORACT		((uint32)0x00000100)        /* 激活Debug monitor */
#define SCB_SHCSR_PENDSVACT			((uint32)0x00000400)        /* 激活PendSV中断 */
#define SCB_SHCSR_SYSTICKACT		((uint32)0x00000800)        /* 激活SysTick中断 */
#define SCB_SHCSR_USGFAULTPENDED	((uint32)0x00001000)        /* 产生了Usage Fault异常 */
#define SCB_SHCSR_MEMFAULTPENDED	((uint32)0x00002000)        /* 产生了Memory Management Fault异常 */
#define SCB_SHCSR_BUSFAULTPENDED	((uint32)0x00004000)        /* 产生了Bus Fault异常 */
#define SCB_SHCSR_SVCALLPENDED		((uint32)0x00008000)        /* 产生了SV Call */
#define SCB_SHCSR_MEMFAULTENA		((uint32)0x00010000)        /* 使能Memory management fault */
#define SCB_SHCSR_BUSFAULTENA		((uint32)0x00020000)        /* 使能Bus fault */
#define SCB_SHCSR_USGFAULTENA		((uint32)0x00040000)        /* 使能Usage fault */

/*
 * 可配置错误状态寄存器 SCB_CFSR
 * 偏移地址: 0x28
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_CFSR_RESET_VALUE	((uint32)0x00000000)        /* 复位值           */
#define SCB_CFSR_IACCVIOL       ((uint32)0x00000001)        /* Instruction access violation. */
#define SCB_CFSR_DACCVIOL       ((uint32)0x00000002)        /* Data access violation */
#define SCB_CFSR_MUNSTKERR      ((uint32)0x00000008)        /* 退出异常时没有正常处理栈指针 */
#define SCB_CFSR_MSTKERR        ((uint32)0x00000010)        /* 进入异常时没有正常处理栈指针 */
#define SCB_CFSR_MLSPERR        ((uint32)0x00000020)        /* 在floating-point lazy状态下产生的内存错误 */
#define SCB_CFSR_MMARVALID      ((uint32)0x00000080)        /* MMAR中记录了一次异常访问地址 */
#define SCB_CFSR_IBUSERR        ((uint32)0x00000100)        /* Instruction Bus Error */
#define SCB_CFSR_PRECISEERR     ((uint32)0x00000200)        /* Precise data bus error */
#define SCB_CFSR_IMPRECISEERR   ((uint32)0x00000400)        /* Imprecise data bus error */
#define SCB_CFSR_UNSTKERR       ((uint32)0x00000800)        /* 因为退出中断时没有恢复栈空间导致的总线错误 */
#define SCB_CFSR_STKERR         ((uint32)0x00001000)        /* 因为进入中断时没有恢复栈空间导致的总线错误 */
#define SCB_CFSR_LSPERR         ((uint32)0x00002000)        /* 在floating-point lazy状态下产生的总线错误 */
#define SCB_CFSR_BFARERR        ((uint32)0x00008000)        /* BFAR中记录了总线异常地址 */
#define SCB_CFSR_UNDEFINERR     ((uint32)0x00010000)        /* 处理器尝试执行未定义的指令 */
#define SCB_CFSR_INVSTATE       ((uint32)0x00020000)        /* 非法访问EPSR */
#define SCB_CFSR_INVPC          ((uint32)0x00040000)        /* 非法装载PC */
#define SCB_CFSR_NOCP           ((uint32)0x00080000)        /* 没有协处理器 */
#define SCB_CFSR_UNALIGNED      ((uint32)0x01000000)        /* 访问没有对齐的地址 */
#define SCB_CFSR_DIVBYZERO      ((uint32)0x02000000)        /* 除零 */

/*
 * 硬件错误状态寄存器 SCB_HFSR
 * 偏移地址: 0x2C
 * 复位值: 0x0000 0000
 * 访问: Privileged
 */
#define SCB_HFSR_RESET_VALUE	((uint32)0x00000000)        /* 复位值           */
#define SCB_HFSR_VECTTBL        ((uint32)0x00000002)        /* 向量表错误 */
#define SCB_HFSR_FORCED         ((uint32)0x40000000)        /* 由于其它fault导致的hard fault */
#define SCB_HFSR_DEBUG_VT       ((uint32)0x80000000)        /* 保留作Debug */







#endif
