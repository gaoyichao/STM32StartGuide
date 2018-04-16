#pragma once

#include <types.h>

struct wwdg_cr_bits {
    uint32 T : 7;
    uint32 WDGA : 1;
    uint32 rsv : 24;
};

union wwdg_cr {
    struct wwdg_cr_bits bits;
    uint32 all;
};

#define WWDG_DIV1 0
#define WWDG_DIV2 1
#define WWDG_DIV4 2
#define WWDG_DIV8 3

struct wwdg_cfr_bits {
    uint32 W : 7;
    uint32 WDGTB : 2;
    uint32 EWI : 1;
    uint32 rsv : 22;
};

union wwdg_cfr {
    struct wwdg_cfr_bits bits;
    uint32 all;
};

struct wwdg_sr_bits {
    uint32 EWIF : 1;
    uint32 rsv : 31;
};

union wwdg_sr {
    struct wwdg_sr_bits bits;
    uint32 all;
};

typedef struct wwdg_regs {
    volatile union wwdg_cr CR;   /* WWDG¿ØÖÆ¼Ä´æÆ÷, offset: 0x00 */
    volatile union wwdg_cfr CFR;  /* WWDGÅäÖÃ¼Ä´æÆ÷, offset: 0x04 */
    volatile union wwdg_sr SR;   /* WWDG×´Ì¬¼Ä´æÆ÷, offset: 0x08 */
} wwdg_regs_t;

/* IWDG¼Ä´æÆ÷µØÖ·Ó³Éä */
#define WWDG_BASE 0x40002C00
/* RCC¼Ä´æÆ÷Ö¸Õë·ÃÎÊ */
#define WWDG ((wwdg_regs_t *) WWDG_BASE)


void wwdg_init(uint8 div, uint8 w, uint8 s);
void wwdg_feed(void);

