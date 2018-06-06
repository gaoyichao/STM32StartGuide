#ifndef __SCCB_H
#define __SCCB_H

#include <stm32f407.h>

void sccb_init(void);

uint8 sccb_wite_reg(uint8 reg,uint8 data);
uint8 sccb_read_reg(uint8 reg);

#endif













