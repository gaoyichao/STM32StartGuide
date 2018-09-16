#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <sdio.h>
#include <utils.h>

void config_interruts(void);


struct sd_card gSDCard;
uint8 writebuf[512];
uint8 readbuf[512];

int main(void) {
    usart1_init(115200);
    USART1->CR1.bits.RXNEIE = 1; // 开启接收中断

    sdio_init(&gSDCard);
    
    config_interruts();
    
    uart_send_bytes(USART1, "wuhaha\r\n", 8);
    for (int i = 0; i < 512; i++)
		writebuf[i] = 'B';
    
    delay(4000000);
    sdio_write_block(&gSDCard, 0, writebuf);
    delay(4000000);
    sdio_read_block(&gSDCard, 0, readbuf);
	delay(4000000);
    
    for (int i = 0; i < 512; i++)
        uart_send_byte(USART1, readbuf[i]);
    
    while (1) {

    }
}





