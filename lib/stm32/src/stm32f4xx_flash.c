#include <stm32f4xx_flash.h>
#include <stm32f407.h>

const uint32 flash_sector_start_addr[12] = {
    FLASH_Sector_Start_0,
    FLASH_Sector_Start_1,
    FLASH_Sector_Start_2,
    FLASH_Sector_Start_3,
    FLASH_Sector_Start_4,
    FLASH_Sector_Start_5,
    FLASH_Sector_Start_6,
    FLASH_Sector_Start_7,
    FLASH_Sector_Start_8,
    FLASH_Sector_Start_9,
    FLASH_Sector_Start_10,
    FLASH_Sector_Start_11
};
/*
 * flash_unlock - 解锁flash控制寄存器访问
 */
void flash_unlock(void)
{
    if (1 == FLASH->CR.bits.LOCK) {
        FLASH->KEYR = FLASH_KEYR_KEY1;
        FLASH->KEYR = FLASH_KEYR_KEY2;
    }
}
/*
 * flash_lock - 锁flash控制寄存器访问
 */
void flash_lock(void)
{
    FLASH->CR.bits.LOCK = 1;
}
/*
 * flash_read_bytes - 读取字节到缓存中
 */
void flash_read_bytes(uint32 addr, uint8 *buf, uint32 len)
{
    volatile uint8 *pflash = (volatile uint8 *)addr;
    for (uint32 i = 0; i < len; i++)
        buf[i] = pflash[i];
}

/*
 * flash_write_byte - 向指定地址写入字节
 */
void flash_write_byte(uint32 addr, uint8 data)
{
    // Todo: 非法地址检查
    
    while (1 == FLASH->SR.bits.BSY);
    
    FLASH->CR.bits.PSIZE = FLASH_CR_PSIZE_X8;
    FLASH->CR.bits.PG = 1;
    
    *(volatile uint8 *)addr = data;
    
    while (1 == FLASH->SR.bits.BSY);
    FLASH->CR.bits.PG = 0;
}

void flash_write_halfword(uint32 addr, uint16 data)
{
    // Todo: 非法地址检查
    
    while (1 == FLASH->SR.bits.BSY);
    
    FLASH->CR.bits.PSIZE = FLASH_CR_PSIZE_X16;
    FLASH->CR.bits.PG = 1;
    
    *(volatile uint16 *)addr = data;
    
    while (1 == FLASH->SR.bits.BSY);
    FLASH->CR.bits.PG = 0;
}

void flash_write_word(uint32 addr, uint32 data)
{
    // Todo: 非法地址检查
    
    while (1 == FLASH->SR.bits.BSY);
    
    FLASH->CR.bits.PSIZE = FLASH_CR_PSIZE_X32;
    FLASH->CR.bits.PG = 1;
    
    *(volatile uint32 *)addr = data;
    
    while (1 == FLASH->SR.bits.BSY);
    FLASH->CR.bits.PG = 0;
}

void flash_mass_erase(void)
{
    while (1 == FLASH->SR.bits.BSY);
    
    FLASH->CR.bits.PSIZE = FLASH_CR_PSIZE_X8;
    FLASH->CR.bits.MER = 1;
    FLASH->CR.bits.STRT = 1;
    
    while (1 == FLASH->SR.bits.BSY);
}

void flash_sector_erase(uint8 sector)
{
    while (1 == FLASH->SR.bits.BSY);
    
    FLASH->CR.bits.PSIZE = FLASH_CR_PSIZE_X8;
    FLASH->CR.bits.SNB = sector;
    FLASH->CR.bits.SER = 1;
    FLASH->CR.bits.STRT = 1;
    
    while (1 == FLASH->SR.bits.BSY);
}

