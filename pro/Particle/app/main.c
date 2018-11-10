#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <sdio.h>
#include <utils.h>

uint8 readbuf[128];
uint8 writebuf[128];

int main(void) {
    for (int i = 0; i < 128; i++)
        writebuf[i] = i;
    
    flash_read_bytes(0x08060000, readbuf, 128);
    if (0x00 != readbuf[0]) {
        flash_unlock();
        flash_write_byte(0x08060000, 0);
        flash_lock();
        
        flash_read_bytes(0x08060000, readbuf, 128);
    }
    
    if (0x00 != readbuf[1]) {
        flash_unlock();
        flash_write_halfword(0x08060000, 0);
        flash_lock();
        
        flash_read_bytes(0x08060000, readbuf, 128);
    }

    if (0x00 != readbuf[2]) {
        flash_unlock();
        flash_write_word(0x08060000, 0);
        flash_lock();
        
        flash_read_bytes(0x08060000, readbuf, 128);
    }
    
    if (0x00 != readbuf[4]) {
        flash_unlock();
        flash_write_word(0x08060004, 0x03020100);
        flash_lock();
        
        flash_read_bytes(0x08060000, readbuf, 128);
    }
//    
//    flash_unlock();
//    flash_sector_erase(7);
//    flash_lock();
//    
//    flash_read_bytes(0x08000000, readbuf, 128);
//    flash_read_bytes(0x08060000, readbuf, 128);
//    
    while (1) {

    }
}





