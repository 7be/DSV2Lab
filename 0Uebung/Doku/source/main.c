#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"

void main(void)
{
	// initialize AD1836
	start_AD1836();
	
	// loop forever
	while(1) {
		idle();	// go asleep and wake up on interrupt only
	}
		
}
