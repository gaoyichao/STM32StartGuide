#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <sdio.h>
#include <utils.h>

#define LCD_BL (PBout(15))

void lcd_init_bl(void) {
    RCC->AHB1ENR.bits.gpiob = 1;
    
    GPIOB->MODER.bits.pin15 = GPIO_Mode_Out;
    GPIOB->OTYPER.bits.pin15 = GPIO_OType_PP;    
    GPIOB->PUPDR.bits.pin15 = GPIO_Pull_No;
    GPIOB->OSPEEDR.bits.pin15 = GPIO_OSpeed_Very_High;
}

void lcd_init_gpio(void) {
    RCC->AHB1ENR.bits.gpiod = 1;
    RCC->AHB1ENR.bits.gpioe = 1;
    RCC->AHB1ENR.bits.gpiof = 1;
    RCC->AHB1ENR.bits.gpiog = 1;
    RCC->AHB3ENR.bits.fsmc = 1;
    // 
    GPIOD->AFR.bits.pin0 = 12;  // PD0 -> FSMC_D2
 	GPIOD->AFR.bits.pin1 = 12;  // PD1 -> FSMC_D3
 	GPIOD->AFR.bits.pin4 = 12;  // PD4 -> FSMC_NOE
 	GPIOD->AFR.bits.pin5 = 12;  // PD5 -> FSMC_NWE
 	GPIOD->AFR.bits.pin8 = 12;  // PD8 -> FSMC_D13
 	GPIOD->AFR.bits.pin9 = 12;  // PD9 -> FSMC_D14
 	GPIOD->AFR.bits.pin10 = 12;	// PD10 -> FSMC_D15
 	GPIOD->AFR.bits.pin14 = 12;	// FD14 -> FSMC_D0
 	GPIOD->AFR.bits.pin15 = 12;	// PD15 -> FSMC_D1
    //
 	GPIOE->AFR.bits.pin7 = 12;  // PE7 -> FSMC_D4
 	GPIOE->AFR.bits.pin8 = 12;  // PE8 -> FSMC_D5
 	GPIOE->AFR.bits.pin9 = 12;  // PE9 -> FSMC_D6
 	GPIOE->AFR.bits.pin10 = 12;	// PE10 -> FSMC_D7
 	GPIOE->AFR.bits.pin11 = 12;	// PE11 -> FSMC_D8
 	GPIOE->AFR.bits.pin12 = 12;	// PE12 -> FSMC_D9
 	GPIOE->AFR.bits.pin13 = 12;	// PE13 -> FSMC_D10
 	GPIOE->AFR.bits.pin14 = 12;	// FE14 -> FSMC_D11
 	GPIOE->AFR.bits.pin15 = 12;	// PE15 -> FSMC_D12
    //
 	GPIOF->AFR.bits.pin12 = 12; // PF12 -> FSMC_A6
    GPIOG->AFR.bits.pin12 = 12; // PG12 -> FSMC_NE4
    
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    gpio_init(GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15, &pincof);
    gpio_init(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, &pincof);
    gpio_init(GPIOF, GPIO_Pin_12, &pincof);
    gpio_init(GPIOG, GPIO_Pin_12, &pincof);
}

void lcd_init_fsmc(void) {
    RCC->AHB3ENR.bits.fsmc = 1;
    // 寄存器清零
    FSMC_Bank1->bcr4.all = 0;
    FSMC_Bank1->btr4.all = 0;
    FSMC_Bank1E->bwtr4.all = 0;
    //
    FSMC_Bank1->bcr4.bits.WREN = 1;                     // 写使能
    FSMC_Bank1->bcr4.bits.EXTMOD = 1;                   // 使用扩展功能
    FSMC_Bank1->bcr4.bits.MWID = FSMC_BCR_MWID_16b;     // 总线宽度
    // 读时序操作
    FSMC_Bank1->btr4.bits.ACCMOD = FSMC_BTR_ACCMOD_A;   // 模式A
    FSMC_Bank1->btr4.bits.ADDSET = 15;                  // 地址建立时间15个HCLK, 15/168M ≈ 90ns
    FSMC_Bank1->btr4.bits.DATAST = 60;                  // 数据保持时间60个HCLK, 约为360ns
    // 写时序操作
    FSMC_Bank1E->bwtr4.bits.ACCMOD = FSMC_BTR_ACCMOD_A; // 模式A
    FSMC_Bank1E->bwtr4.bits.ADDSET = 9;                 // 地址建立时间9个HCLK, 约为54ns
    FSMC_Bank1E->bwtr4.bits.DATAST = 8;                 // 数据保持时间8个HCLK, 约为48ns
    // 使能Bank1,区域4
    FSMC_Bank1->bcr4.bits.MBKEN = 1;
}

struct LcdDev {
    volatile uint16 cmd;
    volatile uint16 data;
};

#define LCD_BASE ((uint32)(0x6C000000 | 0x0000007E))
#define LCD      ((struct LcdDev *) LCD_BASE)

//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(volatile uint16 regval)
{   
	regval=regval;		//使用-O2优化的时候,必须插入的延时
	LCD->cmd=regval;//写入要写的寄存器序号	 
}
//写LCD数据
//data:要写入的值
void LCD_WR_DATA(volatile uint16 data)
{	  
	data=data;			//使用-O2优化的时候,必须插入的延时
	LCD->data=data;		 
}
//读LCD数据
//返回值:读到的值
uint16 LCD_RD_DATA(void)
{
	volatile uint16 ram;			//防止被优化
	ram=LCD->data;	
	return ram;	 
}	
uint16 id;
int main(void) {
    lcd_init_bl();
    lcd_init_gpio();
    lcd_init_fsmc();
    
    delay(1680000);
    delay(1680000);
    delay(1680000);
    delay(1680000);
    
    LCD_BL = 1;
    
    LCD->cmd = 0x0400;
    id = LCD->data;
    LCD->cmd = 0x0401;
    id = (LCD->data << 8);
    LCD->cmd = 0x0402;
    id = LCD->data;
    
    LCD->cmd = 0x1100;
    delay(1680000);
    delay(1680000);
    delay(1680000);
    delay(1680000);
    LCD->cmd = 0x2900;
    delay(1680000);
    delay(1680000);
    delay(1680000);
    delay(1680000);
    
    LCD->cmd = 0x2200;  // all pixel off
    delay(1680000);
    delay(1680000);
    delay(1680000);
    delay(1680000);
    LCD->cmd = 0x2300;  // all pixel on
    
    LCD_BL = 0;

    while (1) {

    }
}





