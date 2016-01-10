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
		
		P2 = R2; // FFT Ordnung
		I0 = R0; // Betragsspektrum - Return 
		I1 = R1; // Komplexes Spektrum - Parameter
		
		R3.L = 10; // Schiebe Faktor
		
		NOP;NOP;NOP;NOP;
		
		R1.L = W[I1++];
		
		LSETUP(_LOOP_START, _LOOP_END) LC0 = P2; // Schleifendurchlaufanzahl
		_LOOP_START:
			A0 		= R1.L * R1.L || R1.L = W[I1++];
			R2.L 	= (A0 += R1.L * R1.L) || R1.L = W[I1++];
			R4.L 	= ASHIFT R2.L BY R3.L;
		_LOOP_END:
			W[I0++] = R4.L; 
		
._abs2_spec.end:
	.global _abs2_spec;
	
