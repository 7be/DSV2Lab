// Assembler FIR filter routine
// requires two function arguments and one return valus
// 1. argument: R0 - current sample (16 bits)
// 2. argument: R1 - address of FIR structure
//
// return value: R0 - calculated output sample
.section/DOUBLE32 program;
.global _fir;
.global _fir_stereo;

_fir:
	P3=R1;				// ADDRESS OF FILTER STRUCTURE
	NOP;NOP;NOP;NOP;	// TO PREVENT COMPILER WARNINGS
	P0=[P3++];			// POINTER TO FILTER COEFFICIENTS
	P1=[P3++];			// POINTER TO DELAY LINE
	P2=[P3++];			// POINTER TO READ/WRITE POINTER
	R1=[P3--];			// NUMBER OF COEFFICIENTS
	R2=R1;
	R2+=(-1);

//!! Begin of Setting I, L, and B regs	
B1 = P1; //Basis: Erstes Verzögerungsglied, hier delay line.
R1 = R1 << 1; //Mal 2, weil Short Int 2 Byte hat.
L1 = R1; // Länge festlegen auf 2 mal 2 Byte.
I1 = P2; // I1 auf Read/Write legen
I2 = P0; // I2 auf Filterkoeffizienten
//!! End of Setting I, L, and B regs	

	P1=R2;				// P1 is used for loop counter initialisation
	NOP;NOP;NOP;NOP;	// TO PREVENT COMPILER WARNINGS
	W[I1++]=R0.L;			// Write current sample in delayline
	A0 = 0 || R0.L = W[I1++] || R1.L = W[I2++];
	LSETUP(_FIR_LOOP,_FIR_LOOP) LC0 = P1;	// MAC loop
_FIR_LOOP:
	A0 += R0.L * R1.L || R0.L = W[I1++] || R1.L = W[I2++];
	R0.L = (A0 += R0.L * R1.L);

	P2=I1;				// Store new READ/WRITE Pointer
	[P3]=P2;
	RTS;
	
._fir.end:

_fir_stereo:
	P3=R1;				// Adress of filter structure
	NOP;NOP;NOP;NOP;	// TO PREVENT COMPILER WARNINGS
	P0=[P3++];			// Pointer to filter coefficients
	P1=[P3++];			// Pointer to delayline
	P2=[P3++];			// read/write pointer (current sample)
	R1=[P3--];			// Number of coefficients
	R2=R1;
	R2+=(-1);

//!! Begin of Setting I, L, and B regs	
B1 = P1; //Basis: Erstes Verzögerungsglied, hier delay line.
R1 = R1 << 2; // 4*R1 da 32 Bit -> 8Bit*4=32
L1 = R1; // Länge festlegen auf 4 mal 2 Byte.
I1 = P2; // I1 auf Read/Write legen
I2 = P0; // I2 auf Filterkoeffizienten
//!! End of Setting I, L, and B regs	
					
	P1=R2;
	NOP;NOP;NOP;NOP;	// TO PREVENT COMPILER WARNINGS
	[I1++]=R0;			// Write current samples (L/R) in delayline HIER IST WAS GEÄNDERT
	A1 = A0 = 0 || R0 = [I1++] || R1.L = W[I2++];
	LSETUP(_FIR_ST_LOOP,_FIR_ST_LOOP) LC0 = P1;	// MAC loop
_FIR_ST_LOOP:
	A0 += R0.L * R1.L, A1 += R0.H * R1.L || R0 = [I1++] || R1.L = W[I2++];
	R0.L = (A0 += R0.L * R1.L);
	R0.H = (A1 += R0.H * R1.L);

	P2=I1;				// Store new READ/WRITE Pointer
	[P3]=P2;
	RTS;
	
._fir_stereo.end:



