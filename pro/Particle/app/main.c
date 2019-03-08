#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <can1.h>

void config_interruts(void);

int main(void) {
    usart1_init(115200);
    can1_init();
    
    config_interruts();
    uart_send_bytes(USART1, "douniwan\r\n", 10);

    uint8 cmd;
    while (1) {
        if (!usart1_rsv_byte(&cmd))
            continue;
        uart_send_byte(USART1, cmd);
        
        CAN1_Send_Msg();

    }
}
