#include <stm32f4xx_rcc.h>
#include <stm32f4xx_wwdg.h>

uint8 _start_value;

/*
 * wwdg_init - 初始化窗口看门狗
 *
 * @div: 分频系数
 * @w: 窗口上限
 * @s: 计数器初值
 */
void wwdg_init(uint8 div, uint8 w, uint8 s) {
    // 打开WWDG的驱动时钟
    RCC->APB1ENR.bits.wwdg = 1;

    WWDG->CFR.bits.WDGTB = div;
    WWDG->CFR.bits.W = w;

    _start_value = s;
    WWDG->CR.bits.T = _start_value;
    WWDG->CR.bits.WDGA = 1;
}

void wwdg_feed(void) {
    if (WWDG->CR.bits.T < WWDG->CFR.bits.W)
        WWDG->CR.bits.T = _start_value;
}

