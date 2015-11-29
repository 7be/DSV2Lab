#include "isr.h"
#include "fir.h"

#ifdef DSP_DEBUG
#include <cycles.h>
#include <stdio.h>
#endif

// Definition der Filterkoeffizienten
#define N_FILT 5

const short coef[N_FILT] = {
6554,6554,6554,6554,6554
};

// Definition der Delayline für alle Filter
//short sDelaylineL[N_FILT];	// delayline for left channel samples
//short sDelaylineR[N_FILT];	// delayline for right channel samples
int iDelayline[N_FILT];	// delayline for left and right channel samples

//FIRstate firL={coef,sDelaylineL,sDelaylineL,N_FILT};
//FIRstate firR={coef,sDelaylineR,sDelaylineR,N_FILT};
FIRstateStereo firLR={coef,iDelayline,iDelayline,N_FILT};

void process_data()
{
#ifdef DSP_DEBUG
	cycle_stats_t stats;
	CYCLES_INIT(stats);
	CYCLES_START(stats);
#endif

// 	2 x Mono-Routine 
//	sDAC1L=fir(sADC1L,&firL);
//	sDAC1R=fir(sADC1R,&firR);


// 	1 x Stereo-Routine mit SIMD	
	*(int*)(&sDAC1L) = fir_stereo(*(int*)(&sADC1L),&firLR);

#ifdef DSP_DEBUG
	CYCLES_STOP(stats);
	CYCLES_PRINT(stats);
	fflush(stdout);
#endif
}

