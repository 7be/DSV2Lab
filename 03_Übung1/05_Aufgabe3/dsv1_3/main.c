#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"
#include "process_data.h"

void main(void)
{
	// initialize AD1836
	start_AD1836();
		
	// loop forever
	while(1) {
		idle();				// go asleep and wake up when external interrupt and ISR have been
		
		if (cNewSample) {
			cNewSample = 0;
			process_data();
		}
	}
		
}
