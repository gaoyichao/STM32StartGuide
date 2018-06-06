/***********************************************************
 *
 * stm32f4xx_usart - ����
 *
 ************************************** ���ҳ�.2017.0131 ***/
#ifndef STM32F4XX_USART_H
#define STM32F4XX_USART_H

#include <types.h>

struct usart_sr_bits {
    // PE - ��żУ�������Ӳ����λ��
    // ���ͨ���ȶ�SR�Ĵ������ٶ�/дDR�Ĵ��������������λ;
    // ���������λ֮ǰ������ȴ�RXNEλ��λ��
    uint32 PE : 1;
    // FE - ֡���󣬼�⵽��ͬ�����������󡢻��߽��յ�Bread֡ʱ����Ӳ����λ��
    // ���ͨ���ȶ�SR,�ٶ�DR�Ĵ��������λ��
    // �����ǰ���ڴ�������ݣ���������֡�����ֲ���Overrun������ô���ݽ��ᱻ���ͣ�ͬʱֻ��OREλ��λ��
    uint32 FE : 1;
    // NF - ������־λ��Ӳ����λ��
    // ���ͨ���ȶ�SR���ٶ�DR�Ĵ��������λ
    uint32 NF : 1;
    // ORE - Overrun���󣬵�RXNE=1ʱ��������λ�Ĵ������Ѿ���ɽ��������ݣ������͵�RDR(������)�Ĵ����С�
    // ���ͨ���ȶ�SR,�ٶ�DR�Ĵ��������λ��
    uint32 ORE : 1;
    // IDLE - Ӳ����⵽Idle Lineʱ��λ��
    // ���ͨ���ȶ�SR,�ٶ�DR�Ĵ��������λ��
    uint32 IDLE : 1;
    // RXNE - �����ݼĴ����ǿգ�Ӳ����λ
    // �����DR�Ĵ����Ϳ��������λ����Ҳ����ͨ��ֱ�����λд0���
    uint32 RXNE : 1;
    // TC - Transmission Complete, ������һ֡����TXE = 1ʱ��λ
    // ���ͨ���ȶ�SR�Ĵ�������дDR�Ĵ��������������λ;��Ҳ����ͨ��ֱ�����λд0���
    uint32 TC : 1;
    // TXE - �������ݼĴ���Ϊ�գ���TDR�Ĵ����е�����д�뷢����λ�Ĵ���ʱ��λ��
    // ���дDR�Ĵ��������λ��
    uint32 TXE : 1;
    // LBD - LIN Bread Detection,
    // ���д0���
    uint32 LBD : 1;
    // CTS - ������CTS��תʱ��λ
    // ���д0���
    uint32 CTS : 1;
    uint32 rsv0 : 6;
    uint32 rsv1 : 16;
};

union usart_sr {
    struct usart_sr_bits bits;
    uint32 all;
};

struct usart_dr_bits {
    uint32 byte : 8;
    uint32 rsv0 : 8;
    uint32 rsv1 : 16;
};

union usart_dr {
    struct usart_dr_bits bits;
    uint32 all;
};

/*
 * ��׼USARTģʽ��(����SPIģʽ)��
 * ������ = f_ck / (8 * (2 - OVER8) * USARTDIV)
 * OVER8 = 0ʱ��USARTDIV = mantissa + fraction / 16
 * OVER8 = 1ʱ��USARTDIV = mantissa + fraction / 8
 *
 * Smartcard, LIN, IrDAģʽ�£�
 * ������ = f_ck / (16 * USARTDIV)
 */
struct usart_brr_bits {
    // DIV��С������
    uint32 fraction : 4;
    // DIV����������
    uint32 mantissa : 12;
    uint32 rsv : 16;
};

union usart_brr {
    struct usart_brr_bits bits;
    uint32 all;
};

struct usart_cr1_bits {
    // SBK - Send BreaK
    uint32 SBK : 1;
    // RWU - Receive WakeUp, �������λ��λ, ���������Ƿ���muteģʽ
    uint32 RWU : 1;
    // RE - ʹ�ܽ�����
    uint32 RE : 1;
    // TE - ʹ�ܷ�����
    uint32 TE : 1;
    // IDLEIE - ʹ��IDLE�ж�
    uint32 IDLEIE : 1;
    // RXNEIE - ʹ�ܽ����ж�
    uint32 RXNEIE : 1;
    // TCIE - ��������ж�ʹ��
    uint32 TCIE : 1;
    // TXEIE - TXE�ж�ʹ��
    uint32 TXEIE : 1;
    // PEIE - ��żУ���ж�ʹ��
    uint32 PEIE : 1;
    // PS - ��żУ�鷽ʽѡ��, 0:Even, 1:Odd,����
    uint32 PS : 1;
    // PCE - ��żУ��ʹ��
    uint32 PCE : 1;
    // WAKE - ���ѷ�ʽ��0:Idle Line, 1: ��ַ����
    uint32 WAKE : 1;
    // M - ֡�ֳ���0:1��ʼλ��8����λ��nֹͣλ
    // 1: 1��ʼλ�� 9����λ��nֹͣλ
    uint32 M : 1;
    // UE - USARTʹ��
    uint32 UE : 1;
    uint32 rsv0 : 1;
    // OVER8 - �ز�����ʽ��0��16�β���, 1:8�β���
    uint32 OVER8 : 1;
    uint32 rsv1 : 16;
};

