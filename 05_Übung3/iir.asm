// Assembler IIR filter routine
// requires two function arguments and one return valus
// 1. argument: R0 - current samples (32 bits for left and right)
// 2. argument: R1 - address of IIR structure
//
// return value: R0 - calculated output samples

.section/DOUBLE32 program;
.global _iir_stereo;

_iir_stereo:
	P3=R1;				// Adress of filter structure
	NOP;NOP;NOP;NOP;
	P0=[P3++];			// Pointer to filter coefficients
	P1=[P3++];			// Pointer to delayline
	P2=[P3];			// Number of biquad stages
	P3=R4;				// use P3 as stack for R4 (no scratch register) to avoid memory usage
			
	I0=P1;
	I1=P0;
	M0=-8(X);
	M1=8(X);
	
    LSETUP(_IIR_ST_LOOP_START,_IIR_ST_LOOP_END) LC0 = P2;
_IIR_ST_LOOP_START:
    R3.L = W[I1++];	                                                         // get scaling factor
	MNOP || R1=[I0++] || R3.H=W[I1++];		                                 // get x(n-2), b2
	A0 = R1.L * R3.H, A1 = R1.H * R3.H || R2 = [I0++] || R3.H = W[I1++];   // get x(n-1), b1
	A0 += R2.L * R3.H, A1 += R2.H * R3.H || R3.H = W[I1++];                  // get b0
	A0 += R0.L * R3.H, A1 += R0.H * R3.H || R1 = [I0++] || R3.H = W[I1++];   // get y(n-2), a2
	A0 += R1.L * R3.H, A1 += R1.H * R3.H || R1 = [I0++M0] || R3.H = W[I1++]; // get y(n-1), a1
	R4.L = (A0 += R1.L * R3.H), R4.H = (A1 += R1.H * R3.H) || [I0--] = R0;   // store x(n) as new x(n-1)
_IIR_ST_LOOP_END:
	R0 = ASHIFT R4 BY R3.L (V) || [I0++M1] = R2 ; 							 // store x(n-1) as new x(n-2)
																			 // Use option (V,S) to avoid overflow her
	[I0++]=R1;																 // store y(n-1) as new y(n-2)
	[I0]=R0;																 // store y(n) as new y(n-1)
	
	R4=P3;				// get R4 from stack

	RTS;
	
._iir_stereo.end:

