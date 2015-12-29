#include "isr.h"
#include "iir.h"


// Definition der Filterkoeffizienten
#define BIQUAD_STAGES 4

// coef includes for all stages a scaling factor (2^s) and five coefficients
// in the order s, b2, b1, b0, a2, a1

// No scaling in stages (Low Pass)

const short coef[6*BIQUAD_STAGES] = {
	1,  427,    172,    427, -10390, 25748, //H4
	1, 3397,  -4336,   3397, -12529, 26454, //H3
	1, 9068, -14340,   9068, -14605, 27191, //H2
	1, 11981, -19529,  11981, -15896, 27808  //H1
};



int iDelayline[2*BIQUAD_STAGES+2];	// delayline for left and right channel samples

IIRstateStereo iirLR={coef,iDelayline,BIQUAD_STAGES};

void process_data()
{
	//!! Scale before filtering
	*(int*)(&sDAC1L) = iir_stereo(*(int*)(&sADC1L),&iirLR);
	//!! Scale after filtering

}

