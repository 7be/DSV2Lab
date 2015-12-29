#include "isr.h"
#include "iir.h"


// Definition der Filterkoeffizienten
#define BIQUAD_STAGES 4

// coef includes for all stages a scaling factor (2^s) and five coefficients
// in the order s, b2, b1, b0, a2, a1

// No scaling in stages (Low Pass)
const short coef[6*BIQUAD_STAGES] = {
	1, 16384, 6581	, 16384, -10390, 25748  //H4
	1, 16384, -20909, 16384, -12529, 26454, //H3
	1, 16384, -25583, 16384, -14605, 27191, //H2
	1, 16384, -26706, 16384, -15896, 27808, //H1
};

int iDelayline[2*BIQUAD_STAGES+2];	// delayline for left and right channel samples

IIRstateStereo iirLR={coef,iDelayline,BIQUAD_STAGES};

void process_data()
{
	//!! Scale before filtering
	sADC1L = sADC1L / 474.5917;
	sADC1R = sADC1R / 474.5917;
	*(int*)(&sDAC1L) = iir_stereo(*(int*)(&sADC1L),&iirLR);

	//!! Scale after filtering
}

