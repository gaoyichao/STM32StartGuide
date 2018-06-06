#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>
#include <ov2640.h>
#include <dcmi.h>

void config_interruts(void);

uint8 wuhaha[6] = "12345";
extern uint8 _usart1_received_datas;

#define jpeg_buf_size 31*1024  			//����JPEG���ݻ���jpeg_buf�Ĵ�С(*4�ֽ�)
__align(4) uint32 jpeg_buf[jpeg_buf_size];	//JPEG���ݻ���buf
volatile uint32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ��� 
volatile uint8 jpeg_data_ok=0;				//JPEG���ݲɼ���ɱ�־ 
										//0,����û�вɼ���;
										//1,���ݲɼ�����,���ǻ�û����;
										//2,�����Ѿ����������,���Կ�ʼ��һ֡����

//DCMI�жϷ�����
void DCMI_IRQHandler(void) {  
	if(1 == DCMI->MIS.bits.FRAME) {
        if(jpeg_data_ok==0) {
            DMA2_Stream1->CR.all &= ~(1<<0);		                //ֹͣ��ǰ����
            while(DMA2_Stream1->CR.all & 0X01);                     //�ȴ�DMA2_Stream1������   
            jpeg_data_len = jpeg_buf_size - DMA2_Stream1->NDTR.all; //�õ��˴����ݴ���ĳ���
            jpeg_data_ok = 1; 				                        //���JPEG���ݲɼ��갴��,�ȴ�������������
        }
		DCMI->ICR.bits.FRAME = 1;                                   //���֡�ж�
	}										 
} 


int main(void) {
    usart1_init(115200);
    usart1_init_dma();
    
    while (OV2640_Init());
    dcmi_init_dma((uint32)jpeg_buf, jpeg_buf_size);
    OV2640_JPEG_Mode();
    OV2640_OutSize_Set(320,240);
    
    config_interruts();
    
    usart1_receive_bytes_dma(wuhaha, 1);
    while (1) {
        if (_usart1_received_datas) {
            dcmi_start();
            while (1 != jpeg_data_ok);
            dcmi_stop();
            jpeg_data_ok = 0;
            uint8 *p = (uint8*)jpeg_buf;
            uint32 len = jpeg_data_len * 4;
            
            if (0xFF == p[0] && 0xD8 == p[1]) {
                for (uint32 i = 0; i < len; i++) {
                    if (0xFF == p[i] && 0xD9 == p[i+1]) {
                        len = i + 2;
                        break;
                    }
                }
                usart1_send_bytes_dma((uint8*)p, len);
            }
            
            _usart1_received_datas = 0;
            usart1_receive_bytes_dma(wuhaha, 1);
        }
    }
}





