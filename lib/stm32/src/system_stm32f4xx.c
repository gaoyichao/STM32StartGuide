#include <cortex_m4_scb.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_flash.h>

#define PLL_M 8
#define PLL_N 336
#define PLL_P 2
#define PLL_Q 7

void SystemInit(void) {
    // 设置FPU
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

    RCC->CR |= RCC_CR_HSION;
    // 重置配置、控制、中断寄存器
    RCC->CFGR.all = 0x00000000;
    RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_HSEBYP);
    RCC->PLLCFGR.all = 0x24003010;
    RCC->CIR = 0x00000000;
    // 开外部高速时钟
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    // 配置PLL时钟源、各个时钟分频
    RCC->CFGR.bits.hpre = RCC_HPRE_DIV1;
    RCC->CFGR.bits.ppre1 = RCC_PPRE_DIV4;
    RCC->CFGR.bits.ppre2 = RCC_PPRE_DIV2;
    RCC->PLLCFGR.bits.pllm = PLL_M;
    RCC->PLLCFGR.bits.plln = PLL_N;
    RCC->PLLCFGR.bits.pllp = (PLL_P >> 1) - 1;
    RCC->PLLCFGR.bits.pllsrc = RCC_PLLSRC_HSE;
    RCC->PLLCFGR.bits.pllq = PLL_Q;
    // 配置FLASH
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5;
    
    // 打开PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    // 以PLL输出作为系统时钟源
    RCC->CFGR.bits.sw = RCC_SW_PLL;
    while (RCC->CFGR.bits.sws != RCC_SW_PLL);
}
