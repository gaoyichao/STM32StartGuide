#include <stm32f407.h>
#include <dcmi.h>
#include <ov2640.h>

/*
 * dcmi_init - ��ʼ��DCMI
 */
void dcmi_init(void) {
    dcmi_reset();
	
    DCMI->CR.bits.CM = 1;                   // ����ģʽ
    DCMI->CR.bits.CROP = 0;                 // ��������ͼ��
	DCMI->CR.bits.ESS = 0;                  // Ӳ��ͬ��HSYNC,VSYNC
	DCMI->CR.bits.PCKPOL = 1;               // PCLK ��������Ч
	DCMI->CR.bits.HSPOL = 0;                // HSYNC �͵�ƽ��Ч
	DCMI->CR.bits.VSPOL = 0;                // VSYNC �͵�ƽ��Ч
	DCMI->CR.bits.FCRC = DCMI_CR_FCRC_All;  // �������е�֡
	DCMI->CR.bits.EDM = DCMI_CR_EDM_8bit; 	// 8λ���ݸ�ʽ  
	DCMI->IER.bits.FRAME = 1;               // ����֡�ж� 
	DCMI->CR.bits.ENABLE = 1;               // DCMIʹ��
}
/*
 * dcmi_init_dma - ����DCMI��DMAͨ��
 */
void dcmi_init_dma(uint32 bufaddr, uint16 buflen) { 
    RCC->AHB1ENR.bits.dma2 = 1;
    dma_reset_stream(DMA2_Stream1);
    
    DMA2_Stream1->CR.bits.CHSEL = 1;                // ͨ��ѡ��
    DMA2_Stream1->CR.bits.DIR = DMA_DIR_P2M;        // ���䷽��    
    DMA2_Stream1->CR.bits.CIRC = 1;                 // ѭ��ģʽ
    DMA2_Stream1->CR.bits.PL = DMA_Priority_High;   // �����ȼ�
    DMA2_Stream1->CR.bits.PINC = 0;                 // �����ַ������
    DMA2_Stream1->CR.bits.PSIZE = DMA_PSIZE_32Bits; // �������ݿ��
    DMA2_Stream1->CR.bits.MINC = 1;                 // �ڴ�����
    DMA2_Stream1->CR.bits.MSIZE = DMA_PSIZE_32Bits; // �ڴ����ݿ��
    DMA2_Stream1->CR.bits.MBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream1->CR.bits.PBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream1->FCR.bits.DMDIS = 0;               // ����Direct Mode
    DMA2_Stream1->FCR.bits.FTH = DMA_FIFO_4;
    
    DMA2_Stream1->PAR = (uint32)&DCMI->DR;          // �����ַ
    DMA2_Stream1->M0AR = bufaddr;                   // �����ַ
    DMA2_Stream1->NDTR.all = buflen;                // �����С
}

/*
 * dcmi_start - DCMI�ӿڿ�ʼ��������
 */
void dcmi_start(void) {
	DMA2_Stream1->CR.all |= 1<<0;   //����DMA2,Stream1 
	DCMI->CR.bits.CAPTURE = 1;      //DCMI����ʹ��  
}

/*
 * dcmi_stop - DCMIֹͣ��������
 */
void dcmi_stop(void)
{
	DCMI->CR.bits.CAPTURE = 0; 			//DCMI����ر�   
	while(1 == DCMI->CR.bits.CAPTURE);  //�ȴ�������� 
	DMA2_Stream1->CR.all &= ~(1<<0);	//�ر�DMA2,Stream1  	
} 









