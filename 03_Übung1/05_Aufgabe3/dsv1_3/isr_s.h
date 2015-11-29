#include <sys\exception.h>
#include <cdefBF561.h>

//extern int iDAC1L,iDAC1R,iADC2L,iADC2R;
extern short sDAC1L,sDAC1R,sADC2L,sADC2R;
extern char cNewSample;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
