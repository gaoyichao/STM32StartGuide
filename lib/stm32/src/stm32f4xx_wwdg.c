#include <stm32f4xx_rcc.h>
#include <stm32f4xx_wwdg.h>

uint8 _start_value;

/*
 * wwdg_init - ��ʼ�����ڿ��Ź�
 *
 * @div: ��Ƶϵ��
 * @w: ��������
 * @s: ��������ֵ
 */
void wwdg_init(uint8 div, uint8 w, uint8 s) {
    // ��WWDG������ʱ��
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

