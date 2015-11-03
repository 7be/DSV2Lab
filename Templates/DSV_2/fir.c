#include "fir.h"

short fir(short sInput, FIRstate *pFIR) {

	int k;
	float acc;
//	int acc;
	
	*(pFIR->p++)=sInput;	// store current sample in delayline
	if ( pFIR->p >= pFIR->d + pFIR->N) pFIR->p-=pFIR->N;

	for (acc=0,k=0;k<pFIR->N;k++) {
		acc += (*(pFIR->p++) * pFIR->h[k]);
		if ( pFIR->p >= pFIR->d + pFIR->N) pFIR->p-=pFIR->N;
	}
	
	return (short)acc;
}

