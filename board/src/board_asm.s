;********************************************************************************************************
;
; board_asm - 一些汇编写的工具
;
;**************************************************************************** Yichao GAO * 2018.12.15 *****
    EXPORT board_lock
    EXPORT board_unlock
    EXPORT board_set_msp

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;********************************************************************************************************
;                                      关闭可屏蔽中断(系统上锁)
;									     int board_lock(void)
;
; 1. 保存中断屏蔽寄存器PRIMASK到R0中
;
; 2. 关闭可屏蔽中断
;
; 3. 退出时R0中保存的PRIMASK作为return数据返回
;
; 4. 与函数xtos_unlock成对使用
;
;********************************************************************************************************

board_lock
    MRS     R0, PRIMASK         ; 保存中断屏蔽寄存器PRIMASK到R0中
    CPSID   I                   ; 关闭中断
    BX      LR

;********************************************************************************************************
;                                      打开可屏蔽中断(系统解锁)
;									  void board_unlock(int key)
;
; 1. 参数key通过内核寄存器R0传递
;
; 2. 把R0的值写回到PRIMASK恢复进入临界区前的状态
;
; 3. 与函数xtos_lock成对使用
;
;********************************************************************************************************

board_unlock
    MSR     PRIMASK, R0			; 把R0的值写回到PRIMASK恢复进入临界区前的状态
    BX      LR
    
;********************************************************************************************************
;                                设置处理器主栈指针(Main Stack Pointer)
;									  void board_set_msp(uint32 msp)
;
; 1. 参数msp通过内核寄存器R0传递
;
; 2. 把R0的值写到MSP
;
;********************************************************************************************************

board_set_msp
    MSR     MSP, R0
    BX      LR




    END