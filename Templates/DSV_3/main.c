#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"
#include "process_data.h"

void main(void)
{
	// initialize AD1836 when code is not debugged
	start_AD1836();
	
	// loop forever
	while(1) {
		idle();				// go asleep and wake up on interrupt only
												
		if (cNewSample) {	// check whether new sample has been read by SPORT0 ISR
			cNewSample=0;	// reset flag
			process_data();	// do the sample processing

		}

	}
		
}
