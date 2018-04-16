#include <stm32f4xx_iwdg.h>

#define KR_KEY_RELOAD 0xAAAA
#define KR_KEY_ENABLE 0xCCCC

/*
 * iwdg_init - 初始化独立看门狗
 *
 * @div: 分频系数
 * @rl: 重载数值
 */
void iwdg_init(uint32 div, uint32 rl) {
    IWDG->KR.bits.key = 0x5555;
    IWDG->PR.bits.pr = IWDG_PR_DIV_MASK & div;
    IWDG->RLR.bits.rl = IWDG_RLR_RL_MASK & rl;
    // 重装载计数器
    IWDG->KR.bits.key = KR_KEY_RELOAD;
    IWDG->KR.bits.key = KR_KEY_ENABLE;
}

void iwdg_feed(void) {
    IWDG->KR.bits.key = KR_KEY_RELOAD;
}
