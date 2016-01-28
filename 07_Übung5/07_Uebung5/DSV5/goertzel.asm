.section/DOUBLE32 program;
.align 2;
_goertzel:

		I0 = R0; // I0 = B0: pointer to input signal x
		B0 = R0;
		I1 = R1; // I1 pointer to DFT coefficients
		P3 = R2; // P3 pointer to Goertzel state
		nop;nop;nop;nop;
		
		R2 = [P3++];
		I2 = R2;		// I2 pointer to Goertzel coefficients
		R1 = [P3++];	
		P1 = R1;		// P1 DFT order
		R1 = R1 << 1;	
		L0 = R1;		// L0 DFT order * 2
		P0 = [P3];		// P0 number of Goertzel filters

		R4 = 0;
		LSETUP(_GOERTZEL_LOOP_START,_GOERTZEL_LOOP_END) LC0 = P0;	// loop for all Goertzel filters
_GOERTZEL_LOOP_START:
			R1 = 0;			// state z1
			R2 = 0;			// state z2
			R0.L = W[I2++]; // coefficient a1
			R0.H = W[I2++]; // coefficient b1
			LSETUP(_STATE_LOOP_START,_STATE_LOOP_END) LC1 = P1>>1;	// loop to calculate states z1 and z2
_STATE_LOOP_START:
				R3 = R0.L * R1.H || R4.H = W[I0++];
				R3 = R3 << 1 (S);
				R3 = R3 + R4;
				R2 = R3 - R2;
				nop;
				R3 = R0.L * R2.H || R4.H = W[I0++];
				R3 = R3 << 1 (S);
				R3 = R3 + R4;
_STATE_LOOP_END:
				R1 = R3 - R1;
			nop;
			R3 = R0.L * R1.H;
			R3 = R3 - R2;
			[I1++] = R3;
			
			R3 = R0.H * R1.H;			
_GOERTZEL_LOOP_END:
			[I1++] = R3;
		
		RTS;		
._goertzel.end:
.global _goertzel;