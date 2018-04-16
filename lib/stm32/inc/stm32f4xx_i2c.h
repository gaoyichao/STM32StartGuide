#pragma once

#include <types.h>

/*
 * I2C控制寄存器1 I2C_CR1
 * 偏移地址: 0x00
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_cr1_bits {
    /* 使能外设，对于Master模式，在传送结束之前一定不能复位该位 */
    uint16 PE : 1;
    /* 0: I2C; 1: SMBUS */
    uint16 SMBUS : 1;
    uint16 rsv0 : 1;
    /* 0: SMBus Device; 1: SMBus Host */
    uint16 SMBTYPE : 1;
    /* 使能ARP，ARP是SMBus中的地址解析协议(Address Resolution Protocol) */
    uint16 ENAPR : 1;
    /* 使能PEC, Packet Error Checking */
    uint16 ENPEC : 1;
    /* 使能广播GC, General Call, 对地址0x00h产生应答 */
    uint16 ENGC : 1;
    /* 关闭从模式下的时钟延长 */
    uint16 NOSTRATCH : 1;
    /* 生成起始位 */
    uint16 START : 1;
    /* 生成停止位 */
    uint16 STOP : 1;
    /* 接收到一个字节之后产生应答ACK信号 */
    uint16 ACK : 1;
    /* 0表示ACK控制当前正在接收字节的(N)ACK信号,1表示下一个字节 */
    uint16 POS : 1;
    /* Packet Error Checking */
    uint16 PEC : 1;
    /* SMBus报警 */
    uint16 ALERT : 1;
    uint16 rsv1 : 1;
    /* 软件复位 */
    uint16 SWRST : 1;
};
union i2c_cr1 {
    struct i2c_cr1_bits bits;
    uint16 all;
};
/*
 * I2C控制寄存器2 I2C_CR2
 * 偏移地址: 0x04
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_cr2_bits {
    /* 外设时钟频率,最低2,最高50 */
    uint16 FREQ : 6;
    uint16 rsv0 : 2;
    /* 错误中断使能 */
    uint16 ITERREN : 1;
    /* 事件中断使能 */
    uint16 ITEVTEN : 1;
    /* 缓冲中断使能 */
    uint16 ITBUFEN : 1;
    /* DMA请求使能 */
    uint16 DMAEN : 1;
    /* 最后一次DMA传输 */
    uint16 LAST : 1;
    uint16 rsv1 : 3;
};
union i2c_cr2 {
    struct i2c_cr2_bits bits;
    uint16 all;
};
/*
 * I2C自有地址寄存器1 I2C_OAR1
 * 偏移地址: 0x08
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_oar1_bits {
    /* 地址 */
    uint16 add : 10;
    uint16 rsv0 : 4;
    /* 必须保持1 */
    uint16 one : 1;
    /* 地址模式 */
    uint16 mode : 1;
};
union i2c_oar1 {
    struct i2c_oar1_bits bits;
    uint16 all;
};
/*
 * I2C自有地址寄存器2 I2C_OAR2
 * 偏移地址: 0x0C
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_oar2_bits {
    /* 使能双地址寻址模式 */
    uint16 ENDUAL : 1;
    uint16 add2 : 7;
    uint16 rsv0 : 8;
};
union i2c_oar2 {
    struct i2c_oar2_bits bits;
    uint16 all;
};
/*
 * I2C状态寄存器 I2C_SR1
 * 偏移地址: 0x14
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_sr1_bits {
    /* 起始位已发送 */
    uint16 SB : 1;
    /* 地址已发送(Master)/已匹配(Slave) */
    uint16 ADDR : 1;
    /* 字节传送结束Byte Transfer Finished */
    uint16 BTF : 1;
    /* 发送10位地址头 */
    uint16 ADD10 : 1;
    /* 从模式下检测到停止位 */
    uint16 STOPF : 1;
    uint16 rsv0 : 1;
    /* 接收寄存器非空 */
    uint16 RxNE : 1;
    /* 发送寄存器空 */
    uint16 TxE : 1;
    /* 总线错误 */
    uint16 BERR : 1;
    /* 主模式下总线仲裁lost */
    uint16 ARLO : 1;
    /* 应答失败 */
    uint16 AF : 1;
    /* 溢出 */
    uint16 OVR : 1;
    /* 接收期间PEC错误 */
    uint16 PECERR : 1;
    uint16 rsv : 1;
    /* SMBus下超时 */
    uint16 TIMEOUT : 1;
    /* SMBus报警 */
    uint16 SMBALERT : 1;
};
union i2c_sr1 {
    struct i2c_sr1_bits bits;
    uint16 all;
};
/*
 * I2C状态寄存器 I2C_SR2
 * 偏移地址: 0x18
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_sr2_bits {
    /* 1:主模式; 0:从模式 */
    uint16 MSL : 1;
    /* 总线忙 */
    uint16 BUSY : 1;
    /* 1:发送器; 0:接收器 */
    uint16 TRA : 1;
    uint16 rsv0 : 1;
    /* 接收到广播呼叫地址 */
    uint16 GENCALL : 1;
    /* 接收到SMBus器件默认地址 */
    uint16 SMBDEFAULT : 1;
    /* SMBus主机头 */
    uint16 SMBHOST : 1;
    /* 1:接收到地址与OAR2匹配;0:匹配OAR1 */
    uint16 DUALF : 1;
    /* 数据包错误校验 */
    uint16 PEC : 8;
};
union i2c_sr2 {
    struct i2c_sr2_bits bits;
    uint16 all;
};
/*
 * I2C时钟控制寄存器 I2C_CCR
 * 偏移地址: 0x1C
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_ccr_bits {
    /* 时钟控制寄存器,与CR2.FREQ一起决定低电平和高电平时间 */
    uint16 CCR : 12;
    uint16 rsv0 : 2;
    /* 快速模式下的占空比配置 */
    uint16 DUTY : 1;
    /* 1:快速I2C;0:标准I2C */
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
 * I2C滤波寄存器 I2C_FLTR
 * 偏移地址: 0x24
 * 复位值: 0x0000
 * 访问: 无等待状态, half-word访问
 */
