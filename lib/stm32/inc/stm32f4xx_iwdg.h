#pragma once

#include <types.h>

struct iwdg_kr_bits {
    uint16 key : 16;
    uint16 rsv : 16;
};

union iwdg_kr {
    struct iwdg_kr_bits bits;
    uint32 all;
};

#define IWDG_PR_DIV_4 0
#define IWDG_PR_DIV_8 1
#define IWDG_PR_DIV_16 2
#define IWDG_PR_DIV_32 3
#define IWDG_PR_DIV_64 4
#define IWDG_PR_DIV_128 5
#define IWDG_PR_DIV_256 6
#define IWDG_PR_DIV_MASK ((uint32)0x07)

struct iwdg_pr_bits {
    uint32 pr : 3;
    uint32 rsv : 29;
};

union iwdg_pr {
    struct iwdg_pr_bits bits;
    uint32 all;
};

#define IWDG_RLR_RL_MASK ((uint32)0x0FFF)

struct iwdg_rlr_bits {
    uint32 rl : 12;
    uint32 rsv : 20;
};

union iwdg_rlr {
    struct iwdg_rlr_bits bits;
    uint32 all;
};

struct iwdg_sr_bits {
    uint32 PVU : 1;
    uint32 RVU : 1;
    uint32 rsv : 30;
};

union iwdg_sr {
    struct iwdg_sr_bits bits;
    uint32 all;
};

typedef struct iwdg_regs {
    volatile union iwdg_kr KR;   /* IWDG Key register, offset: 0x00 */
    volatile union iwdg_pr PR;   /* IWDG Prescaler register, offset: 0x04 */
    volatile union iwdg_rlr RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
    volatile union iwdg_sr SR;   /*!< IWDG Status register,    Address offset: 0x0C */
} iwdg_regs_t;

/* IWDG¼Ä´æÆ÷µØÖ·Ó³Éä */
#define IWDG_BASE 0x40003000
/* RCC¼Ä´æÆ÷Ö¸Õë·ÃÎÊ */
#define IWDG ((iwdg_regs_t *) IWDG_BASE)


void iwdg_init(uint32 div, uint32 rl);
void iwdg_feed(void);
