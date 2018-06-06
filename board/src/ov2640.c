#include <ov2640.h>
#include <utils.h>
#include <sccb.h>

#include <ov2640cfg.h>

#define OV2640_PWDN  	PGout(9)			//POWER DOWN控制信号 
#define OV2640_RST  	PGout(15)			//复位控制信号 

void ov2640_init_gpio(void) {
    // 控制引脚:PG9 -> DCMI_PWDN, PG15 -> DCMI_RESET
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
    // DCMI,相关时钟
    RCC->AHB1ENR.bits.gpioa = 1;
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->AHB1ENR.bits.gpioc = 1;
    RCC->AHB1ENR.bits.gpioe = 1;
    RCC->AHB2ENR.bits.dcmi = 1;
    // DCMI引脚功能分配
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
    // DCMI引脚具体配置
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;    
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_Very_High;
    gpio_init(GPIOA, GPIO_Pin_4 | GPIO_Pin_6, &pincof);
    gpio_init(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, &pincof);
    gpio_init(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11, &pincof);
    gpio_init(GPIOE, GPIO_Pin_5 | GPIO_Pin_6, &pincof);
}

//初始化OV2640 
//配置完以后,默认输出是1600*1200尺寸的图片!! 
//返回值:0,成功
//    其他,错误代码
uint8 OV2640_Init(void) {
    ov2640_init_gpio();
  	sccb_init();
    dcmi_init();

 	OV2640_PWDN=0;	//POWER ON
    delay(168000);
	OV2640_RST=0;	//复位OV2640
    delay(168000);
	OV2640_RST=1;	//结束复位
    
	sccb_wite_reg(OV2640_DSP_RA_DLMT, 0x01);	//操作sensor寄存器
 	sccb_wite_reg(OV2640_SENSOR_COM7, 0x80);	//软复位OV2640
	delay(1680000); 
    
    // 读取厂家MID
	uint16 reg = sccb_read_reg(OV2640_SENSOR_MIDH) << 8;
	reg |= sccb_read_reg(OV2640_SENSOR_MIDL);
	if(reg != OV2640_MID)
		return 1;
    // 读取厂家PID
	reg = sccb_read_reg(OV2640_SENSOR_PIDH) << 8;
	reg |= sccb_read_reg(OV2640_SENSOR_PIDL);
	if(reg != OV2640_PID)
		return 2;
    
 	//初始化 OV2640,采用SXGA分辨率(1600*1200)  
	for(uint16 i=0;i<sizeof(ov2640_uxga_init_reg_tbl)/2;i++)
	{
	   	sccb_wite_reg(ov2640_uxga_init_reg_tbl[i][0],ov2640_uxga_init_reg_tbl[i][1]);
 	} 
  	return 0x00;
} 
//OV2640切换为JPEG模式
void OV2640_JPEG_Mode(void) 
{
	uint16 i=0;
	//设置:YUV422格式
	for(i=0;i<(sizeof(ov2640_yuv422_reg_tbl)/2);i++)
	{
		sccb_wite_reg(ov2640_yuv422_reg_tbl[i][0],ov2640_yuv422_reg_tbl[i][1]); 
	} 
	//设置:输出JPEG数据
	for(i=0;i<(sizeof(ov2640_jpeg_reg_tbl)/2);i++)
	{
		sccb_wite_reg(ov2640_jpeg_reg_tbl[i][0],ov2640_jpeg_reg_tbl[i][1]);  
	}  
}
//OV2640切换为RGB565模式
void OV2640_RGB565_Mode(void) 
{
	uint16 i=0;
	//设置:RGB565输出
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
	sccb_wite_reg(0X51,hsize&0XFF);		//设置H_SIZE的低八位
	sccb_wite_reg(0X52,vsize&0XFF);		//设置V_SIZE的低八位
	sccb_wite_reg(0X53,offx&0XFF);		//设置offx的低八位
	sccb_wite_reg(0X54,offy&0XFF);		//设置offy的低八位
	temp=(vsize>>1)&0X80;
	temp|=(offy>>4)&0X70;
	temp|=(hsize>>5)&0X08;
	temp|=(offx>>8)&0X07; 
	sccb_wite_reg(0X55,temp);				//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
	sccb_wite_reg(0X57,(hsize>>2)&0X80);	//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
	sccb_wite_reg(0XE0,0X00);	
	return 0;
} 

//设置图像输出大小
//OV2640输出图像的大小(分辨率),完全由该函数确定
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
//返回值:0,设置成功
//    其他,设置失败
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
	sccb_wite_reg(0X5A,outw&0XFF);		//设置OUTW的低八位
	sccb_wite_reg(0X5B,outh&0XFF);		//设置OUTH的低八位
	temp=(outw>>8)&0X03;
	temp|=(outh>>6)&0X04;
	sccb_wite_reg(0X5C,temp);				//设置OUTH/OUTW的高位 
	sccb_wite_reg(0XE0,0X00);	
	return 0;
}

//自动曝光设置参数表,支持5个等级
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

//OV2640自动曝光等级设置
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
//白平衡设置
//0:自动
//1:太阳sunny
//2,阴天cloudy
//3,办公室office
//4,家里home
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

//色度设置
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
//亮度设置
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
//对比度设置
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640_Contrast(uint8 contrast)
{
	uint8 reg7d0val=0X20;//默认为普通模式
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
//特效设置
//0:普通模式    
//1,负片
//2,黑白   
//3,偏红色
//4,偏绿色
//5,偏蓝色
//6,复古	    
void OV2640_Special_Effects(uint8 eft)
{
	uint8 reg7d0val=0X00;//默认为普通模式
	uint8 reg7d1val=0X80;
	uint8 reg7d2val=0X80; 
	switch(eft)
	{
		case 1://负片
			reg7d0val=0X40; 
			break;	
		case 2://黑白
			reg7d0val=0X18; 
			break;	 
		case 3://偏红色
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0XC0; 
			break;	
		case 4://偏绿色
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0X40; 
			break;	
		case 5://偏蓝色
			reg7d0val=0X18; 
			reg7d1val=0XA0;
			reg7d2val=0X40; 
			break;	
		case 6://复古
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




