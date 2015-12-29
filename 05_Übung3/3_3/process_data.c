#include "isr.h"
#include "iir.h"


// Definition der Filterkoeffizienten
#define BIQUAD_STAGES 4

// coef includes for all stages a scaling factor (2^s) and five coefficients
// in the order s, b2, b1, b0, a2, a1

// No scaling in stages (Low Pass)
const short coef[6*BIQUAD_STAGES] = {
	1, 3514, 1412, 3514, -2229, 5523, //H4
	1, 3514, -4485, 3514, -2687, 5674,//H3
	1, 3514, -5488, 3514, -3133, 5832,//H2
	1, 3514, -5728, 3514, -3410, 5965 //H1
};



int iDelayline[2*BIQUAD_STAGES+2];	// delayline for left and right channel samples

IIRstateStereo iirLR={coef,iDelayline,BIQUAD_STAGES};

void process_data()
{
	//!! Scale before filtering
	*(int*)(&sDAC1L) = iir_stereo(*(int*)(&sADC1L),&iirLR);
	//!! Scale after filtering

}

