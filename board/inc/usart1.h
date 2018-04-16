#ifndef USART1_H
#define USART1_H

#include <stm32f4xx_usart.h>

void usart1_init(uint32 baudrate);
void usart1_send_byte(uint8 value);
void usart1_send_bytes(const uint8 *buf, uint32 len);
void usart1_send_str(const uint8 *str);


#endif

