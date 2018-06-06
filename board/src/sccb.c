#include <sccb.h>
#include <utils.h>

//IO方向设置
#define SCCB_SDA_IN()  { GPIOD->MODER.bits.pin7 = GPIO_Mode_In; }	//PD7 输入
#define SCCB_SDA_OUT() { GPIOD->MODER.bits.pin7 = GPIO_Mode_Out; } 	//PD7 输出
#define SCCB_SCL    		PDout(6)	 	//SCL
#define SCCB_SDA    		PDout(7) 		//SDA	 
#define SCCB_READ_SDA    	PDin(7)  		//输入SDA    
#define SCCB_ID   			0X60  			//OV2640的ID

/*
 * sccb_init - 初始化SCCB接口
 */
void sccb_init(void) {
    SCCB_SCL = 1;
    SCCB_SDA = 1;

	SCCB_SDA_OUT();
}			 

/*
 * sccb_start - SCCB起始信号
 *
 * 保持时钟高电平, 数据线产生下降沿
 * 起始信号结束后保证SDA和SCL均为低电平,总线忙
 */
static void sccb_start(void) {
    SCCB_SDA=1;
    SCCB_SCL=1;
    delay(168);
    
    SCCB_SDA=0;
    
    delay(168);
    SCCB_SCL=0;
}

/*
 * sccb_stop - SCCB停止信号
 *
 * 保持时钟高电平,数据线产生上升沿
 * 停止信号结束后保证SDA,SCL均为高电平,总线空闲
 */
static void sccb_stop(void) {
    SCCB_SDA=0;
    delay(168);
    SCCB_SCL=1;	
    delay(168);
    
    SCCB_SDA=1;
    
    delay(168);
}

/*
 * sccb_nack - 产生NA信号
 *
 * 一个字节通信的第9个时钟, 在时钟的上升沿保持数据为高电平
 * 在读寄存器操作的第三个phase中产生
 */
static void sccb_nack(void) {
    delay(168);
	SCCB_SDA=1;	
	SCCB_SCL=1;	
    delay(168);
	SCCB_SCL=0;
	
    delay(168);
	SCCB_SDA=0;	
    delay(168);
}

/*
 * sccb_write_byte - 向总线写一个字节
 *
 * 一共有9个时钟,前8个时钟为具体的数据,第9个时钟为Slave的NA反馈
 * 若Slave反馈为0表示成功接收
 * 在下降沿或者说是低电平更新数据,上升沿锁存
 *
 * @dat: 目标数据
 * return: 0正常接收,!0有错
 */
static uint8 sccb_write_byte(uint8 dat) {
	uint8 j,res;	 
	for(j = 0; j < 8; j++) {
        // SCCB_SCL=0;
        SCCB_SDA = (dat & 0x80) ? 1 : 0;
		dat<<=1;
        delay(168);
        
		SCCB_SCL=1;
        delay(168);
		SCCB_SCL=0;		   
	}
    // 第9个时钟
	SCCB_SDA_IN();
    delay(168);
	SCCB_SCL=1;
    delay(168);
    res = (1 == SCCB_READ_SDA) ? 1 : 0;
	SCCB_SCL=0;		 
    
	SCCB_SDA_OUT();		//设置SDA为输出    
	return res;  
}	 

/*
 * sccb_read_byte - 从总线上读取一个字节
 *
 * 只处理前8个时钟,保存接收到的数据,第九个时钟一般为NACK不在本函数体现
 * 在下降沿或者说是低电平更新数据,上升沿锁存
 *
 * return: 读到的数据
 */
static uint8 sccb_read_byte(void) {
	uint8 temp=0,j;    
	SCCB_SDA_IN();
    
	for(j=8;j>0;j--) {  	  
        delay(168);
		SCCB_SCL=1;
        
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;
        
        delay(168);
		SCCB_SCL=0;
	}
    
	SCCB_SDA_OUT();
	return temp;
} 							    

/*
 * sccb_wite_reg - 写从设备寄存器
 *
 * 有3个phase: 发送从设备ID,发送寄存器地址,发送写数据内容
 *
 * @reg: 寄存器地址
 * @data: 数据内容
 */
uint8 sccb_wite_reg(uint8 reg,uint8 data) {
	uint8 res=0;
	sccb_start();
    
	if(sccb_write_byte(SCCB_ID))
        res=1;
    delay(168);
    
  	if(sccb_write_byte(reg))
        res=1;
    delay(168);
    
  	if(sccb_write_byte(data))
        res=1;
    
  	sccb_stop();	  
  	return	res;
}		  					    

/*
 * sccb_read_reg - 读从设备寄存器
 *
 * 有2个阶段: 2Phase写和2Phase读
 * 2Phase写: 发送从设备ID, 发送寄存器地址
 * 2Phase读: 发送从设备读ID, 接收数据内容
 *
 * @reg: 寄存器地址
 * return: 接收到的数据
 */
uint8 sccb_read_reg(uint8 reg) {
	uint8 val=0;
    
	sccb_start();
	sccb_write_byte(SCCB_ID);
    delay(168);
  	sccb_write_byte(reg);
    delay(168);
	sccb_stop();
    delay(168);
    
	//设置寄存器地址后，才是读
	sccb_start();
	sccb_write_byte(SCCB_ID|0X01);
    delay(168);
  	val = sccb_read_byte();	
  	sccb_nack();
  	sccb_stop();
    
  	return val;
}















