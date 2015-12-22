#include "isr.h"
#include "iir.h"


// Definition der Filterkoeffizienten
#define BIQUAD_STAGES 4

// coef includes for all stages a scaling factor (2^s) and five coefficients
// in the order s, b2, b1, b0, a2, a1

// No scaling in stages (Low Pass)

const short coef[6*BIQUAD_STAGES] = {
	1,  -122,	   0,	 122, -16139, 30276, //H4
	1,  -651,      0,	 651, -16116, 29781, //H3
	1,  -343,      0,	 343, -15783, 29817, //H2
	1,  -451,	   0,	 451, -15760, 29601  //H1
};


int iDelayline[2*BIQUAD_STAGES+2];	// delayline for left and right channel samples

IIRstateStereo iirLR={coef,iDelayline,BIQUAD_STAGES};

void process_data()
{
	//!! Scale before filtering
	*(int*)(&sDAC1L) = iir_stereo(*(int*)(&sADC1L),&iirLR);
	//!! Scale after filtering

}

