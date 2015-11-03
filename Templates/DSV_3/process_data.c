#include "isr.h"
#include "iir.h"


// Definition der Filterkoeffizienten
#define BIQUAD_STAGES 4

// coef includes for all stages a scaling factor (2^s) and five coefficients
// in the order s, b2, b1, b0, a2, a1

// No scaling in stages (Low Pass)
const short coef[6*BIQUAD_STAGES] = {

//!! add your coefficients here

};

int iDelayline[2*BIQUAD_STAGES+2];	// delayline for left and right channel samples

IIRstateStereo iirLR={coef,iDelayline,BIQUAD_STAGES};

void process_data()
{
	//!! Scale before filtering
	
	*(int*)(&sDAC1L) = iir_stereo(*(int*)(&sADC1L),&iirLR);

	//!! Scale after filtering
}

