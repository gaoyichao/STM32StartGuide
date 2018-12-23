#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>

void config_interruts(void);

int main(void) {
    usart1_init(115200);
    config_interruts();
    
    for (int i = 0; i < 1000; i++)
        delay(1000);

    uart_send_bytes(USART1, "Application\r\n", 13);

    uint8 cmd;
    while (1) {
        if (!usart1_rsv_byte(&cmd))
            continue;
        uart_send_byte(USART1, cmd);
    }
}
