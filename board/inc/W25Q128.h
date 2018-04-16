#ifndef W25Q128_H
#define W25Q128_H

#define W25Q128_select()    (PBout(14) = 0)
#define W25Q128_unselect()  (PBout(14) = 1)
#define W25Q128_SPI         SPI1

void W25Q128_init(void);
uint16 W25Q128_read_id(void);

#endif
