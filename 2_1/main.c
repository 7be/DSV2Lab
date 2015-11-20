#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"
#include "process_data.h"

void main(void)
{
#ifndef DSP_DEBUG	
	// initialize AD1836 when code is not debugged
	start_AD1836();
#else
	// set cNewSample when code is debugged
	cNewSample=1;
#endif
	
	// loop forever
	while(1) {

#ifndef DSP_DEBUG	
		idle();	// go asleep and wake up on interrupt only
#endif
		if (cNewSample) {	// check whether new sample has been read by SPORT0 ISR
#ifndef DSP_DEBUG	
			cNewSample=0;	// reset flag
#endif
			process_data();	// do the sample processing

		}

	}
		
}
