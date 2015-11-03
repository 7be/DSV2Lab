#include <ccblkfn.h>
#include <filter.h>
#include "isr.h"
#include "tools.h"

complex_fract16 temp[FRAMELENGTH];
complex_fract16 spectrum[FRAMELENGTH];
complex_fract16 twiddle_table[FRAMELENGTH];
fract16 window[FRAMELENGTH];

void process_data()
{
	short i;
	
//	winmul(pInFrame,window,FRAMELENGTH); /* uncomment to include window function */
	rfft_fr16(pInFrame,temp,spectrum,twiddle_table,1,FRAMELENGTH,0,0);
	abs2_spec(pOutFrame,spectrum,FRAMELENGTH);

/* Add the code for detection and decoding here */
	
}


