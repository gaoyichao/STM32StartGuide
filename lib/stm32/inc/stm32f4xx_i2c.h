#pragma once

#include <types.h>

/*
 * I2C���ƼĴ���1 I2C_CR1
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_cr1_bits {
    /* ʹ�����裬����Masterģʽ���ڴ��ͽ���֮ǰһ�����ܸ�λ��λ */
    uint16 PE : 1;
    /* 0: I2C; 1: SMBUS */
    uint16 SMBUS : 1;
    uint16 rsv0 : 1;
    /* 0: SMBus Device; 1: SMBus Host */
    uint16 SMBTYPE : 1;
    /* ʹ��ARP��ARP��SMBus�еĵ�ַ����Э��(Address Resolution Protocol) */
    uint16 ENAPR : 1;
    /* ʹ��PEC, Packet Error Checking */
    uint16 ENPEC : 1;
    /* ʹ�ܹ㲥GC, General Call, �Ե�ַ0x00h����Ӧ�� */
    uint16 ENGC : 1;
    /* �رմ�ģʽ�µ�ʱ���ӳ� */
    uint16 NOSTRATCH : 1;
    /* ������ʼλ */
    uint16 START : 1;
    /* ����ֹͣλ */
    uint16 STOP : 1;
    /* ���յ�һ���ֽ�֮�����Ӧ��ACK�ź� */
    uint16 ACK : 1;
    /* 0��ʾACK���Ƶ�ǰ���ڽ����ֽڵ�(N)ACK�ź�,1��ʾ��һ���ֽ� */
    uint16 POS : 1;
    /* Packet Error Checking */
    uint16 PEC : 1;
    /* SMBus���� */
    uint16 ALERT : 1;
    uint16 rsv1 : 1;
    /* �����λ */
    uint16 SWRST : 1;
};
union i2c_cr1 {
    struct i2c_cr1_bits bits;
    uint16 all;
};
/*
 * I2C���ƼĴ���2 I2C_CR2
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_cr2_bits {
    /* ����ʱ��Ƶ��,���2,���50 */
    uint16 FREQ : 6;
    uint16 rsv0 : 2;
    /* �����ж�ʹ�� */
    uint16 ITERREN : 1;
    /* �¼��ж�ʹ�� */
    uint16 ITEVTEN : 1;
    /* �����ж�ʹ�� */
    uint16 ITBUFEN : 1;
    /* DMA����ʹ�� */
    uint16 DMAEN : 1;
    /* ���һ��DMA���� */
    uint16 LAST : 1;
    uint16 rsv1 : 3;
};
union i2c_cr2 {
    struct i2c_cr2_bits bits;
    uint16 all;
};
/*
 * I2C���е�ַ�Ĵ���1 I2C_OAR1
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_oar1_bits {
    /* ��ַ */
    uint16 add : 10;
    uint16 rsv0 : 4;
    /* ���뱣��1 */
    uint16 one : 1;
    /* ��ַģʽ */
    uint16 mode : 1;
};
union i2c_oar1 {
    struct i2c_oar1_bits bits;
    uint16 all;
};
/*
 * I2C���е�ַ�Ĵ���2 I2C_OAR2
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_oar2_bits {
    /* ʹ��˫��ַѰַģʽ */
    uint16 ENDUAL : 1;
    uint16 add2 : 7;
    uint16 rsv0 : 8;
};
union i2c_oar2 {
    struct i2c_oar2_bits bits;
    uint16 all;
};
/*
 * I2C״̬�Ĵ��� I2C_SR1
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_sr1_bits {
    /* ��ʼλ�ѷ��� */
    uint16 SB : 1;
    /* ��ַ�ѷ���(Master)/��ƥ��(Slave) */
    uint16 ADDR : 1;
    /* �ֽڴ��ͽ���Byte Transfer Finished */
    uint16 BTF : 1;
    /* ����10λ��ַͷ */
    uint16 ADD10 : 1;
    /* ��ģʽ�¼�⵽ֹͣλ */
    uint16 STOPF : 1;
    uint16 rsv0 : 1;
    /* ���ռĴ����ǿ� */
    uint16 RxNE : 1;
    /* ���ͼĴ����� */
    uint16 TxE : 1;
    /* ���ߴ��� */
    uint16 BERR : 1;
    /* ��ģʽ�������ٲ�lost */
    uint16 ARLO : 1;
    /* Ӧ��ʧ�� */
    uint16 AF : 1;
    /* ��� */
    uint16 OVR : 1;
    /* �����ڼ�PEC���� */
    uint16 PECERR : 1;
    uint16 rsv : 1;
    /* SMBus�³�ʱ */
    uint16 TIMEOUT : 1;
    /* SMBus���� */
    uint16 SMBALERT : 1;
};
union i2c_sr1 {
    struct i2c_sr1_bits bits;
    uint16 all;
};
/*
 * I2C״̬�Ĵ��� I2C_SR2
 * ƫ�Ƶ�ַ: 0x18
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_sr2_bits {
    /* 1:��ģʽ; 0:��ģʽ */
    uint16 MSL : 1;
    /* ����æ */
    uint16 BUSY : 1;
    /* 1:������; 0:������ */
    uint16 TRA : 1;
    uint16 rsv0 : 1;
    /* ���յ��㲥���е�ַ */
    uint16 GENCALL : 1;
    /* ���յ�SMBus����Ĭ�ϵ�ַ */
    uint16 SMBDEFAULT : 1;
    /* SMBus����ͷ */
    uint16 SMBHOST : 1;
    /* 1:���յ���ַ��OAR2ƥ��;0:ƥ��OAR1 */
    uint16 DUALF : 1;
    /* ���ݰ�����У�� */
    uint16 PEC : 8;
};
union i2c_sr2 {
    struct i2c_sr2_bits bits;
    uint16 all;
};
/*
 * I2Cʱ�ӿ��ƼĴ��� I2C_CCR
 * ƫ�Ƶ�ַ: 0x1C
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_ccr_bits {
    /* ʱ�ӿ��ƼĴ���,��CR2.FREQһ������͵�ƽ�͸ߵ�ƽʱ�� */
    uint16 CCR : 12;
    uint16 rsv0 : 2;
    /* ����ģʽ�µ�ռ�ձ����� */
    uint16 DUTY : 1;
    /* 1:����I2C;0:��׼I2C */
    uint16 F_S : 1;
};
union i2c_ccr {
    struct i2c_ccr_bits bits;
    uint16 all;
};

