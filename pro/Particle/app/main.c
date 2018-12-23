#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <iap_hex.h>

void config_interruts(void);

#define BOOT_FLASH_START_ADDR 0x08000000
#define APP_FLASH_START_ADDR 0x08004000

void board_set_msp(uint32 msp);

void bootloader_jump(void) {
    uint32 msp = *(uint32 *)(APP_FLASH_START_ADDR);
    uint32 reset = *(uint32 *)(APP_FLASH_START_ADDR+4);
    
    
    if((msp & 0x2FFE0000) == 0x20000000) {	
        SCB->VTOR = 0x08004000;
        
        uart_send_bytes(USART1, "Jumping......\r\n", 15);

        board_set_msp(msp);
        ((void (*)())(reset))();
    }

}



int main(void) {
    usart1_init(115200);
    config_interruts();
    uart_send_bytes(USART1, "BootLoader\r\n", 12);

    uint8 cmd;
    while (1) {
        if (!usart1_rsv_byte(&cmd))
            continue;
        uart_send_byte(USART1, cmd);

        switch (cmd) {
        case 'A':
            bootloader_jump();
            break;
        case 'B':
            IapHex_Update(&gIapHexParser);
            break;
        }
    }
}
