.section/DOUBLE32 data1;
.extern _sDAC1L;
.extern _sDAC1R;
.extern _sADC1L;
.extern _sADC1R;

.section/DOUBLE32 program;
.global _process_data;

_process_data:

		P0.L = _sADC1L; P0.H = _sADC1L;
		R0.L = W[P0];
		P1.L = _sDAC1L; P1.H = _sDAC1L;
		W[P1] = R0.L;

		P2.L = _sADC1R; P2.H = _sADC1R;
		R0.L = W[P2];
		
// !! Add the processing R0.L -> R1.L here                */

		P3.L = _sDAC1R; P3.H = _sDAC1R;
		W[P3] = R1.L;

		RTS;

._process_data.end:


