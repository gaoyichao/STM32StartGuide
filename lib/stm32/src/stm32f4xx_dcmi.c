#include <stm32f4xx_dcmi.h>

void dcmi_reset(void) {
    DCMI->CR.all = 0x0;	
	DCMI->IER.all = 0x0;
	DCMI->ICR.all = 0x1F;
	DCMI->ESCR.all = 0x0;
	DCMI->ESUR.all = 0x0;
	DCMI->CWSTRTR.all = 0x0;
	DCMI->CWSIZER.all = 0x0;
}