struct i2c_trise_bits {
    uint16 TRISE : 6;
    uint16 rsv0 : 10;
};
union i2c_trise {
    struct i2c_trise_bits bits;
    uint16 all;
};
/*
 * I2C�˲��Ĵ��� I2C_FLTR
 * ƫ�Ƶ�ַ: 0x24
 * ��λֵ: 0x0000
 * ����: �޵ȴ�״̬, half-word����
 */
struct i2c_fltr_bits {
    /* ���������˲��� */
    uint16 DNF : 4;
    /* ģ�������˲����ر� */
    uint16 ANOFF : 1;
    uint16 rsv0 : 11;
};
union i2c_fltr {
    struct i2c_fltr_bits bits;
    uint16 all;
};

#pragma pack(1)
typedef struct i2c_regs {
    volatile union i2c_cr1 CR1;     /* I2C���ƼĴ���1, offset: 0x00 */
    uint16 rsv0;
    volatile union i2c_cr2 CR2;     /* I2C���ƼĴ���2, offset: 0x04 */
    uint16 rsv1;
    volatile union i2c_oar1 OAR1;   /* I2C���е�ַ�Ĵ���1, offset: 0x08 */
    uint16 rsv2;
    volatile union i2c_oar2 OAR2;   /* I2C���е�ַ�Ĵ���2, offset: 0x0C */
    uint16 rsv3;
    volatile uint16 DR;             /* I2C���ݼĴ���, offset: 0x10 */
    uint16 rsv4;
    volatile union i2c_sr1 SR1;     /* I2C״̬�Ĵ���1, offset: 0x14 */
    uint16 rsv5;
    volatile union i2c_sr2 SR2;     /* I2C״̬�Ĵ���2, offset: 0x18 */
    uint16 rsv6;
    volatile union i2c_ccr CCR;     /* I2Cʱ�ӿ��ƼĴ���, offset: 0x1C */
    uint16 rsv7;
    volatile union i2c_trise TRISE; /* I2C���������ʱ��Ĵ���, offset: 0x20 */
    uint16 rsv8;
    volatile union i2c_fltr FLTR;       /* I2C�˲��Ĵ���, offset: 0x24 */
    uint16 rsv9;
} i2c_regs_t;
#pragma pack()

/* I2C�Ĵ�����ַӳ�� */
#define I2C1_BASE 0x40005400
#define I2C2_BASE 0x40005800
#define I2C3_BASE 0x40005C00
/* I2C�Ĵ���ָ����� */
#define I2C1 ((i2c_regs_t *) I2C1_BASE)
#define I2C2 ((i2c_regs_t *) I2C2_BASE)
#define I2C3 ((i2c_regs_t *) I2C3_BASE)


