#include <ccblkfn.h>
#include <sys\exception.h>
#include <cdefBF561.h>
#include "codeclib.h"

#define INTERNAL_ADC_L0 0x0
#define INTERNAL_ADC_R0 0x4

#define INTERNAL_DAC_L0 0x0
#define INTERNAL_DAC_R0 0x4

char cNewSample = 0;
int iDAC1L,iDAC1R,iADC1L,iADC1R;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA2_0_IRQ_STATUS = 0x0001;

	iADC1L = iDMARxBuffer[INTERNAL_ADC_L0];
	iADC1R = iDMARxBuffer[INTERNAL_ADC_R0];

	iDMATxBuffer[INTERNAL_DAC_L0] = iDAC1L;
	iDMATxBuffer[INTERNAL_DAC_R0] = iDAC1R;

	cNewSample = 1;
	
}

