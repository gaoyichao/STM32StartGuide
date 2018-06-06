#include <ov2640.h>
#include <utils.h>
#include <sccb.h>

#include <ov2640cfg.h>

#define OV2640_PWDN  	PGout(9)			//POWER DOWN�����ź� 
#define OV2640_RST  	PGout(15)			//��λ�����ź� 

void ov2640_init_gpio(void) {
    // ��������:PG9 -> DCMI_PWDN, PG15 -> DCMI_RESET
    RCC->AHB1ENR.bits.gpiog = 1;
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Out;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    gpio_init(GPIOG, GPIO_Pin_9 | GPIO_Pin_15, &pincof);
    // SCCB:PD6 -> DCMI_SCL, PD7 -> DCMI_SDA
    RCC->AHB1ENR.bits.gpiod = 1;
    pincof.mode = GPIO_Mode_Out;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    gpio_init(GPIOD, GPIO_Pin_6 | GPIO_Pin_7, &pincof);
    // DCMI,���ʱ��
    RCC->AHB1ENR.bits.gpioa = 1;
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->AHB1ENR.bits.gpioc = 1;
    RCC->AHB1ENR.bits.gpioe = 1;
    RCC->AHB2ENR.bits.dcmi = 1;
    // DCMI���Ź��ܷ���
    GPIOA->AFR.bits.pin4 = 0x0D;    // PA4 -> DCMI_HREF
    GPIOA->AFR.bits.pin6 = 0x0D;    // PA6 -> DCMI_PCLK
    GPIOB->AFR.bits.pin6 = 0x0D;    // PB6 -> DCMI_D5
    GPIOB->AFR.bits.pin7 = 0x0D;    // PB7 -> DCMI_VSYNC
    GPIOC->AFR.bits.pin6 = 0x0D;    // PC6 -> DCMI_D0
    GPIOC->AFR.bits.pin7 = 0x0D;    // PC7 -> DCMI_D1
    GPIOC->AFR.bits.pin8 = 0x0D;    // PC8 -> DCMI_D2
    GPIOC->AFR.bits.pin9 = 0x0D;    // PC9 -> DCMI_D3
    GPIOC->AFR.bits.pin11 = 0x0D;   // PC11 -> DCMI_D4
    GPIOE->AFR.bits.pin5 = 0x0D;    // PE5 -> DCMI_D6
    GPIOE->AFR.bits.pin6 = 0x0D;    // PE6 -> DCMI_D7
    // DCMI���ž�������
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    gpio_init(GPIOA, GPIO_Pin_4 | GPIO_Pin_6, &pincof);
    gpio_init(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, &pincof);
    gpio_init(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11, &pincof);
    gpio_init(GPIOE, GPIO_Pin_5 | GPIO_Pin_6, &pincof);
}