union usart_cr1 {
    struct usart_cr1_bits bits;
    uint32 all;
};

#define USART_STOP_1bit 0x00
#define USART_STOP_0_5bit 0x01
#define USART_STOP_2bit 0x02
#define USART_STOP_1_5bit 0x03
struct usart_cr2_bits {
    // ���������ĵ�ַ
    uint32 add : 4;
    uint32 rsv0 : 1;
    // LBDL - LIN break detection length, 0:10-bit, 1:11-bit
    uint32 LBDL : 1;
    // LBDIE - LIN break detection �ж�ʹ��
    uint32 LBDIE : 1;
    uint32 rsv1 : 1;
    // LBCL - Last Bit Clock Pulse, ��ͬ��ģʽ�£�����MSBʱ��CK�����Ƿ�ӦMSB
    uint32 LBCL : 1;
    // CPHA - Clock Phase, ͬ��ģʽ�£�����ʲôʱ���ȡ����
    // 0: ��һ��ʱ���������ǵ�һ�λ�ȡ���ݵ�ʱ����
    // 1: �ڶ���ʱ���������ǵ�һ�λ�ȡ���ݵ�ʱ����
    uint32 CPHA : 1;
    // CPOL - Clock Polarity, ͬ��ģʽ�£�CK���ŵ���̬��ƽ��0:steady low, 1:steady high
    uint32 CPOL : 1;
    // CLKEN - ʱ��ʹ��
    uint32 CLKEN : 1;
    // STOP - ֹͣλ����2'b00:1bit, 2'01:0.5bit, 2'10:2bit, 2'11:1.5bit
    uint32 STOP : 2;
    // LINEN - LINģʽ����
    uint32 LINEN : 1;
    uint32 rsv2 : 1;
    uint32 rsv3 : 16;
};

union usart_cr2 {
    struct usart_cr2_bits bits;
    uint32 all;
};

struct usart_cr3_bits {
    // EIE - �����ж�ʹ��
    uint32 EIE : 1;
    // IREN - ����IrDAģʽ
    uint32 IREN : 1;
    // IRLP - IrDA�͵�ѹģʽ
    uint32 IRLP : 1;
    // HDSEL - ��˫��ģʽѡ��
    uint32 HDSEL : 1;
    // NACK - Smartcardģʽ�£���λ��1ʱ������żУ�飬���������շ��᷵��һ��NACK�ź�
    uint32 NACK : 1;
    // SCEN - Smartcardģʽ����
    uint32 SCEN : 1;
    // DMAR - �������ݲ���DMA��ʽ
    uint32 DMAR : 1;
    // DMAT - �������ݲ���DMA��ʽ
    uint32 DMAT : 1;
    // RTSE - RTS Enable,������
    uint32 RTSE : 1;
    // CTSE - CTS Enable,������
    uint32 CTSE : 1;
    // CTSIE - CTS�ж�ʹ��,������
    uint32 CTSIE : 1;
    // ONEBIT - λ������ʽ,0:���β���,1:1�β���
    uint32 ONEBIT : 1;
    uint32 rsv0 : 4;
    uint32 rsv1 : 16;
};

union usart_cr3 {
    struct usart_cr3_bits bits;
    uint32 all;
};

struct usart_gtpr_bits {
    uint32 PSC : 8;
    uint32 GT : 8;
    uint32 rsv0 : 16;
};

union usart_gtpr {
    struct usart_gtpr_bits bits;
    uint32 all;
};

typedef struct usart_regs {
    volatile union usart_sr SR;         /* ����״̬�Ĵ���, offset: 0x00 */
    volatile union usart_dr DR;         /* �������ݼĴ���, offset: 0x04 */
    volatile union usart_brr BRR;       /* ���ڲ����ʼĴ���, offset: 0x08 */
    volatile union usart_cr1 CR1;       /* ���ڿ��ƼĴ���1, offset: 0x0C */
    volatile union usart_cr2 CR2;       /* ���ڿ��ƼĴ���2, offset: 0x10 */
    volatile union usart_cr3 CR3;       /* ���ڿ��ƼĴ���3, offset: 0x14 */
    volatile union usart_gtpr GTPR;     /* �����ػ�ʱ��ͷ�Ƶ�Ĵ���, offset: 0x18 */
} usart_regs_t;


/* ���ڼĴ�����ַӳ�� */
#define USART1_BASE 0x40011000
#define USART2_BASE 0x40004400
#define USART3_BASE 0x40004800
#define UART4_BASE  0x40004C00
#define UART5_BASE  0x40005000
#define USART6_BASE 0x40011400
/* ���ڼĴ���ָ����� */
#define USART1 ((usart_regs_t *) USART1_BASE)
#define USART2 ((usart_regs_t *) USART2_BASE)
#define USART3 ((usart_regs_t *) USART3_BASE)
#define UART4  ((usart_regs_t *) UART4_BASE)
#define UART5  ((usart_regs_t *) UART5_BASE)
#define USART6 ((usart_regs_t *) USART6_BASE)

void uart_init(usart_regs_t *uart, uint32 baudrate);
void uart_send_byte(usart_regs_t *uart, uint8 value);
void uart_send_bytes(usart_regs_t *uart, const uint8 *buf, uint32 len);
void uart_send_str(usart_regs_t *uart, const uint8 *str);

#endif
