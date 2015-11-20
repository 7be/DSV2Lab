#include <sys\exception.h>
#include <cdefBF561.h>

extern short sDAC1L,sDAC1R,sADC1L,sADC1R;
extern char cNewSample;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