//��ʼ��OV2640 
//�������Ժ�,Ĭ�������1600*1200�ߴ��ͼƬ!! 
//����ֵ:0,�ɹ�
//    ����,�������
uint8 OV2640_Init(void) {
    ov2640_init_gpio();
  	sccb_init();
    dcmi_init();

 	OV2640_PWDN=0;	//POWER ON
    delay(168000);
	OV2640_RST=0;	//��λOV2640
    delay(168000);
	OV2640_RST=1;	//������λ
    
	sccb_wite_reg(OV2640_DSP_RA_DLMT, 0x01);	//����sensor�Ĵ���
 	sccb_wite_reg(OV2640_SENSOR_COM7, 0x80);	//��λOV2640
	delay(1680000); 
    
    // ��ȡ����MID
	uint16 reg = sccb_read_reg(OV2640_SENSOR_MIDH) << 8;
	reg |= sccb_read_reg(OV2640_SENSOR_MIDL);
	if(reg != OV2640_MID)
		return 1;
    // ��ȡ����PID
	reg = sccb_read_reg(OV2640_SENSOR_PIDH) << 8;
	reg |= sccb_read_reg(OV2640_SENSOR_PIDL);
	if(reg != OV2640_PID)
		return 2;
    
 	//��ʼ�� OV2640,����SXGA�ֱ���(1600*1200)  
	for(uint16 i=0;i<sizeof(ov2640_uxga_init_reg_tbl)/2;i++)
	{
	   	sccb_wite_reg(ov2640_uxga_init_reg_tbl[i][0],ov2640_uxga_init_reg_tbl[i][1]);
 	} 
  	return 0x00;
} 
//OV2640�л�ΪJPEGģʽ
void OV2640_JPEG_Mode(void) 
{
	uint16 i=0;
	//����:YUV422��ʽ
	for(i=0;i<(sizeof(ov2640_yuv422_reg_tbl)/2);i++)
	{
		sccb_wite_reg(ov2640_yuv422_reg_tbl[i][0],ov2640_yuv422_reg_tbl[i][1]); 
	} 
	//����:���JPEG����
	for(i=0;i<(sizeof(ov2640_jpeg_reg_tbl)/2);i++)
	{
		sccb_wite_reg(ov2640_jpeg_reg_tbl[i][0],ov2640_jpeg_reg_tbl[i][1]);  
	}  
}
//OV2640�л�ΪRGB565ģʽ
void OV2640_RGB565_Mode(void) 
{
	uint16 i=0;
	//����:RGB565���
	for(i=0;i<(sizeof(ov2640_rgb565_reg_tbl)/2);i++)
	{
		sccb_wite_reg(ov2640_rgb565_reg_tbl[i][0],ov2640_rgb565_reg_tbl[i][1]); 
	} 
} 
uint8 OV2640_ImageWin_Set(uint16 offx,uint16 offy,uint16 width,uint16 height)
{
	uint16 hsize;
	uint16 vsize;
	uint8 temp; 
	if(width%4)return 1;
	if(height%4)return 2;
	hsize=width/4;
	vsize=height/4;
	sccb_wite_reg(0XFF,0X00);	
	sccb_wite_reg(0XE0,0X04);					
	sccb_wite_reg(0X51,hsize&0XFF);		//����H_SIZE�ĵͰ�λ
	sccb_wite_reg(0X52,vsize&0XFF);		//����V_SIZE�ĵͰ�λ
	sccb_wite_reg(0X53,offx&0XFF);		//����offx�ĵͰ�λ
	sccb_wite_reg(0X54,offy&0XFF);		//����offy�ĵͰ�λ
	temp=(vsize>>1)&0X80;
	temp|=(offy>>4)&0X70;
	temp|=(hsize>>5)&0X08;
	temp|=(offx>>8)&0X07; 
	sccb_wite_reg(0X55,temp);				//����H_SIZE/V_SIZE/OFFX,OFFY�ĸ�λ
	sccb_wite_reg(0X57,(hsize>>2)&0X80);	//����H_SIZE/V_SIZE/OFFX,OFFY�ĸ�λ
	sccb_wite_reg(0XE0,0X00);	
	return 0;
} 

//����ͼ�������С
//OV2640���ͼ��Ĵ�С(�ֱ���),��ȫ�ɸú���ȷ��
//width,height:���(��Ӧ:horizontal)�͸߶�(��Ӧ:vertical),width��height������4�ı���
//����ֵ:0,���óɹ�
//    ����,����ʧ��
uint8 OV2640_OutSize_Set(uint16 width,uint16 height)
{
	uint16 outh;
	uint16 outw;
	uint8 temp; 
	if(width%4)return 1;
	if(height%4)return 2;
	outw=width/4;
	outh=height/4; 
	sccb_wite_reg(0XFF,0X00);	
	sccb_wite_reg(0XE0,0X04);			
	sccb_wite_reg(0X5A,outw&0XFF);		//����OUTW�ĵͰ�λ
	sccb_wite_reg(0X5B,outh&0XFF);		//����OUTH�ĵͰ�λ
	temp=(outw>>8)&0X03;
	temp|=(outh>>6)&0X04;
	sccb_wite_reg(0X5C,temp);				//����OUTH/OUTW�ĸ�λ 
	sccb_wite_reg(0XE0,0X00);	
	return 0;
}

//�Զ��ع����ò�����,֧��5���ȼ�
const static uint8 OV2640_AUTOEXPOSURE_LEVEL[5][8]=
{
	{
		0xFF,0x01,
		0x24,0x20,
		0x25,0x18,
		0x26,0x60,
	},
	{
		0xFF,0x01,
		0x24,0x34,
		0x25,0x1c,
		0x26,0x00,
	},
	{
		0xFF,0x01,	
		0x24,0x3e,	
		0x25,0x38,
		0x26,0x81,
	},
	{
		0xFF,0x01,
		0x24,0x48,
		0x25,0x40,
		0x26,0x81,
	},
	{
		0xFF,0x01,	
		0x24,0x58,	
		0x25,0x50,	
		0x26,0x92,	
	},
}; 

