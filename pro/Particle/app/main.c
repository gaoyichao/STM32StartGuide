#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <i2c1.h>

void config_interruts(void);

void Delay(uint32 nCount) {
    for(; nCount != 0; nCount--);
}

int main(void) {
    usart1_init(115200);
    i2c1_init();

    config_interruts();

    Delay(168000000);
    
    uint8 id = i2c_read_byte(I2C1, 0x68, 0x75);
    usart1_send_bytes((uint8*)&id, 1);

    while (1) {
        
    }
}
