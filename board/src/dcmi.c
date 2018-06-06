#include <stm32f407.h>
#include <dcmi.h>
#include <ov2640.h>

/*
 * dcmi_init - 初始化DCMI
 */
void dcmi_init(void) {
    dcmi_reset();
	
    DCMI->CR.bits.CM = 1;                   // 快照模式
    DCMI->CR.bits.CROP = 0;                 // 捕获完整图像
	DCMI->CR.bits.ESS = 0;                  // 硬件同步HSYNC,VSYNC
	DCMI->CR.bits.PCKPOL = 1;               // PCLK 上升沿有效
	DCMI->CR.bits.HSPOL = 0;                // HSYNC 低电平有效
	DCMI->CR.bits.VSPOL = 0;                // VSYNC 低电平有效
	DCMI->CR.bits.FCRC = DCMI_CR_FCRC_All;  // 捕获所有的帧
	DCMI->CR.bits.EDM = DCMI_CR_EDM_8bit; 	// 8位数据格式  
	DCMI->IER.bits.FRAME = 1;               // 开启帧中断 
	DCMI->CR.bits.ENABLE = 1;               // DCMI使能
}
/*
 * dcmi_init_dma - 配置DCMI的DMA通道
 */
void dcmi_init_dma(uint32 bufaddr, uint16 buflen) { 
    RCC->AHB1ENR.bits.dma2 = 1;
    dma_reset_stream(DMA2_Stream1);
    
    DMA2_Stream1->CR.bits.CHSEL = 1;                // 通道选择
    DMA2_Stream1->CR.bits.DIR = DMA_DIR_P2M;        // 传输方向    
    DMA2_Stream1->CR.bits.CIRC = 1;                 // 循环模式
    DMA2_Stream1->CR.bits.PL = DMA_Priority_High;   // 高优先级
    DMA2_Stream1->CR.bits.PINC = 0;                 // 外设地址不增长
    DMA2_Stream1->CR.bits.PSIZE = DMA_PSIZE_32Bits; // 外设数据宽度
    DMA2_Stream1->CR.bits.MINC = 1;                 // 内存增长
    DMA2_Stream1->CR.bits.MSIZE = DMA_PSIZE_32Bits; // 内存数据宽度
    DMA2_Stream1->CR.bits.MBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream1->CR.bits.PBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream1->FCR.bits.DMDIS = 0;               // 保持Direct Mode
    DMA2_Stream1->FCR.bits.FTH = DMA_FIFO_4;
    
    DMA2_Stream1->PAR = (uint32)&DCMI->DR;          // 外设地址
    DMA2_Stream1->M0AR = bufaddr;                   // 缓存地址
    DMA2_Stream1->NDTR.all = buflen;                // 缓存大小
}

/*
 * dcmi_start - DCMI接口开始接收数据
 */
void dcmi_start(void) {
	DMA2_Stream1->CR.all |= 1<<0;   //开启DMA2,Stream1 
	DCMI->CR.bits.CAPTURE = 1;      //DCMI捕获使能  
}

/*
 * dcmi_stop - DCMI停止接收数据
 */
void dcmi_stop(void)
{
	DCMI->CR.bits.CAPTURE = 0; 			//DCMI捕获关闭   
	while(1 == DCMI->CR.bits.CAPTURE);  //等待传输结束 
	DMA2_Stream1->CR.all &= ~(1<<0);	//关闭DMA2,Stream1  	
} 









