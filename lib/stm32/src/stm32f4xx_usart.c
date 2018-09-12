#include <stm32f4xx_usart.h>
#include <stm32f407.h>

void uart_init(usart_regs_t *uart, uint32 baudrate) {
    uint32 tmp;
    // TODO: 在写计时器输入捕获测量频率的例程时发现
    // 不知道什么原因在main一开始调用uart_init的时候会导致Tim8无法输出PWM
    // 经定位发现__mantissa和__fraction两个变量的修改会复现问题
    // 猜测这两个变量的修改无意间修改了Tim8的寄存器,故用static修饰之,问题得以解决
    // 猜测是否正确没有进一步验证
    static uint32 __mantissa, __fraction;

    uart->CR1.bits.M = 0;      // 8数据位
    uart->CR1.bits.PCE = 0;    // 无奇偶校验
    uart->CR1.bits.RE = 1;     // 收
    uart->CR1.bits.TE = 1;     // 发
    uart->CR2.bits.STOP = USART_STOP_1bit; // 1位停止位

    uart->CR3.bits.CTSE = 0;   // 关闭硬件控制流
    uart->CR3.bits.RTSE = 0;

    uart->CR1.bits.OVER8 = 0;  // 起始位16次重采样，并依此计算波特率

    if (uart == USART1)
        tmp = (FRE_APB2 / 4) * 25 / baudrate;
    else
        tmp = (25 * FRE_APB1) / (4 * baudrate);

    __mantissa = tmp / 100;
    __fraction = (16 * (tmp - 100 * __mantissa) + 50) / 100;

    uart->BRR.bits.mantissa = __mantissa;
    uart->BRR.bits.fraction = __fraction;

    //uart->CR1.bits.RXNEIE = 1; // 开启接收中断
    uart->CR1.bits.UE = 1;     // 开启串口
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
