#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <i2c1.h>

void config_interruts(void);

void Delay(uint32 nCount) {
    for(; nCount != 0; nCount--);
}

uint8 wuhaha[6] = "12345";
extern uint8 _usart1_received_datas;

int main(void) {
    usart1_init(115200);
    usart1_init_dma();
    i2c1_init();

    config_interruts();

    Delay(1680000);
    
    uint8 id = i2c_read_byte(I2C1, 0x68, 0x75);

    usart1_send_bytes_dma("laiyadouniwa\n", 13);
    usart1_send_bytes_dma("laiyadouniwa\n", 13);
    
    usart1_receive_bytes_dma(wuhaha, 5);
    
    while (1) {
        if (_usart1_received_datas) {
            usart1_send_bytes_dma(wuhaha, 5);
            _usart1_received_datas = 0;
            usart1_receive_bytes_dma(wuhaha, 5);
        }
    }
}





