#include <stm32f4xx_fi2c.h>
#include <utils.h>
#include <systick.h>

/* ����/����ģʽ */
#define I2C_DIRECTION_TX    ((uint8)0x00)
#define I2C_DIRECTION_RX    ((uint8)0x01)
/*
 * fi2c_delay - I2C��ʱ����
 */
#define fi2c_delay(us) delay(us)

/*
* fi2c_start - ������ʼ�ź�
*/
static void fi2c_start(i2c_dev *dev) {
    dev->sda_h();
    dev->scl_h();

    fi2c_delay(dev->delayus);
    dev->sda_l();
    fi2c_delay(dev->delayus);
    dev->scl_l();
    fi2c_delay(dev->delayus);
}
/*
* fi2c_stop - ������ֹ�ź�
*/
static void fi2c_stop(i2c_dev *dev) {
    dev->scl_l();
    fi2c_delay(dev->delayus);
    dev->sda_l();
    fi2c_delay(dev->delayus);
    dev->scl_h();
    fi2c_delay(dev->delayus);
    dev->sda_h();
    fi2c_delay(dev->delayus);
}
/*
* fi2c_send_ack - ����Ӧ��
*
* @ack: 0-ACK, 1-NACK
*/
static void fi2c_send_ack(i2c_dev *dev, uint8 ack) {
    dev->scl_l();
    fi2c_delay(dev->delayus);
    (0 == ack) ? dev->sda_l() : dev->sda_h();
    fi2c_delay(dev->delayus);
    dev->scl_h();
    fi2c_delay(dev->delayus);
    dev->scl_l();
    fi2c_delay(dev->delayus);
}

#define _ACK_     0
#define _NACK_    1

/*
* fi2c_wait_ack - �ȴ�Ӧ��
*
* return: 0-ACK,1-NACK
*/
static uint8 fi2c_wait_ack(i2c_dev *dev) {
    uint8 re;
    dev->scl_l();
    fi2c_delay(dev->delayus);

    dev->set_sda_in();

    dev->scl_h();
    fi2c_delay(dev->delayus);
    re = (dev->sda()) ? 1 : 0;
    dev->scl_l();

    dev->set_sda_out();
    fi2c_delay(dev->delayus);
    return re;
}

/*
* fi2c_write_byte - ����һ���ֽ�
*
* @data: ����������
*/
static void fi2c_write_byte(i2c_dev *dev, uint8 data) {
    uint8 i = 8;
    while (i--) {
        dev->scl_l();

        fi2c_delay(dev->delayus);
        (data & 0x80) ? dev->sda_h() : dev->sda_l();
        data <<= 1;
        fi2c_delay(dev->delayus);
        dev->scl_h();
        fi2c_delay(dev->delayus);
    }
    dev->scl_l();
    fi2c_wait_ack(dev);
}

/*
* fi2c_read_byte - ����һ���ֽ�
*
* return: ���յ��ֽ�
*/
static uint8 fi2c_read_byte(i2c_dev *dev) {
    uint8 i = 8;
    uint8 re = 0;

    dev->sda_h();
    dev->set_sda_in();
    while (i--) {
        re <<= 1;
        dev->scl_l();
        fi2c_delay(dev->delayus);
        dev->scl_h();
        fi2c_delay(dev->delayus);
        if (dev->sda())
            re |= 0x01;
    }
    dev->scl_l();
    dev->set_sda_out();

    return re;
}

/*
* fi2c_init - ��ʼ��I2C
*/
void fi2c_init(i2c_dev *dev) {
    dev->init();
}


/*
* fi2c_send_byte - �����ֽ�@data���豸@dev�ļĴ���@reg��
*
* @data: ����
* @dev: �豸��ַ
* @reg: �Ĵ���
*/
void fi2c_send_byte(i2c_dev *dev, uint8 data, uint8 add, uint8 reg) {
    fi2c_start(dev);
    fi2c_write_byte(dev, add | I2C_DIRECTION_TX);
    fi2c_write_byte(dev, reg);
    fi2c_write_byte(dev, data);
    fi2c_stop(dev);
}
/*
* fi2c_send_bytes - ��������*buf���豸@dev�ļĴ���@reg��
*
* @buf: ���ݻ���
* @dev: �豸��ַ
* @reg: �Ĵ���
*/
void fi2c_send_bytes(i2c_dev *dev, const uint8 *buf, int len, uint8 add, uint8 reg) {
    fi2c_start(dev);
    fi2c_write_byte(dev, add | I2C_DIRECTION_TX);
    fi2c_write_byte(dev, reg);
    while (len--) {
        fi2c_write_byte(dev, buf[0]);
        buf++;
    }
    fi2c_stop(dev);
}
/*
* fi2c_receive_bytes - ���豸@dev�ļĴ���@reg�н��ճ���Ϊ@len������*buf
*
* @buf: ���ݻ���
* @len: ���ݳ���
* @dev: �豸��ַ
* @reg: �Ĵ���
*/
void fi2c_receive_bytes(i2c_dev *dev, uint8 *buf, int len, uint8 add, uint8 reg) {
    fi2c_start(dev);
    fi2c_write_byte(dev, add | I2C_DIRECTION_TX);
    fi2c_write_byte(dev, reg);

    fi2c_start(dev);
    fi2c_write_byte(dev, add | I2C_DIRECTION_RX);
    while (len > 1) {
        buf[0] = fi2c_read_byte(dev);
        buf++;
        len--;
        fi2c_send_ack(dev, _ACK_);
    }

    buf[0] = fi2c_read_byte(dev);
    fi2c_send_ack(dev, _NACK_);
    fi2c_stop(dev);
}




