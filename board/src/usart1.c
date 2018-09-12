#include <stm32f407.h>
#include <usart1.h>

uint8 _usart1_is_sending = 0;
uint8 _usart1_received_datas = 0;
/*
 * usart1_init - 初始化串口
 */
void usart1_init(uint32 baudrate) {
    RCC->AHB1ENR.bits.gpioa = 1;
    // 功能选择
    // remark: 对于引脚的功能选择应当放在具体的配置之前
    // 否则初始化后，会通过串口发送一个0xFF的数到上位机
    GPIOA->AFR.bits.pin9 = GPIO_AF_USART1;
    GPIOA->AFR.bits.pin10 = GPIO_AF_USART1;
    // PA9 : tx
    GPIOA->MODER.bits.pin9 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin9 = GPIO_OType_PP;
    GPIOA->PUPDR.bits.pin9 = GPIO_Pull_Up;
    GPIOA->OSPEEDR.bits.pin9 = GPIO_OSpeed_High;
    // PA10 : rx
    GPIOA->MODER.bits.pin10 = GPIO_Mode_Af;
    GPIOA->PUPDR.bits.pin10 = GPIO_Pull_No;
    GPIOA->OTYPER.bits.pin10 = GPIO_OType_OD;
    
    RCC->APB2ENR.bits.usart1 = 1;
    uart_init(USART1, baudrate);
}

void usart1_init_dma(void) {
    RCC->AHB1ENR.bits.dma2 = 1;
    // 发送DMA
    dma_reset_stream(DMA2_Stream7);
    DMA2_Stream7->CR.bits.CHSEL = 4;                // 通道选择
    DMA2_Stream7->CR.bits.DIR = DMA_DIR_M2P;        // 传输方向
    DMA2_Stream7->CR.bits.CIRC = 0;                 // 关闭循环模式
    DMA2_Stream7->CR.bits.PL = DMA_Priority_Low;    // 低优先级
    DMA2_Stream7->CR.bits.PINC = 0;                 // 外设地址不增长
    DMA2_Stream7->CR.bits.PSIZE = DMA_PSIZE_8Bits;  // 外设数据宽度
    DMA2_Stream7->CR.bits.MINC = 1;                 // 内存增长
    DMA2_Stream7->CR.bits.MSIZE = DMA_PSIZE_8Bits;  // 内存数据宽度
    DMA2_Stream7->CR.bits.MBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream7->CR.bits.PBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream7->FCR.bits.DMDIS = 0;               // 保持Direct Mode
    DMA2_Stream7->FCR.bits.FTH = DMA_FIFO_4;
    DMA2_Stream7->PAR = (uint32)(&(USART1->DR));
    DMA2_Stream7->CR.bits.TCIE = 1;
    // 接收DMA
    dma_reset_stream(DMA2_Stream5);
    DMA2_Stream5->CR.bits.CHSEL = 4;                // 通道选择
    DMA2_Stream5->CR.bits.DIR = DMA_DIR_P2M;        // 传输方向
    DMA2_Stream5->CR.bits.CIRC = 0;                 // 关闭循环模式
    DMA2_Stream5->CR.bits.PL = DMA_Priority_Low;    // 低优先级
    DMA2_Stream5->CR.bits.PINC = 0;                 // 外设地址不增长
    DMA2_Stream5->CR.bits.PSIZE = DMA_PSIZE_8Bits;  // 外设数据宽度
    DMA2_Stream5->CR.bits.MINC = 1;                 // 内存增长
    DMA2_Stream5->CR.bits.MSIZE = DMA_PSIZE_8Bits;  // 内存数据宽度
    DMA2_Stream5->CR.bits.MBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream5->CR.bits.PBURST = DMA_Burst_0;     // Single Transfer
    DMA2_Stream5->FCR.bits.DMDIS = 0;               // 保持Direct Mode
    DMA2_Stream5->FCR.bits.FTH = DMA_FIFO_4;
    DMA2_Stream5->PAR = (uint32)(&(USART1->DR));
    DMA2_Stream5->CR.bits.TCIE = 1;
}

void usart1_send_bytes_dma(uint8 *buf, int len) {
    while (_usart1_is_sending);
    
    _usart1_is_sending = 1;
    
    DMA2_Stream7->CR.bits.EN = 0;
    DMA2_Stream7->M0AR = (uint32)buf;
    DMA2_Stream7->NDTR.all = len;
    DMA2_Stream7->CR.bits.EN = 1;
    
    USART1->CR3.bits.DMAT = 1;
}

void usart1_receive_bytes_dma(uint8 *buf, int len) {
    DMA2_Stream5->CR.bits.EN = 0;
    DMA2_Stream5->M0AR = (uint32)buf;
    DMA2_Stream5->NDTR.all = len;
    DMA2_Stream5->CR.bits.EN = 1;
    
    USART1->CR3.bits.DMAR = 1;
}

void DMA2_Stream5_IRQHandler(void) {
    if (1 == DMA2->HISR.bits.TCIF5) {
        DMA2->HIFCR.bits.TCIF5 = 1;
        USART1->CR3.bits.DMAR = 0;
        _usart1_received_datas = 1;
    }
}

void DMA2_Stream7_IRQHandler(void) {
    if (1 == DMA2->HISR.bits.TCIF7) {
        DMA2->HIFCR.bits.TCIF7 = 1;
        USART1->CR3.bits.DMAT = 0;
        _usart1_is_sending = 0;
    }
}

