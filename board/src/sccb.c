#include <sccb.h>
#include <utils.h>

//IO��������
#define SCCB_SDA_IN()  { GPIOD->MODER.bits.pin7 = GPIO_Mode_In; }	//PD7 ����
#define SCCB_SDA_OUT() { GPIOD->MODER.bits.pin7 = GPIO_Mode_Out; } 	//PD7 ���
#define SCCB_SCL    		PDout(6)	 	//SCL
#define SCCB_SDA    		PDout(7) 		//SDA	 
#define SCCB_READ_SDA    	PDin(7)  		//����SDA    
#define SCCB_ID   			0X60  			//OV2640��ID

/*
 * sccb_init - ��ʼ��SCCB�ӿ�
 */
void sccb_init(void) {
    SCCB_SCL = 1;
    SCCB_SDA = 1;

	SCCB_SDA_OUT();
}			 

/*
 * sccb_start - SCCB��ʼ�ź�
 *
 * ����ʱ�Ӹߵ�ƽ, �����߲����½���
 * ��ʼ�źŽ�����֤SDA��SCL��Ϊ�͵�ƽ,����æ
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
 * sccb_stop - SCCBֹͣ�ź�
 *
 * ����ʱ�Ӹߵ�ƽ,�����߲���������
 * ֹͣ�źŽ�����֤SDA,SCL��Ϊ�ߵ�ƽ,���߿���
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
 * sccb_nack - ����NA�ź�
 *
 * һ���ֽ�ͨ�ŵĵ�9��ʱ��, ��ʱ�ӵ������ر�������Ϊ�ߵ�ƽ
 * �ڶ��Ĵ��������ĵ�����phase�в���
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
 * sccb_write_byte - ������дһ���ֽ�
 *
 * һ����9��ʱ��,ǰ8��ʱ��Ϊ���������,��9��ʱ��ΪSlave��NA����
 * ��Slave����Ϊ0��ʾ�ɹ�����
 * ���½��ػ���˵�ǵ͵�ƽ��������,����������
 *
 * @dat: Ŀ������
 * return: 0��������,!0�д�
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
    // ��9��ʱ��
	SCCB_SDA_IN();
    delay(168);
	SCCB_SCL=1;
    delay(168);
    res = (1 == SCCB_READ_SDA) ? 1 : 0;
	SCCB_SCL=0;		 
    
	SCCB_SDA_OUT();		//����SDAΪ���    
	return res;  
}	 

/*
 * sccb_read_byte - �������϶�ȡһ���ֽ�
 *
 * ֻ����ǰ8��ʱ��,������յ�������,�ھŸ�ʱ��һ��ΪNACK���ڱ���������
 * ���½��ػ���˵�ǵ͵�ƽ��������,����������
 *
 * return: ����������
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
 * sccb_wite_reg - д���豸�Ĵ���
 *
 * ��3��phase: ���ʹ��豸ID,���ͼĴ�����ַ,����д��������
 *
 * @reg: �Ĵ�����ַ
 * @data: ��������
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
 * sccb_read_reg - �����豸�Ĵ���
 *
 * ��2���׶�: 2Phaseд��2Phase��
 * 2Phaseд: ���ʹ��豸ID, ���ͼĴ�����ַ
 * 2Phase��: ���ʹ��豸��ID, ������������
 *
 * @reg: �Ĵ�����ַ
 * return: ���յ�������
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
    
	//���üĴ�����ַ�󣬲��Ƕ�
	sccb_start();
	sccb_write_byte(SCCB_ID|0X01);
    delay(168);
  	val = sccb_read_byte();	
  	sccb_nack();
  	sccb_stop();
    
  	return val;
}















