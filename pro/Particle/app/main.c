#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>
#include <ov2640.h>
#include <dcmi.h>

void config_interruts(void);

uint8 wuhaha[6] = "12345";
extern uint8 _usart1_received_datas;

#define jpeg_buf_size 31*1024  			//定义JPEG数据缓存jpeg_buf的大小(*4字节)
__align(4) uint32 jpeg_buf[jpeg_buf_size];	//JPEG数据缓存buf
volatile uint32 jpeg_data_len=0; 			//buf中的JPEG有效数据长度 
volatile uint8 jpeg_data_ok=0;				//JPEG数据采集完成标志 
										//0,数据没有采集完;
										//1,数据采集完了,但是还没处理;
										//2,数据已经处理完成了,可以开始下一帧接收

//DCMI中断服务函数
void DCMI_IRQHandler(void) {  
	if(1 == DCMI->MIS.bits.FRAME) {
        if(jpeg_data_ok==0) {
            DMA2_Stream1->CR.all &= ~(1<<0);		                //停止当前传输
            while(DMA2_Stream1->CR.all & 0X01);                     //等待DMA2_Stream1可配置   
            jpeg_data_len = jpeg_buf_size - DMA2_Stream1->NDTR.all; //得到此次数据传输的长度
            jpeg_data_ok = 1; 				                        //标记JPEG数据采集完按成,等待其他函数处理
        }
		DCMI->ICR.bits.FRAME = 1;                                   //清除帧中断
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