//OV2640�Զ��ع�ȼ�����
//level:0~4
void OV2640_Auto_Exposure(uint8 level)
{  
	uint8 i;
	uint8 *p=(uint8*)OV2640_AUTOEXPOSURE_LEVEL[level];
	for(i=0;i<4;i++)
	{ 
		sccb_wite_reg(p[i*2],p[i*2+1]); 
	} 
}  
//��ƽ������
//0:�Զ�
//1:̫��sunny
//2,����cloudy
//3,�칫��office
//4,����home
void OV2640_Light_Mode(uint8 mode)
{
	uint8 regccval=0X5E;//Sunny 
	uint8 regcdval=0X41;
	uint8 regceval=0X54;
	switch(mode)
	{ 
		case 0://auto 
			sccb_wite_reg(0XFF,0X00);	 
			sccb_wite_reg(0XC7,0X00);//AWB ON 
			return;  	
		case 2://cloudy
			regccval=0X65;
			regcdval=0X41;
			regceval=0X4F;
			break;	
		case 3://office
			regccval=0X52;
			regcdval=0X41;
			regceval=0X66;
			break;	
		case 4://home
			regccval=0X42;
			regcdval=0X3F;
			regceval=0X71;
			break;	
	}
	sccb_wite_reg(0XFF,0X00);	 
	sccb_wite_reg(0XC7,0X40);	//AWB OFF 
	sccb_wite_reg(0XCC,regccval); 
	sccb_wite_reg(0XCD,regcdval); 
	sccb_wite_reg(0XCE,regceval);  
}

//ɫ������
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640_Color_Saturation(uint8 sat)
{ 
	uint8 reg7dval=((sat+2)<<4)|0X08;
	sccb_wite_reg(0XFF,0X00);		
	sccb_wite_reg(0X7C,0X00);		
	sccb_wite_reg(0X7D,0X02);				
	sccb_wite_reg(0X7C,0X03);			
	sccb_wite_reg(0X7D,reg7dval);			
	sccb_wite_reg(0X7D,reg7dval); 		
}
//��������
//0:(0X00)-2
//1:(0X10)-1
//2,(0X20) 0
//3,(0X30)+1
//4,(0X40)+2
void OV2640_Brightness(uint8 bright)
{
  sccb_wite_reg(0xff, 0x00);
  sccb_wite_reg(0x7c, 0x00);
  sccb_wite_reg(0x7d, 0x04);
  sccb_wite_reg(0x7c, 0x09);
  sccb_wite_reg(0x7d, bright<<4); 
  sccb_wite_reg(0x7d, 0x00); 
}
\
//�Աȶ�����
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640_Contrast(uint8 contrast)
{
	uint8 reg7d0val=0X20;//Ĭ��Ϊ��ͨģʽ
	uint8 reg7d1val=0X20;
  	switch(contrast)
	{
		case 0://-2
			reg7d0val=0X18;	 	 
			reg7d1val=0X34;	 	 
			break;	
		case 1://-1
			reg7d0val=0X1C;	 	 
			reg7d1val=0X2A;	 	 
			break;	
		case 3://1
			reg7d0val=0X24;	 	 
			reg7d1val=0X16;	 	 
			break;	
		case 4://2
			reg7d0val=0X28;	 	 
			reg7d1val=0X0C;	 	 
			break;	
	}
	sccb_wite_reg(0xff,0x00);
	sccb_wite_reg(0x7c,0x00);
	sccb_wite_reg(0x7d,0x04);
	sccb_wite_reg(0x7c,0x07);
	sccb_wite_reg(0x7d,0x20);
	sccb_wite_reg(0x7d,reg7d0val);
	sccb_wite_reg(0x7d,reg7d1val);
	sccb_wite_reg(0x7d,0x06);
}
//��Ч����
//0:��ͨģʽ    
//1,��Ƭ
//2,�ڰ�   
//3,ƫ��ɫ
//4,ƫ��ɫ
//5,ƫ��ɫ
//6,����	    
void OV2640_Special_Effects(uint8 eft)
{
	uint8 reg7d0val=0X00;//Ĭ��Ϊ��ͨģʽ
	uint8 reg7d1val=0X80;
	uint8 reg7d2val=0X80; 
	switch(eft)
	{
		case 1://��Ƭ
			reg7d0val=0X40; 
			break;	
		case 2://�ڰ�
			reg7d0val=0X18; 
			break;	 
		case 3://ƫ��ɫ
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0XC0; 
			break;	
		case 4://ƫ��ɫ
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0X40; 
			break;	
		case 5://ƫ��ɫ
			reg7d0val=0X18; 
			reg7d1val=0XA0;
			reg7d2val=0X40; 
			break;	
		case 6://����
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0XA6; 
			break;	 
	}
	sccb_wite_reg(0xff,0x00);
	sccb_wite_reg(0x7c,0x00);
	sccb_wite_reg(0x7d,reg7d0val);
	sccb_wite_reg(0x7c,0x05);
	sccb_wite_reg(0x7d,reg7d1val);
	sccb_wite_reg(0x7d,reg7d2val); 
}




