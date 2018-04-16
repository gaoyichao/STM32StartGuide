#include <stm32f4xx_i2c.h>
#include <stm32f4xx_rcc.h>

#define FLAG_MASK ((uint32)0x00FFFFFF)  /*<! I2C FLAG mask */

/*
 * i2c_reset - 重置I2C设备
 */
void i2c_reset(i2c_regs_t *i2c) {
    if (I2C1 == i2c) {
        RCC->APB1RSTR.bits.i2c1 = 1;
        RCC->APB1RSTR.bits.i2c1 = 0;
    } else if (I2C2 == i2c) {
        RCC->APB1RSTR.bits.i2c2 = 1;
        RCC->APB1RSTR.bits.i2c2 = 0;
    } else if (I2C3 == i2c) {
        RCC->APB1RSTR.bits.i2c3 = 1;
        RCC->APB1RSTR.bits.i2c3 = 0;
    }

    i2c->CR1.bits.SWRST = 1;
    i2c->CR1.bits.SWRST = 0;
}
/*
 * i2c_init - 初始化I2C
 */
void i2c_init(i2c_regs_t *i2c) {
    //
    i2c_reset(i2c);
    // i2c工作频率42MHz
    i2c->CR2.bits.FREQ = 42;
    //
    i2c->CR1.bits.PE = 0;
    // 100KHz的标准通信, 210 / 42 * 10^-6
    //I2C1->CCR.bits.F_S = 0;
    //I2C1->CCR.bits.CCR = 210;
    //I2C1->TRISE.bits.TRISE = 43;
    // 400KHz的快速通信, F/S=1,DUTY=0,CCR=1
    i2c->TRISE.bits.TRISE = 13;
    i2c->CCR.all = 0x83;
    i2c->CR1.bits.PE = 1;
    i2c->CR1.bits.ACK = 1;
    //
    i2c->OAR1.bits.add = 0xC0;
}

/*
 * i2c_check_status - 检查I2C总线状态
 *
 * @i2c: 目标总线
 * @sr: 待测状态, sr[31:16] <==> SR2, sr[15:0] <==> SR1
 */
BOOL i2c_check_status(i2c_regs_t *i2c, uint32 sr) {
    union Data32 tmp;
    tmp.half_word[0] = i2c->SR1.all;
    tmp.half_word[1] = i2c->SR2.all;
    tmp.word = tmp.word & FLAG_MASK;
    return ((sr & tmp.word) == sr) ? TRUE : FALSE;
}
/*
 * i2c_read_byte - 读取一个字节
 *
 * @i2c: I2C端口
 * @addr: 从设备地址
 * @reg: 从设备寄存器
 */
uint8 i2c_read_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg) {
    uint8 data;
    i2c_read_bytes(i2c, addr, reg, 1, &data);
    return data;
}
/*
 * i2c_read_bytes - 读取多个字节
 *
 * @i2c: I2C端口
 * @addr: 从设备地址
 * @reg: 从设备寄存器
 * @len: 数据长度
 * @buf: 缓存
 */
void i2c_read_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, uint8 *buf) {
    // 总线空闲
    while (1 == i2c->SR2.bits.BUSY);
    // 产生START,进入Master模式
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    // 发送7位地址, 发送模式
    i2c->DR = (addr << 1) | I2C_DIRECTION_TX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR_TXE_TRA));
    // 发送寄存器地址
    i2c->DR = reg;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
    // 重新产生起始位, 进入Master Receiver模式
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    i2c->DR = (addr << 1) | I2C_DIRECTION_RX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR));
    // 依次接收字节,每次接收都需要返回一个ACK
    i2c->CR1.bits.ACK = 1;
    while (len > 1) {
        while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_RXNE));
        buf[0] = i2c->DR;
        buf++; len--;
    }
    // 读最后一个字节,所以返回NACK
    i2c->CR1.bits.ACK = 0;
    i2c->CR1.bits.STOP = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_RXNE));
    buf[0] = i2c->DR;

    i2c->CR1.bits.ACK = 1;
}
/*
* i2c_write_byte - 发送一个字节
*
* @i2c: I2C端口
* @addr: 从设备地址
* @reg: 从设备寄存器
* @data: 数据
*/
void i2c_write_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 data) {
    i2c_write_bytes(i2c, addr, reg, 1, &data);
}
/*
* i2c_write_bytes - 发送多个字节
*
* @i2c: I2C端口
* @addr: 从设备地址
* @reg: 从设备寄存器
* @len: 数据长度
* @buf: 数据
*/
void i2c_write_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, const uint8 *buf) {
    // 总线空闲
    while (1 == i2c->SR2.bits.BUSY);
    // 产生START,进入Master模式
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    // 发送7位地址, 发送模式
    i2c->DR = (addr << 1) | I2C_DIRECTION_TX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR_TXE_TRA));
    // 发送寄存器地址
    i2c->DR = reg;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
    // 发送数据
    while (len--) {
        i2c->DR = buf[0];
        while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
        buf++;
    }

    i2c->CR1.bits.STOP = 1;
}

