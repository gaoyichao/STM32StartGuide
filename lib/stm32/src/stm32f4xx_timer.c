/***********************************************************
 *
 * stm32f407_timer - 计时器
 *
 ************************************** 高乙超.2017.0618 ***/
#include <stm32f4xx_timer.h>

/*
 * timer_set_ccmr - 设置计时器通道,工作模式
 *
 * @tim: 计时器
 * @c: 通道
 * @cfg: 配置
 */
void timer_set_ccmr(timer_regs_t * tim, uint8 c, union timer_chanel_mode cfg) {
    switch (c) {
    case 1:
        tim->CCMR1.bytes.b13 = cfg.byte;
        break;
    case 2:
        tim->CCMR1.bytes.b24 = cfg.byte;
        break;
    case 3:
        tim->CCMR2.bytes.b13 = cfg.byte;
        break;
    case 4:
        tim->CCMR2.bytes.b24 = cfg.byte;
        break;
    default:
        tim->CCMR1.all = 0;
        tim->CCMR2.all = 0;
        break;
    }
}
/*
 * timer_set_ccer - 设置计时器通道,使能和工作电平
 *
 * @tim: 计时器
 * @c: 通道
 * @cen: 配置
 */
void timer_set_ccer(timer_regs_t * tim, uint8 c, union timer_chanel_en cen) {
    uint16 tmp = tim->CCER.all;
    c = 4 * (c - 1);
    tmp &= ~(0x000F << c);
    tmp |= (cen.all << c);
    tim->CCER.all = tmp;
}