struct i2c_fltr_bits {
    /* 数字噪声滤波器 */
    uint16 DNF : 4;
    /* 模拟噪声滤波器关闭 */
    uint16 ANOFF : 1;
    uint16 rsv0 : 11;
};
union i2c_fltr {
    struct i2c_fltr_bits bits;
    uint16 all;
};

#pragma pack(1)
typedef struct i2c_regs {
    volatile union i2c_cr1 CR1;     /* I2C控制寄存器1, offset: 0x00 */
    uint16 rsv0;
    volatile union i2c_cr2 CR2;     /* I2C控制寄存器2, offset: 0x04 */
    uint16 rsv1;
    volatile union i2c_oar1 OAR1;   /* I2C自有地址寄存器1, offset: 0x08 */
    uint16 rsv2;
    volatile union i2c_oar2 OAR2;   /* I2C自有地址寄存器2, offset: 0x0C */
    uint16 rsv3;
    volatile uint16 DR;             /* I2C数据寄存器, offset: 0x10 */
    uint16 rsv4;
    volatile union i2c_sr1 SR1;     /* I2C状态寄存器1, offset: 0x14 */
    uint16 rsv5;
    volatile union i2c_sr2 SR2;     /* I2C状态寄存器2, offset: 0x18 */
    uint16 rsv6;
    volatile union i2c_ccr CCR;     /* I2C时钟控制寄存器, offset: 0x1C */
    uint16 rsv7;
    volatile union i2c_trise TRISE; /* I2C上升沿最大时间寄存器, offset: 0x20 */
    uint16 rsv8;
    volatile union i2c_fltr FLTR;       /* I2C滤波寄存器, offset: 0x24 */
    uint16 rsv9;
} i2c_regs_t;
#pragma pack()

/* I2C寄存器地址映射 */
#define I2C1_BASE 0x40005400
#define I2C2_BASE 0x40005800
#define I2C3_BASE 0x40005C00
/* I2C寄存器指针访问 */
#define I2C1 ((i2c_regs_t *) I2C1_BASE)
#define I2C2 ((i2c_regs_t *) I2C2_BASE)
#define I2C3 ((i2c_regs_t *) I2C3_BASE)


/*
 * EV5  开始通信
 *
 * 发送START信号以后I2C进入Master模式，等待该事件。
 * 意味着起始信号已经成功的发送到I2C总线上了。
 */
#define I2C_STA_BUSY_MSL_SB            ((uint32)0x00030001)  /* BUSY, MSL and SB flag */
/*
 * EV6  Address Acknowledge
 *
 * EV5事件,即起始位发送,之后, Master将发送Slave的地址, 同时决定了下一段数据的传送方向.
 * 接着主设备需要等待地址匹配的从设备返回一个ACK. 如果返回了ACK有如下几种情况:
 *
 *  1) 对于主设备接收器(Master Receiver): 需检测I2C_STA_BUSY_MSL_ADDR.
 *
 *  2) 对于主设备发送器(Master Transmitter): 需检测I2C_STA_BUSY_MSL_ADDR_TXE_TRA
 */
#define I2C_STA_BUSY_MSL_ADDR_TXE_TRA   ((uint32)0x00070082)
#define I2C_STA_BUSY_MSL_ADDR           ((uint32)0x00030002)
/*
 * EV7, EV8, EV8_2 Communication events
 *
 * 如果已经建立了一次通信(发送了起始位 和 从设备地址),那么主设备就必须检测如下的事件:
 *
 * 1) 主设备接收器: 主设备必须等待事件EV7,并读取数据
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
 * i2c_check_status - 检查I2C总线状态
 *
 * @i2c: 目标总线
 * @sr: 待测状态, sr[31:16] <==> SR2, sr[15:0] <==> SR1
 */
BOOL i2c_check_status(i2c_regs_t *i2c, uint32 sr);


/* 发送/接收模式 */
#define I2C_DIRECTION_TX    ((uint8)0x00)
#define I2C_DIRECTION_RX    ((uint8)0x01)
/*
 * i2c_reset - 重置I2C设备
 */
void i2c_reset(i2c_regs_t *i2c);
/*
 * i2c_init - 初始化I2C
 */
void i2c_init(i2c_regs_t *i2c);
/*
 * i2c_read_byte - 读取一个字节
 *
 * @i2c: I2C端口
 * @addr: 从设备地址
 * @reg: 从设备寄存器
 */
uint8 i2c_read_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg);
/*
* i2c_read_bytes - 读取多个字节
*
* @i2c: I2C端口
* @addr: 从设备地址
* @reg: 从设备寄存器
* @len: 数据长度
* @buf: 缓存
*/
void i2c_read_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, uint8 *buf);
/*
* i2c_write_byte - 发送一个字节
*
* @i2c: I2C端口
* @addr: 从设备地址
* @reg: 从设备寄存器
* @data: 数据
*/
void i2c_write_byte(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 data);
/*
* i2c_write_bytes - 发送多个字节
*
* @i2c: I2C端口
* @addr: 从设备地址
* @reg: 从设备寄存器
* @len: 数据长度
* @buf: 数据
*/
void i2c_write_bytes(i2c_regs_t *i2c, uint8 addr, uint8 reg, uint8 len, const uint8 *buf);


