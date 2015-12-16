#include "isr.h"
#include "fir.h"
#include "process_data.h"

#ifdef DSP_DEBUG
#include <cycles.h>
#include <stdio.h>
#endif

// Definition der Filterkoeffizienten
#define N_FILT 184

const short coef[N_FILT] = {
       -5,    -12,    -25,    -43,    -67,    -98,   -132,   -168,   -200,
     -226,   -239,   -237,   -215,   -175,   -119,    -51,     21,     89,
      144,    179,    189,    173,    134,     79,     18,    -39,    -81,
     -100,    -92,    -59,     -7,     54,    112,    155,    174,    163,
      124,     64,     -5,    -69,   -115,   -132,   -114,    -64,      9,
       91,    164,    213,    224,    193,    124,     31,    -70,   -155,
     -206,   -209,   -160,    -66,     56,    181,    282,    334,    323,
      245,    112,    -52,   -214,   -336,   -390,   -355,   -231,    -36,
      196,    416,    575,    630,    555,    347,     33,   -336,   -686,
     -939,  -1017,   -864,   -454,    204,   1058,   2024,   2996,   3856,
     4500,   4843,   4843,   4500,   3856,   2996,   2024,   1058,    204,
     -454,   -864,  -1017,   -939,   -686,   -336,     33,    347,    555,
      630,    575,    416,    196,    -36,   -231,   -355,   -390,   -336,
     -214,    -52,    112,    245,    323,    334,    282,    181,     56,
      -66,   -160,   -209,   -206,   -155,    -70,     31,    124,    193,
      224,    213,    164,     91,      9,    -64,   -114,   -132,   -115,
      -69,     -5,     64,    124,    163,    174,    155,    112,     54,
       -7,    -59,    -92,   -100,    -81,    -39,     18,     79,    134,
      173,    189,    179,    144,     89,     21,    -51,   -119,   -175,
     -215,   -237,   -239,   -226,   -200,   -168,   -132,    -98,    -67,
      -43,    -25,    -12,     -5
};

// Definition der Delayline fuer alle Filter
//short sDelaylineL[N_FILT];    // delayline for left channel samples
//short sDelaylineR[N_FILT];    // delayline for right channel samples
int iDelayline[N_FILT]; // delayline for left and right channel samples

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

//  2 x Mono-Routine 
//  sDAC1L=fir(sADC1L,&firL);
//  sDAC1R=fir(sADC1R,&firR);


//  1 x Stereo-Routine mit SIMD 
    *(int*)(&sDAC1L) = fir_stereo(*(int*)(&sADC1L),&firLR);

#ifdef DSP_DEBUG
    CYCLES_STOP(stats);
    CYCLES_PRINT(stats);
    fflush(stdout);
#endif
}