/*
 * EV5  ��ʼͨ��
 *
 * ����START�ź��Ժ�I2C����Masterģʽ���ȴ����¼���
 * ��ζ����ʼ�ź��Ѿ��ɹ��ķ��͵�I2C�������ˡ�
 */
#define I2C_STA_BUSY_MSL_SB            ((uint32)0x00030001)  /* BUSY, MSL and SB flag */
/*
 * EV6  Address Acknowledge
 *
 * EV5�¼�,����ʼλ����,֮��, Master������Slave�ĵ�ַ, ͬʱ��������һ�����ݵĴ��ͷ���.
 * �������豸��Ҫ�ȴ���ַƥ��Ĵ��豸����һ��ACK. ���������ACK�����¼������:
 *
 *  1) �������豸������(Master Receiver): ����I2C_STA_BUSY_MSL_ADDR.
 *
 *  2) �������豸������(Master Transmitter): ����I2C_STA_BUSY_MSL_ADDR_TXE_TRA
 */
#define I2C_STA_BUSY_MSL_ADDR_TXE_TRA   ((uint32)0x00070082)
#define I2C_STA_BUSY_MSL_ADDR           ((uint32)0x00030002)
/*
 * EV7, EV8, EV8_2 Communication events
 *
 * ����Ѿ�������һ��ͨ��(��������ʼλ �� ���豸��ַ),��ô���豸�ͱ��������µ��¼�:
 *
 * 1) ���豸������: ���豸����ȴ��¼�EV7,����ȡ����
 *
 * 2) Master Transmitter mode: The master has to send data (I2C_SendData()
 *    function) then to wait on event EV8 or EV8_2.
 *    These two events are similar:
 *     - EV8 means that the data has been written in the data register and is
 *       being shifted out.
 *     - EV8_2 means that the data has been physically shifted out and output
 *       on the bus.
 *     In most cases, using EV8 is sufficient for the application.
 *     Using EV8_2 leads to a slower communication but ensure more reliable test.
 *     EV8_2 is also more suitable than EV8 for testing on the last data transmission
 *     (before Stop condition generation).
 *
 *  @note In case the  user software does not guarantee that this event EV7 is
 *  managed before the current byte end of transfer, then user may check on EV7
 *  and BTF flag at the same time (ie. (I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF)).
 *  In this case the communication may be slower.
 *
 */
/* --EV7 */
#define  I2C_STA_BUSY_MSL_RXNE          ((uint32)0x00030040)
/* EV8_2 */
#define  I2C_STA_BUSY_MSL_TXE_TRA_BTF   ((uint32)0x00070084)

/*
 * i2c_check_status - ���I2C����״̬
 *
 * @i2c: Ŀ������
 * @sr: ����״̬, sr[31:16] <==> SR2, sr[15:0] <==> SR1
 */
BOOL i2c_check_status(i2c_regs_t *i2c, uint32 sr);


/* ����/����ģʽ */
#define I2C_DIRECTION_TX    ((uint8)0x00)
#define I2C_DIRECTION_RX    ((uint8)0x01)
/*
 * i2c_reset - ����I2C�豸
 */
void i2c_reset(i2c_regs_t *i2c);
/*
 * i2c_init - ��ʼ��I2C
 */
void i2c_init(i2c_regs_t *i2c);
/*
 * i2c_read_byte - ��ȡһ���ֽ�
 *
 * @i2c: I2C�˿�
 * @addr: ���豸��ַ
 * @reg: ���豸�Ĵ���
 */
uint8 i2c_read_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg);
/*
* i2c_read_bytes - ��ȡ����ֽ�
*
* @i2c: I2C�˿�
* @addr: ���豸��ַ
* @reg: ���豸�Ĵ���
* @len: ���ݳ���
* @buf: ����
*/
void i2c_read_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, uint8 *buf);
/*
* i2c_write_byte - ����һ���ֽ�
*
* @i2c: I2C�˿�
* @addr: ���豸��ַ
* @reg: ���豸�Ĵ���
* @data: ����
*/
void i2c_write_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 data);
/*
* i2c_write_bytes - ���Ͷ���ֽ�
*
* @i2c: I2C�˿�
* @addr: ���豸��ַ
* @reg: ���豸�Ĵ���
* @len: ���ݳ���
* @buf: ����
*/
void i2c_write_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, const uint8 *buf);


