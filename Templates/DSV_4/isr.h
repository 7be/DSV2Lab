#include <sys\exception.h>
#include <cdefBF561.h>

#define FRAMELENGTH // Define frame length = FFT Order

extern short *pInFrame, *pOutFrame;
extern char cNewFrame;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
