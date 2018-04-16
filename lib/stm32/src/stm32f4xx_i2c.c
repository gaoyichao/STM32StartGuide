#include <stm32f4xx_i2c.h>
#include <stm32f4xx_rcc.h>

#define FLAG_MASK ((uint32)0x00FFFFFF)  /*<! I2C FLAG mask */

/*
 * i2c_reset - ����I2C�豸
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
 * i2c_init - ��ʼ��I2C
 */
void i2c_init(i2c_regs_t *i2c) {
    //
    i2c_reset(i2c);
    // i2c����Ƶ��42MHz
    i2c->CR2.bits.FREQ = 42;
    //
    i2c->CR1.bits.PE = 0;
    // 100KHz�ı�׼ͨ��, 210 / 42 * 10^-6
    //I2C1->CCR.bits.F_S = 0;
    //I2C1->CCR.bits.CCR = 210;
    //I2C1->TRISE.bits.TRISE = 43;
    // 400KHz�Ŀ���ͨ��, F/S=1,DUTY=0,CCR=1
    i2c->TRISE.bits.TRISE = 13;
    i2c->CCR.all = 0x83;
    i2c->CR1.bits.PE = 1;
    i2c->CR1.bits.ACK = 1;
    //
    i2c->OAR1.bits.add = 0xC0;
}

/*
 * i2c_check_status - ���I2C����״̬
 *
 * @i2c: Ŀ������
 * @sr: ����״̬, sr[31:16] <==> SR2, sr[15:0] <==> SR1
 */
BOOL i2c_check_status(i2c_regs_t *i2c, uint32 sr) {
    union Data32 tmp;
    tmp.half_word[0] = i2c->SR1.all;
    tmp.half_word[1] = i2c->SR2.all;
    tmp.word = tmp.word & FLAG_MASK;
    return ((sr & tmp.word) == sr) ? TRUE : FALSE;
}
/*
 * i2c_read_byte - ��ȡһ���ֽ�
 *
 * @i2c: I2C�˿�
 * @addr: ���豸��ַ
 * @reg: ���豸�Ĵ���
 */
uint8 i2c_read_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg) {
    uint8 data;
    i2c_read_bytes(i2c, addr, reg, 1, &data);
    return data;
}
/*
 * i2c_read_bytes - ��ȡ����ֽ�
 *
 * @i2c: I2C�˿�
 * @addr: ���豸��ַ
 * @reg: ���豸�Ĵ���
 * @len: ���ݳ���
 * @buf: ����
 */
void i2c_read_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, uint8 *buf) {
    // ���߿���
    while (1 == i2c->SR2.bits.BUSY);
    // ����START,����Masterģʽ
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    // ����7λ��ַ, ����ģʽ
    i2c->DR = (addr << 1) | I2C_DIRECTION_TX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR_TXE_TRA));
    // ���ͼĴ�����ַ
    i2c->DR = reg;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
    // ���²�����ʼλ, ����Master Receiverģʽ
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    i2c->DR = (addr << 1) | I2C_DIRECTION_RX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR));
    // ���ν����ֽ�,ÿ�ν��ն���Ҫ����һ��ACK
    i2c->CR1.bits.ACK = 1;
    while (len > 1) {
        while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_RXNE));
        buf[0] = i2c->DR;
        buf++; len--;
    }
    // �����һ���ֽ�,���Է���NACK
    i2c->CR1.bits.ACK = 0;
    i2c->CR1.bits.STOP = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_RXNE));
    buf[0] = i2c->DR;

    i2c->CR1.bits.ACK = 1;
}
/*
* i2c_write_byte - ����һ���ֽ�
*
* @i2c: I2C�˿�
* @addr: ���豸��ַ
* @reg: ���豸�Ĵ���
* @data: ����
*/
void i2c_write_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 data) {
    i2c_write_bytes(i2c, addr, reg, 1, &data);
}
/*
* i2c_write_bytes - ���Ͷ���ֽ�
*
* @i2c: I2C�˿�
* @addr: ���豸��ַ
* @reg: ���豸�Ĵ���
* @len: ���ݳ���
* @buf: ����
*/
void i2c_write_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, const uint8 *buf) {
    // ���߿���
    while (1 == i2c->SR2.bits.BUSY);
    // ����START,����Masterģʽ
    i2c->CR1.bits.START = 1;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_SB));
    // ����7λ��ַ, ����ģʽ
    i2c->DR = (addr << 1) | I2C_DIRECTION_TX;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_ADDR_TXE_TRA));
    // ���ͼĴ�����ַ
    i2c->DR = reg;
    while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
    // ��������
    while (len--) {
        i2c->DR = buf[0];
        while (TRUE != i2c_check_status(i2c, I2C_STA_BUSY_MSL_TXE_TRA_BTF));
        buf++;
    }

    i2c->CR1.bits.STOP = 1;
}

