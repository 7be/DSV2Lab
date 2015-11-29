#include <defBF561.h>

#define INTERNAL_ADC_L1 0x1
#define INTERNAL_ADC_R1 0x5

#define INTERNAL_DAC_L0 0x0
#define INTERNAL_DAC_R0 0x4

.section/DOUBLE32 data1;
.align 1;
.byte _cNewSample[1];
.global _cNewSample;

.align 4;
.byte _iDAC1L[4];
.global _iDAC1L;
.byte _iDAC1R[4];
.global _iDAC1R;
.byte _iADC2L[4];
.global _iADC2L;
.byte _iADC2R[4];
.global _iADC2R;

.extern _iDMATxBuffer;
.extern _iDMARxBuffer;

.section/DOUBLE32 program;
.global _Sport0_RX_ISR;

_Sport0_RX_ISR:

// push DSP status and regs on stack
		[--SP] = ASTAT;
		[--SP] = (R7:0,P5:0);
		[--SP] = FP;
		[--SP] = LC0;
		[--SP] = LC1;

		P0.L =  LO(DMA2_0_IRQ_STATUS); P0.H =  HI(DMA2_0_IRQ_STATUS);
		R0 =   1;
		W[P0] = R0;
		
		
		P1.L = _iDMARxBuffer; P1.H = _iDMARxBuffer;

		R1 = [P1+INTERNAL_ADC_L1*4];
		P2.L = _iADC2L; P2.H = _iADC2L;
		[P2] = R1;
		
		R2 = [P1+INTERNAL_ADC_R1*4];
		P2.L = _iADC2R; P2.H = _iADC2R;
		[P2] = R2;

		P1.L = _iDMATxBuffer; P1.H = _iDMATxBuffer;

		P2.L = _iDAC1L; P2.H = _iDAC1L;
		R1 = [P2];
		[P1+INTERNAL_DAC_L0*4] = R1;
		
		P2.L = _iDAC1R; P2.H = _iDAC1R;
		R1 = [P2];
		[P1+INTERNAL_DAC_R0*4] = R1;
		
		R0 =   1;
		P0.L = _cNewSample; P0.H = _cNewSample;
		B[P0] = R0;
		
// pop DSP status and regs from stack

		LC1 = [SP++];
		LC0 = [SP++];
		FP = [SP++];
		(R7:0,P5:0) = [SP++];
		ASTAT = [SP++];

		RTI;

._Sport0_RX_ISR.end:

