
typedef struct {
		const short *h; // filter coefficients 
		const int *d; 	// start of delay line 
		int N;    		// number of coefficients 
} IIRstateStereo;

int iir_stereo(int iInput, IIRstateStereo *pIIR);

