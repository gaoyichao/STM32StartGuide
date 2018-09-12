#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>
#include <ov2640.h>
#include <dcmi.h>

void config_interruts(void);

void fsmc_sram_init_gpio(void) {
    RCC->AHB1ENR.bits.gpiod = 1;
    RCC->AHB1ENR.bits.gpioe = 1;
    RCC->AHB1ENR.bits.gpiof = 1;
    RCC->AHB1ENR.bits.gpiog = 1;
    
    RCC->AHB3ENR.bits.fsmc = 1;
    
    GPIOG->AFR.bits.pin10 = 12; // PG10 -> FSMC_NE3,CE, 片选信号
    GPIOD->AFR.bits.pin4 = 12;  // PD4  -> FSMC_NOE, 读使能
    GPIOD->AFR.bits.pin5 = 12;  // PD5  -> FSMC_NWE, 写使能
    GPIOE->AFR.bits.pin0 = 12;  // PE0  -> FSMC_NBL0,LB, 低字节使能
    GPIOE->AFR.bits.pin1 = 12;  // PE1  -> FSMC_NBL1,UB, 高字节使能
    
    GPIOD->AFR.bits.pin14 = 12; // PD14 -> FSMC_D0
    GPIOD->AFR.bits.pin15 = 12; // PD15 -> FSMC_D1
    GPIOD->AFR.bits.pin0 = 12;  // PD0  -> FSMC_D2
    GPIOD->AFR.bits.pin1 = 12;  // PD1  -> FSMC_D3
    GPIOE->AFR.bits.pin7 = 12;  // PE7  -> FSMC_D4
    GPIOE->AFR.bits.pin8 = 12;  // PE8  -> FSMC_D5
    GPIOE->AFR.bits.pin9 = 12;  // PE9  -> FSMC_D6
    GPIOE->AFR.bits.pin10 = 12; // PE10 -> FSMC_D7
    GPIOE->AFR.bits.pin11 = 12; // PE11 -> FSMC_D8
    GPIOE->AFR.bits.pin12 = 12; // PE12 -> FSMC_D9
    GPIOE->AFR.bits.pin13 = 12; // PE13 -> FSMC_D10
    GPIOE->AFR.bits.pin14 = 12; // PE14 -> FSMC_D11
    GPIOE->AFR.bits.pin15 = 12; // PE15 -> FSMC_D12
    GPIOD->AFR.bits.pin8 = 12;  // PD8  -> FSMC_D13
    GPIOD->AFR.bits.pin9 = 12;  // PD9  -> FSMC_D14
    GPIOD->AFR.bits.pin10 = 12; // PD10 -> FSMC_D15
    
    GPIOF->AFR.bits.pin0 = 12;  // PF0  -> FSMC_A0
    GPIOF->AFR.bits.pin1 = 12;  // PF1  -> FSMC_A1
    GPIOF->AFR.bits.pin2 = 12;  // PF2  -> FSMC_A2
    GPIOF->AFR.bits.pin3 = 12;  // PF3  -> FSMC_A3
    GPIOF->AFR.bits.pin4 = 12;  // PF4  -> FSMC_A4
    GPIOF->AFR.bits.pin5 = 12;  // PF5  -> FSMC_A5
    GPIOF->AFR.bits.pin12 = 12; // PF12 -> FSMC_A6
    GPIOF->AFR.bits.pin13 = 12; // PF13 -> FSMC_A7
    GPIOF->AFR.bits.pin14 = 12; // PF14 -> FSMC_A8
    GPIOF->AFR.bits.pin15 = 12; // PF15 -> FSMC_A9
    GPIOG->AFR.bits.pin0 = 12;  // PG0  -> FSMC_A10
    GPIOG->AFR.bits.pin1 = 12;  // PG1  -> FSMC_A11
    GPIOG->AFR.bits.pin2 = 12;  // PG2  -> FSMC_A12
    GPIOG->AFR.bits.pin3 = 12;  // PG3  -> FSMC_A13
    GPIOG->AFR.bits.pin4 = 12;  // PG4  -> FSMC_A14
    GPIOG->AFR.bits.pin5 = 12;  // PG5  -> FSMC_A15
    GPIOD->AFR.bits.pin11 = 12; // PD11 -> FSMC_A16
    GPIOD->AFR.bits.pin12 = 12; // PD12 -> FSMC_A17
    GPIOD->AFR.bits.pin13 = 12; // PD13 -> FSMC_A18
    
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    // PD0,1,4,5,8~15
    gpio_init(GPIOD, (3<<0)|(3<<4)|(0XFF<<8), &pincof);
    // PE0,1,7~15
    gpio_init(GPIOE, (3<<0)|(0X1FF<<7), &pincof);
    // PF0~5,12~15
    gpio_init(GPIOF, (0X3F<<0)|(0XF<<12), &pincof);
    // PG0~5,10
    gpio_init(GPIOG, (0X3F<<0) | GPIO_Pin_10, &pincof);
}

void fsmc_sram_init(void) {
    fsmc_sram_init_gpio();
    // 寄存器清零
    FSMC_Bank1->bcr3.all = 0;
    FSMC_Bank1->btr3.all = 0;
    FSMC_Bank1E->bwtr3.all = 0;
    // 使用异步模式A(读写共用一个时序寄存器)
    FSMC_Bank1->bcr3.bits.MWID = FSMC_BCR_MWID_16b;
    FSMC_Bank1->bcr3.bits.WREN = 1;
    FSMC_Bank1->btr3.bits.DATAST = 8;
    FSMC_Bank1->btr3.bits.ADDHLD = 0;
    FSMC_Bank1->btr3.bits.ADDSET = 0;
    
    FSMC_Bank1E->bwtr3.all = 0x0FFFFFFF;
    FSMC_Bank1->bcr3.bits.MBKEN = 1;
}

uint32 testbuf[100] __attribute__((at(0X68000000)));
uint32 *testptr = testbuf;

int main(void) {
    usart1_init(115200);
    usart1_init_dma();
    led_init();
    fsmc_sram_init();

    config_interruts();
    LED_0 = LED_ON;
    LED_1 = LED_ON;
    
    for (int i = 0; i < 100; i++)
        testbuf[i] = i;
    
    for (int i = 0; i < 100; i++) {
        if (i != testptr[i]) {
            uart_send_byte(USART1, 'E');
            LED_0 = LED_OFF;
        } else {
            uart_send_byte(USART1, 'Y');
        }
    }
    
    while (1) {

    }
}





