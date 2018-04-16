#include <stm32f407.h>
#include <usart1.h>

/*
 * usart1_init - ��ʼ������
 */
void usart1_init(uint32 baudrate) {
    RCC->AHB1ENR.bits.gpioa = 1;
    // ����ѡ��
    // remark: �������ŵĹ���ѡ��Ӧ�����ھ��������֮ǰ
    // �����ʼ���󣬻�ͨ�����ڷ���һ��0xFF��������λ��
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

void usart1_send_byte(uint8 value) {
    USART1->DR.bits.byte = value;
    while (!USART1->SR.bits.TXE);
}

void usart1_send_bytes(const uint8 *buf, uint32 len) {
    for (uint32 i = 0; i < len; i++) {
        USART1->DR.bits.byte = buf[i];
        while (!USART1->SR.bits.TXE);
    }
}

void usart1_send_str(const uint8 *str) {
    while ('\0' != str[0]) {
        USART1->DR.bits.byte = str[0];
        while (!USART1->SR.bits.TXE);
        str++;
    }
}

void USART1_IRQHandler(void) {
    if (0 != USART1->SR.bits.RXNE) {
        uint8 data = USART1->DR.bits.byte;
        usart1_send_byte(data);
    }
}

