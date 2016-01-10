#include <ccblkfn.h>
#include <filter.h>
#include <window.h>
#include "isr.h"
#include "codeclib.h"
#include "process_data.h"

void main(void)
{
	// initialize AD1836 when code is not debugged
	start_AD1836();
	
	*pFIO2_DIR=0xFFFF;			// all LED PF output direction
	ssync();

	*pFIO2_FLAG_D=0x0000;			// switch off all LEDs
	ssync();

	twidfftrad2_fr16(twiddle_table,FRAMELENGTH);
	gen_hamming_fr16(window,1,FRAMELENGTH);	/* Uncomment to generate Hamming window */
//	gen_bartlett_fr16(window,1,FRAMELENGTH);	/* Uncomment to generate Bartlett window */
	
	// loop forever
	while(1) {
		idle();				// go asleep and wake up on interrupt only
		if (cNewFrame) {		// check whether new frame has been read by SPORT0 ISR
			cNewFrame=0;		// reset flag
			process_data();		// do the frame processing
		}
	}
	
}
