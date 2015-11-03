#include <sys\exception.h>
#include <cdefBF561.h>

extern int iDAC1L,iDAC1R,iADC1L,iADC1R;
extern short sDAC1L,sDAC1R,sADC1L,SADC1R;
extern char cNewSample;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
