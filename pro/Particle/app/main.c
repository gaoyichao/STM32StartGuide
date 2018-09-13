#include <stm32f407.h>
#include <led.h>
#include <usart1.h>
#include <utils.h>

void config_interruts(void);

void adc_gpio_init() {
    RCC->AHB1ENR.bits.gpioa = 1;
    GPIOA->MODER.bits.pin0 = GPIO_Mode_Analog;
    GPIOA->PUPDR.bits.pin0 = GPIO_Pull_No;
    GPIOA->MODER.bits.pin1 = GPIO_Mode_Analog;
    GPIOA->PUPDR.bits.pin1 = GPIO_Pull_No;
}

void adc_dma_init(uint16 *buf) {
    RCC->AHB1ENR.bits.dma2 = 1;
    // DMA2_Stream0_Channel0 -> ADC1
    dma_reset_stream(DMA2_Stream0);
    DMA2_Stream0->CR.bits.CHSEL = 0;                // 通道选择
    DMA2_Stream0->CR.bits.DIR = DMA_DIR_P2M;        // 传输方向
    DMA2_Stream0->CR.bits.CIRC = 1;                 // 打开循环模式
    DMA2_Stream0->CR.bits.PL = DMA_Priority_Low;    // 低优先级
    DMA2_Stream0->CR.bits.PINC = 0;                 // 外设地址不增长
    DMA2_Stream0->CR.bits.PSIZE = DMA_PSIZE_16Bits; // 外设数据宽度
    DMA2_Stream0->CR.bits.MINC = 1;                 // 内存增长
    DMA2_Stream0->CR.bits.MSIZE = DMA_PSIZE_16Bits; // 内存数据宽度
    DMA2_Stream0->CR.bits.MBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream0->CR.bits.PBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream0->FCR.bits.DMDIS = 0;               // 保持Direct Mode
    DMA2_Stream0->FCR.bits.FTH = DMA_FIFO_2;
    DMA2_Stream0->PAR = (uint32)(&(ADC1->DR));      // 指定外设地址
    DMA2_Stream0->M0AR = (uint32)buf;               // 指定内存地址
    DMA2_Stream0->NDTR.all = 2;                     // 
    
    DMA2_Stream0->CR.bits.EN = 1;
}

void adc_init(uint16 *buf) {
    adc_gpio_init();
    adc_dma_init(buf);
    
    RCC->APB2ENR.bits.adc1 = 1;
    
    ADC_COM->CCR.bits.MULTI = ADC_Mode_Independent;         // ADC独立工作
    ADC_COM->CCR.bits.ADCPRE = ADC_Prescaler_Div2;          // 分频系数
    ADC_COM->CCR.bits.DMA = ADC_DMA_Mode1;                  // 开启DMA
    ADC_COM->CCR.bits.DELAY = ADC_SamplingDelay_5Cycles;    // 两个采样工作之间的时间间隔
    
    ADC1->CR1.bits.RES = ADC_RES_12Bits;                    // 分辨率
    ADC1->CR1.bits.SCAN = 1;                                // 开启SCAN模式
    ADC1->CR2.bits.CONT = 1;                                // 开启连续转换模式
    ADC1->CR2.bits.EXTEN = ADC_ExtTrigger_Dis;              // 禁止触发检测
    ADC1->CR2.bits.ALIGN = ADC_Align_Right;                 // 右对齐
    ADC1->SQR1.bits.L = 2 - ADC_SQR_LOffset;                // 2个转换在规则序列中

    ADC1->SMPR2.bits.SMP0 = ADC_Sample_Time_3Cycles;         // 采样频率
    ADC1->SMPR2.bits.SMP1 = ADC_Sample_Time_3Cycles;
    
    ADC1->SQR3.bits.SQ1 = 0;                                // 依次转换0,1两个通道
    ADC1->SQR3.bits.SQ2 = 1;
    
    ADC1->CR2.bits.DDS = 1;                                 // 连续DMA请求
    ADC1->CR2.bits.DMA = 1;                                 // 开启DMA
    ADC1->CR2.bits.ADON = 1;                                // 开启ADC
    ADC1->CR2.bits.SWSTART = 1;                             // 开始转换
}

uint16 adcbuf[2];
uint8 gUartByte = 0;
void USART1_IRQHandler(void) {
    if (0 != USART1->SR.bits.RXNE) {
        gUartByte = USART1->DR.bits.byte;
        uart_send_byte(USART1, gUartByte);
    }
}

int main(void) {
    usart1_init(115200);
    USART1->CR1.bits.RXNEIE = 1; // 开启接收中断

    adc_init(adcbuf);
    
    config_interruts();
    
    uart_send_bytes(USART1, "wuhaha\r\n", 8);

    while (1) {
        switch (gUartByte) {
        case 'a':
            uart_send_bytes(USART1, (uint8*)&adcbuf[0], 2);
            gUartByte = 0;
            break;
        case 'A':
            uart_send_bytes(USART1, (uint8*)&adcbuf[1], 2);
            gUartByte = 0;
            break;
        }
    }
}





