#include <filter.h>

typedef struct {
	fract16* coeff;
	unsigned long n_fft;
	unsigned long n_goertzel;
} GOERTZELState;

extern void goertzel(fract16 *x, complex_fract32* fft_goertzel, GOERTZELState *sgoertz);
