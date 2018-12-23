#ifndef USART1_H
#define USART1_H

#include <stm32f4xx_usart.h>

void usart1_init(uint32 baudrate);

BOOL usart1_ready_read(void);
BOOL usart1_rsv_byte(uint8 *buf);
int usart1_buf_count(void);

#endif

