/***********************************************************
 *
 * stm32f407_exit - 外部中断
 *
 * 0x4001 3C00 - 0x4001 3FFF, APB2
 *
 ************************************** 高乙超.2017.0111 ***/
#ifndef STM32F407_EXTI_H
#define STM32F407_EXTI_H

#include <types.h>

struct exti_register_1bit {
    uint32 tr0 : 1;
    uint32 tr1 : 1;
    uint32 tr2 : 1;
    uint32 tr3 : 1;
    uint32 tr4 : 1;
    uint32 tr5 : 1;
    uint32 tr6 : 1;
    uint32 tr7 : 1;
    uint32 tr8 : 1;
    uint32 tr9 : 1;
    uint32 tr10 : 1;
    uint32 tr11 : 1;
    uint32 tr12 : 1;
    uint32 tr13 : 1;
    uint32 tr14 : 1;
    uint32 tr15 : 1;
    uint32 tr16 : 1;
    uint32 tr17 : 1;
    uint32 tr18 : 1;
    uint32 tr19 : 1;
    uint32 tr20 : 1;
    uint32 tr21 : 1;
    uint32 tr22 : 1;
    uint32 r0 : 9;
};

union exti_register {
    struct exti_register_1bit bits;
    uint32 all;
};

typedef struct exit_regs {
    volatile union exti_register IMR;    /* EXTI中断使能寄存器, offset: 0x00 */
    volatile union exti_register EMR;    /* EXTI事件使能寄存器, offset: 0x04 */
    volatile union exti_register RTSR;   /* EXTI上升沿触发选择寄存器, offset: 0x08 */
    volatile union exti_register FTSR;   /* EXTI下降沿触发选择寄存器, offset: 0x0C */
    volatile union exti_register SWIER;  /* EXTI软件触发中断, offset: 0x10 */
    volatile union exti_register PR;     /* EXTI Pending寄存器,写1清除, offset: 0x14 */
} exit_regs_t;

#define EXTI_BASE 0x40013C00
#define EXTI ((exit_regs_t *) EXTI_BASE)

#endif // !STM32F407_EXTI_H

