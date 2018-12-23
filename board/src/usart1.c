#include <stm32f407.h>
#include <usart1.h>
#include <queue.int.h>
#include <utils.h>

int board_lock(void);
void board_unlock(int key);

#define CFG_UART1_BUF_SIZE 1024
#define CFG_UART_RECV_TIMEOUT 1000

uint8 gUsart1Buf[CFG_UART1_BUF_SIZE];
queue_uint8 gUsart1Queue;

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
    
    queue_uint8_init(&gUsart1Queue, gUsart1Buf, CFG_UART1_BUF_SIZE);
}

void USART1_IRQHandler(void) {
    if (0 != USART1->SR.bits.RXNE) {
        queue_uint8_enqueue(&gUsart1Queue, USART1->DR.bits.byte);
    }
}

BOOL usart1_ready_read(void) {
    return !queue_uint8_empty(&gUsart1Queue);
}

BOOL usart1_rsv_byte(uint8 *buf) {
    uint32 times = 0;
    int primask;
    BOOL re;
    
    while (1) {
        if (times > CFG_UART_RECV_TIMEOUT)
            return False;
        
        primask = board_lock();
        re = queue_uint8_dequeue(&gUsart1Queue, buf);
        board_unlock(primask);
        
        if (True == re)
            return True;
        
        times++;
    }
}

int usart1_buf_count(void) {
    int primask, count;

    primask = board_lock();
    count = queue_uint8_count(&gUsart1Queue);
    board_unlock(primask);
    
    return count;
}


