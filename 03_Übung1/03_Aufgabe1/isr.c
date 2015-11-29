#include <sys\exception.h>
#include <cdefBF561.h>
#include "codeclib.h"
#include "copydata.h"

#define N 32

int iCircInput[N];
int *ppWrite = iCircInput;

EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA2_0_IRQ_STATUS = 0x0001;

	// copy input data from dma input buffer into circular array
	copyData(iCircInput,&ppWrite,N);
}
