#include <stm32f407.h>
#include <can1.h>


void can1_init_gpio(void)
{
    RCC->AHB1ENR.bits.gpioa = 1;
    // ����ѡ��
    GPIOA->AFR.bits.pin11 = GPIO_AF_CAN1;
    GPIOA->AFR.bits.pin12 = GPIO_AF_CAN1;
    // PA12 : tx
    GPIOA->MODER.bits.pin12 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin12 = GPIO_OType_PP;
    GPIOA->PUPDR.bits.pin12 = GPIO_Pull_Up;
    GPIOA->OSPEEDR.bits.pin12 = GPIO_OSpeed_High;
    // PA11 : rx
    GPIOA->MODER.bits.pin11 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin11 = GPIO_OType_PP;
    GPIOA->PUPDR.bits.pin11 = GPIO_Pull_Up;
    GPIOA->OSPEEDR.bits.pin11 = GPIO_OSpeed_High;
}

void can1_init(void)
{
    can1_init_gpio();
    RCC->APB1ENR.bits.can1 = 1;
    // �˳�Sleep,��������ģʽ
    CAN1->MCR.bits.SLEEP = 0;
    CAN1->MCR.bits.INRQ = 1;
    while (1 != CAN1->MSR.bits.INAK);
    // ���ù���ģʽ
    CAN1->MCR.bits.TTCM = 0; // ʱ�䴥��ͨ��ģʽ
    CAN1->MCR.bits.ABOM = 0; // Automatic BusOff Mode
    CAN1->MCR.bits.AWUM = 0; // Automatic Wakeup Mode
    CAN1->MCR.bits.NART = 0; // �Զ��ش�
    CAN1->MCR.bits.RFLM = 0; // ���ձ���, ����
    CAN1->MCR.bits.TXFP = 0; // �����������ȼ����ݱ���ID����
    // ����������
    CAN1->BTR.bits.BRP = 6 - 1; // 42M ==> 8M freqTq
    CAN1->BTR.bits.TS1 = 7;
    CAN1->BTR.bits.TS2 = 6;
    CAN1->BTR.bits.SJW = 1 - 1; // 1Tq�ݲ�
    // �ػ�����
    CAN1->BTR.bits.LBKM = 1;
    
    // CAN�����������
    CAN1->MCR.bits.INRQ = 0;
    while (0 != CAN1->MSR.bits.INAK);
    
    // ���ù�����
    CAN1->FMR.bits.FINIT = 1;
    CAN1->FA1R.bits.F0 = 1;
    CAN1->Filters[0].FR0 = 0;
    CAN1->Filters[1].FR1 = 0;
    CAN1->FM1R.bits.F0 = 0;
    CAN1->FS1R.bits.F0 = 1;
    CAN1->FFA1R.bits.F0 = 0;
    CAN1->FMR.bits.FINIT = 0;

    // ���������ж�
    CAN1->IER.bits.FMPIE0 = 1;
}

void CAN1_Send_Msg(void)
{
    
    CAN1->TxMailBox[0].TIR.ebits.EXID = (uint32)0x11010001;
    CAN1->TxMailBox[0].TIR.ebits.IDE = 1;
    
    CAN1->TxMailBox[0].TDTR.tbits.DLC = 8;
    
    CAN1->TxMailBox[0].TDLR = 0xbeafbeaf;
    CAN1->TxMailBox[0].TDHR = 0xbeafbeaf;
    
    CAN1->TxMailBox[0].TIR.ebits.TXRQ = 1;
}

void CAN1_Recv_Msg(void)
{
    //struct can_mailbox mail;

}

uint8 gid = 0;

void CAN1_RX0_IRQHandler(void)
{
    CAN1->RF0R.bits.RFOM = 1;
}




