#include <stm32f4xx_usart.h>
#include <stm32f407.h>

void uart_init(usart_regs_t *uart, uint32 baudrate) {
    uint32 tmp;
    // TODO: ��д��ʱ�����벶�����Ƶ�ʵ�����ʱ����
    // ��֪��ʲôԭ����mainһ��ʼ����uart_init��ʱ��ᵼ��Tim8�޷����PWM
    // ����λ����__mantissa��__fraction�����������޸ĻḴ������
    // �²��������������޸�������޸���Tim8�ļĴ���,����static����֮,������Խ��
    // �²��Ƿ���ȷû�н�һ����֤
    static uint32 __mantissa, __fraction;

    uart->CR1.bits.M = 0;      // 8����λ
    uart->CR1.bits.PCE = 0;    // ����żУ��
    uart->CR1.bits.RE = 1;     // ��
    uart->CR1.bits.TE = 1;     // ��
    uart->CR2.bits.STOP = USART_STOP_1bit; // 1λֹͣλ

    uart->CR3.bits.CTSE = 0;   // �ر�Ӳ��������
    uart->CR3.bits.RTSE = 0;

    uart->CR1.bits.OVER8 = 0;  // ��ʼλ16���ز����������˼��㲨����

    if (uart == USART1)
        tmp = (FRE_APB2 / 4) * 25 / baudrate;
    else
        tmp = (25 * FRE_APB1) / (4 * baudrate);

    __mantissa = tmp / 100;
    __fraction = (16 * (tmp - 100 * __mantissa) + 50) / 100;

    uart->BRR.bits.mantissa = __mantissa;
    uart->BRR.bits.fraction = __fraction;

    //uart->CR1.bits.RXNEIE = 1; // ���������ж�
    uart->CR1.bits.UE = 1;     // ��������
}

void uart_send_byte(usart_regs_t *uart, uint8 value) {
    uart->DR.bits.byte = value;
    while (!uart->SR.bits.TXE);
}

void uart_send_bytes(usart_regs_t *uart, const uint8 *buf, uint32 len) {
    for (uint32 i = 0; i < len; i++) {
        uart->DR.bits.byte = buf[i];
        while (!uart->SR.bits.TXE);
    }
}

void uart_send_str(usart_regs_t *uart, const uint8 *str) {
    while ('\0' != str[0]) {
        uart->DR.bits.byte = str[0];
        while (!uart->SR.bits.TXE);
        str++;
    }
}
