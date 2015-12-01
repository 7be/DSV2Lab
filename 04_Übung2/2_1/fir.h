typedef struct {
		const float *h; // filter coefficients float
//		const short *h; // filter coefficients (1.15)
		const short *d; // start of delay line 
		short *p; 		// read/write pointer for current sample
		int N;    		// number of coefficients 
} FIRstate;

typedef struct {
		const short *h; // filter coefficients (1.15)
		const int *d; 	// start of delay line 
		int *p; 		// read/write pointer for current sample
		int N;    		// number of coefficients 
} FIRstateStereo;

short fir(short sInput, FIRstate *pFIR);
int fir_stereo(int iInput, FIRstateStereo *pFIR);
