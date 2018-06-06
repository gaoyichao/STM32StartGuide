/***********************************************************
 *
 * stm32f4xx_dcmi - 数字摄像头
 *
 ************************************** 高乙超.2018.0604 ***/
#ifndef STM32F4XX_DCMI_H
#define STM32F4XX_DCMI_H

#include <types.h>

#define DCMI_CR_FCRC_All    0   // 捕获所有帧
#define DCMI_CR_FCRC_Half   1   // 捕获50%帧
#define DCMI_CR_FCRC_Quat   2   // 捕获25%帧

#define DCMI_CR_EDM_8bit    0
#define DCMI_CR_EDM_10bit   1
#define DCMI_CR_EDM_12bit   2
#define DCMI_CR_EDM_14bit   3

struct dcmi_cr_bits {
    // 使能捕获,开始接收数据。
    // 在快照模式下,一帧图像接收结束后,将自动清零该位;
    // 需要在DMA以及DCMI的配置结束后,将该位置位,开始接收数据
    uint32 CAPTURE : 1;
    // Capture Mode - 捕获模式。
    // 0: 连续抓取模式, 接收到的数据通过DMA保存到缓存中,缓存由DMA控制器管理。
    // 1: 快照模式, 只接收一帧图像。
    uint32 CM : 1;
    // 裁剪特性
    // 0: 捕获完整图像,此模式下一帧图像的大小应是4的整数倍
    // 1: 只捕获裁剪寄存器声明的窗口内的数据
    uint32 CROP : 1;
    // JPEG压缩图像模式。
    // 0: 没有压缩的视频格式
    // 1: JPEG格式的数据, HSYNC信号不再用作行同步信号,只是标记数据可用
    // 此模式下,不支持图像裁剪和内嵌同步码
    uint32 JPEG : 1;
    // Embedded Synchronization Select,内嵌同步码。
    // 0: 使用HSYNC和VSYNC硬件信号作为行同步和帧同步信号
    // 1: 在数据流内部通过特殊字节作为行同步和帧同步信号
    uint32 ESS : 1;
    // 数据时钟极性
    // 0: 下降沿捕获数据
    // 1: 上升沿捕获数据
    uint32 PCKPOL : 1;
    // 行同步信号极性
    uint32 HSPOL : 1;
    // 帧同步信号极性
    uint32 VSPOL : 1;
    // 帧率控制,只在连续捕获的模式下有意义
    uint32 FCRC : 2;
    // 数据线宽
    uint32 EDM : 2;
    uint32 rsv0 : 2;
    uint32 ENABLE: 1;
    uint32 rsv1 : 17;
};
union dcmi_cr {
    struct dcmi_cr_bits bits;
    uint32 all;
};

struct dcmi_sr_bits {
    uint32 HSYNC : 1;
    uint32 VSYNC : 1;
    uint32 FNE : 1;
    uint32 rsv0 : 29;
};

union dcmi_sr {
    struct dcmi_sr_bits bits;
    uint32 all;
};

/*
 * dcmi_interrupt_bits - raw interrupt status
 */
struct dcmi_interrupt_bits {
    uint32 FRAME : 1;
    uint32 OVR : 1;
    uint32 ERR : 1;
    uint32 VSYNC : 1;
    uint32 LINE : 1;
    uint32 rsv0 : 27;
};

union dcmi_interrupt {
    struct dcmi_interrupt_bits bits;
    uint32 all;
};

struct dcmi_es_bits {
    uint32 FS : 8;
    uint32 LS : 8;
    uint32 LE : 8;
    uint32 FE : 8;
};

union dcmi_es {
    struct dcmi_es_bits bits;
    uint32 all;
};

struct dcmi_cwstrt_bits {
    // Horizontal Offset Count
    uint32 HOFFCNT : 14;
    uint32 rsv0 : 2;
    // Vertical Start Line Count
    uint32 VST : 13;
    uint32 rsv1 : 3;
};

union dcmi_cwstrt {
    struct dcmi_cwstrt_bits bits;
    uint32 all;
};

struct dcmi_cwsize_bits {
    uint32 CAPCNT : 14;
    uint32 rsv0 : 2;
    uint32 VLINE : 14;
    uint32 rsv1 : 2;
};

union dcmi_cwsize {
    struct dcmi_cwsize_bits bits;
    uint32 all;
};

union dcmi_dr {
    uint8 bytes[4];
    uint32 all;
};

typedef struct dcmi_regs
{
  volatile union dcmi_cr CR;            /* DCMI控制寄存器1, offset: 0x00 */
  volatile union dcmi_sr SR;            /* DCMI状态寄存器, offset: 0x04 */
  volatile union dcmi_interrupt RIS;    /* DCMI原始中断状态寄存器, offset: 0x08 */
  volatile union dcmi_interrupt IER;    /* DCMI中断使能寄存器, offset: 0x0C */
  volatile union dcmi_interrupt MIS;    /* DCMI中断屏蔽寄存器, offset: 0x10 */
  volatile union dcmi_interrupt ICR;    /* DCMI中断清除寄存器, offset: 0x14 */
  volatile union dcmi_es ESCR;          /* DCMI内嵌同步信号, offset: 0x18 */
  volatile union dcmi_es ESUR;          /* DCMI内嵌同步屏蔽信号, offset: 0x1C */
  volatile union dcmi_cwstrt CWSTRTR;   /* DCMI裁剪窗口起始坐标, offset: 0x20 */
  volatile union dcmi_cwsize CWSIZER;   /* DCMI裁剪窗口大小, offset: 0x24 */
  volatile union dcmi_dr DR;            /* DCMI数据寄存器, offset: 0x28 */
} dcmi_regs_t;

/* DCMI寄存器地址映射 */
#define DCMI_BASE 0x50050000
/* DCMI寄存器指针访问 */
#define DCMI ((dcmi_regs_t *) DCMI_BASE)

void dcmi_reset(void);


#endif





