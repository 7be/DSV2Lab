.section/DOUBLE32 program;
.align 2;
_winmul:
		// R0 = Pointer to pInFrame (fract16)
		// R1 = Pointer to window (fract16)
		// R2 = FFT Order
._winmul.end:
.global _winmul;

.align 2;
_abs2_spec:
		// R0 = Pointer to abs2_spectrum (fract16)
		// R1 = Pointer to spectrum (complex fract16)
		// R2 = FFT Order
._abs2_spec.end:
	.global _abs2_spec;
	
