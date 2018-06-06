#ifndef DCMI_H
#define DCMI_H

#include <types.h>

void dcmi_init(void);
void dcmi_init_dma(uint32 bufaddr, uint16 buflen);

void dcmi_start(void);
void dcmi_stop(void);


#endif
