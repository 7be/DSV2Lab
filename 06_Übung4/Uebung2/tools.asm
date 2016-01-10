.section/DOUBLE32 program;
.align 2;
_winmul:
		// R0 = Pointer to pInFrame (fract16)
		// R1 = Pointer to window (fract16)
		// R2 = FFT Order

		I0 = R0; // Input
		I1 = R1; // Window
		P1 = R2; // Ordnung
				
		R3.L = 0; // Anzahl der Shifts setzen
		
		NOP;NOP;NOP;NOP;
		
		R0.L = W[I0] || R1.L = W[I1++];
		
		LSETUP(_LOOP_START1, _LOOP_END1) LC0 = P1; // Schleifendurchlaufanzahl
		_LOOP_START1:
			R4.L = (A0 = R0.L * R1.L);
			R4.L = ASHIFT R4.L BY R3.L(S);
			W[I0++] = R4.L;	
		_LOOP_END1:
			R0.L = W[I0] || R1.L = W[I1++];
		RTS;	
		
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
		RTS;
._abs2_spec.end:
	.global _abs2_spec;
	
