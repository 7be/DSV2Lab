#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"

void main(void)
{
	// initialize AD1836
	start_AD1836();
	
	// !! set control register so that PF5 ... 8 are enabled as input, all LED PF are directed as output
	// !! and all LED are switched off
	ssync();
	
	// loop forever
	while(1) {
		idle();				// go asleep and wake up when external interrupt and ISR have been
	}
		
}
