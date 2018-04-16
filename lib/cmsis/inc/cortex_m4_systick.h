#ifndef CORTEX_M4_SYSTICK_H
#define CORTEX_M4_SYSTICK_H

#include <types.h>

struct systick_ctrl_bits {
    uint32 en : 1;
    uint32 tickint : 1;
    // 驱动时钟源,1:AHB,0:AHB/8
    uint32 clksource : 1;
    uint32 r0 : 13;
    uint32 countflag : 1;
    uint32 r1 : 15;
};

union systick_ctrl {
    struct systick_ctrl_bits bits;
    uint32 all;
};

struct systick_cnt_bits {
    uint32 cnt : 24;
    uint32 r0 : 8;
};

union systick_cnt {
    struct systick_cnt_bits bits;
    uint32 all;
};

struct systick_calib_bits {
    uint32 tenms : 24;
    uint32 r0 : 6;
    uint32 skew : 1;
    uint32 noref : 1;
};

union systick_calib {
    struct systick_calib_bits bits;
    uint32 all;
};

typedef struct systick_regs {
    volatile union systick_ctrl CTRL;   /* 控制与状态寄存器, Offset: 0x000 (R/W) */
    volatile union systick_cnt LOAD;   /* 重载数寄存器, Offset: 0x004 (R/W) */
    volatile union systick_cnt VAL;    /* 当前计数寄存器, Offset: 0x008 (R/W) */
    volatile union systick_calib CALIB;  /* 校准数值寄存器, Offset: 0x00C (R/ ) */
} systick_regs_t;

/* SysTick寄存器地址映射 */
#define SYSTICK_BASE  0xE000E010
/* SysTick寄存器指针访问 */
#define SYSTICK ((systick_regs_t *) SYSTICK_BASE)


#endif // !CORTEX_M4_SYSTICK_H

