#include <fract.h>
#include <ccblkfn.h>
#include <sys\exception.h>
#include <cdefBF561.h>
#include "codeclib.h"
#include "isr.h"

/* Add your own global variables and definitions here */

char cNewFrame;
fract16 *pInFrame, *pOutFrame;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
/* Add your own local variables here */

	// confirm interrupt handling
	*pDMA2_0_IRQ_STATUS = 0x0001;

/* Add input and output and pointer setting here */

}

