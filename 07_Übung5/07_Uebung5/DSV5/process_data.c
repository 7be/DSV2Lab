#include <ccblkfn.h>
#include "math.h"
#include <filter.h>
#include "isr.h"
#include "tools.h"
#include <cycles.h>
#include "goertzel.h"
#include <stdio.h>

complex_fract16 temp[FRAMELENGTH];
complex_fract16 spectrum[FRAMELENGTH];
complex_fract32 g_spectrum[16];
complex_fract16 twiddle_table[FRAMELENGTH];
fract16 window[FRAMELENGTH];
fract16 dtmf_sig[4096];
	
					
fract16 coeff[16] = { //ak 		bk
					32634, 2962,
					32600, 3312,
					32563, 3662,
					32522, 4011,
					32360, 5156,
					32268, 5701, 
				32158, 6294,
					32026, 6934
//					0.99590, 0.09038,
//					0.99488, 0.10107,
//					0.99374, 0.11175,
//					0.99248, 0.12241,
//					0.98754, 0.15734,
//					0.98475, 0.17398,
//					0.98138, 0.19208,
//					0.97735, 0.21161
				};
	
//Zeilenfrequenzen
#define dtmf_697 59
#define dtmf_770 66
#define dtmf_852 73
#define dtmf_941 80

//Spaltenfrequenzen
#define dtmf_1209 103
#define dtmf_1336 114
#define dtmf_1477 126
#define dtmf_1633 139

#define PI 3.14159265359
#define f 770

 GOERTZELState goerztelZustand = {
	coeff,
	FRAMELENGTH,
	8
};


//Rauschfrequenzen
typedef enum rausch_bereich{
	LOWER,
	HIGHER
}rausch_bereich;

short dtmf_mittelwert(short);
short dtmf_noise_mittelwert(rausch_bereich);
short max_mittelwert(short[], short);

void process_data()

{
	short i;
	short zeilenWerte[4]; 	// Mittelwerte der Zeilenfrequenzen
	short spaltenWerte[4]; 	// Mittelwerte der Spaltenfrequenzen
	short rauschWerte[2];
	short testZ, testS;
	double omega = 0;
	
	const short leds[5][5] = {
		{0x0001, 0x0002, 0x0004, 0x0008, 0x0000}, // 1 2 3 A x --> LED 13 - 16
		{0x0010, 0x0020, 0x0040, 0x0080, 0x0000}, // 4 5 6 B x --> LED 17 - 20
		{0x0100, 0x0200, 0x0400, 0x0800, 0x0000}, // 7 8 9 C x --> LED 5 - 8
		{0x1000, 0x2000, 0x4000, 0x8000, 0x0000}, // * 0 # D x --> LED 9 - 12
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}  // x x x x x --> Keine
	};

	for(i = 0; i < FRAMELENGTH; i++){
		omega = omega + 2*PI*(770.0/48000.0);
		dtmf_sig[i] = sin(omega) * 531;
		if(omega > 2*PI){
			omega -= 2 * PI;
		}
	}
	
	
	
//	winmul(dtmf_sig,window,FRAMELENGTH); /* uncomment to include window function */
	cycle_stats_t stats;
	CYCLES_INIT(stats);
	CYCLES_START(stats);
	rfft_fr16(dtmf_sig,temp,spectrum,twiddle_table,1,FRAMELENGTH,0,0); 
	//goertzel(dtmf_sig, g_spectrum, &goerztelZustand);

	CYCLES_STOP(stats);
	CYCLES_PRINT(stats);
	fflush(stdout);
	//abs2_spec(pOutFrame,g_spectrum,FRAMELENGTH);
/*
	//Zeilenmittelwerte
	zeilenWerte[0] = dtmf_mittelwert(dtmf_697);
	zeilenWerte[1] = dtmf_mittelwert(dtmf_770);
	zeilenWe rte[2] = dtmf_mittelwert(dtmf_852);
	zeilenWerte[3] = dtmf_mittelwert(dtmf_941);
	
	//Spaltenmittelwerte
	spaltenWerte[0] = dtmf_mittelwert(dtmf_1209);
	spaltenWerte[1] = dtmf_mittelwert(dtmf_1336);
	spaltenWerte[2] = dtmf_mittelwert(dtmf_1477);
	spaltenWerte[3] = dtmf_mittelwert(dtmf_1633);
	
	//Rauschmittelwerte
	rauschWerte[0] = dtmf_noise_mittelwert(LOWER);
	rauschWerte[1] = dtmf_noise_mittelwert(HIGHER);
	
	testZ = max_mittelwert(zeilenWerte, rauschWerte[0]);
	testS = max_mittelwert(spaltenWerte,rauschWerte[1]);
	
	*pFIO2_FLAG_D = leds[testZ][testS];
	*/
	
/* Add the code for detection and decoding here */
	return;
}


short dtmf_mittelwert(short dtmf_freq){
	return (*(pOutFrame + dtmf_freq - 1) + *(pOutFrame + dtmf_freq) + *(pOutFrame + dtmf_freq + 1))/3;
}

short dtmf_noise_mittelwert(rausch_bereich bereich){
	int sum = 0;
	int i = 0;
	
	switch(bereich){
		case LOWER:
			for(i = 4; i < 51; i++){ // 50Hz - 600Hz
				sum = sum + pOutFrame[i];
			}
			return sum/(51 - 4);
		
		case HIGHER:
			for(i = 149; i < 363; i++){ // 1750Hz - 4250Hz
				sum = sum + pOutFrame[i];
			}
			return sum/(362 - 149);

		default:
			return 0;	
	}
}

short max_mittelwert(short dtmf_mittelwert[], short rausch_mittel){
	short tempMax = 0;
	int i; 
	short index = 4;
	for(i = 0; i < 4; i++){
		if(dtmf_mittelwert[i] > tempMax){ //Mittelwert größer als letzter Maximalwert
			if(dtmf_mittelwert[i] > (rausch_mittel>>1)){ //Mittelwert größer als Rauschmittelwert 
				index = i;
				tempMax = dtmf_mittelwert[i];
			}else{
				index = 4;
				tempMax = rausch_mittel>>1;
			}
		}
	}
	return index;
}



