#pragma once

#include <stm32f4xx_gpio.h>

typedef struct {
    void(*scl_h)(void);
    void(*scl_l)(void);
    void(*sda_h)(void);
    void(*sda_l)(void);
    bool(*sda)(void);
    void(*set_sda_out)(void);
    void(*set_sda_in)(void);
    void(*init)(void);
    uint16 delayus;
} i2c_dev;


void fi2c_init(i2c_dev *dev);
void fi2c_send_byte(i2c_dev *dev, uint8 data, uint8 add, uint8 reg);
void fi2c_send_bytes(i2c_dev *dev, const uint8 *buf, int len, uint8 add, uint8 reg);
void fi2c_receive_bytes(i2c_dev *dev, uint8 *buf, int len, uint8 add, uint8 reg);

