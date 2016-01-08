#include <ccblkfn.h>
#include <filter.h>
#include "isr.h"
#include "tools.h"

complex_fract16 temp[FRAMELENGTH];
complex_fract16 spectrum[FRAMELENGTH];
complex_fract16 twiddle_table[FRAMELENGTH];
fract16 window[FRAMELENGTH];

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
	
	const short leds[5][5] = {
		{0x0001, 0x0002, 0x0004, 0x0008, 0x0000}, // 1 2 3 A x --> LED 13 - 16
		{0x0010, 0x0020, 0x0040, 0x0080, 0x0000}, // 4 5 6 B x --> LED 17 - 20
		{0x0100, 0x0200, 0x0400, 0x0800, 0x0000}, // 7 8 9 C x --> LED 5 - 8
		{0x1000, 0x2000, 0x4000, 0x8000, 0x0000}, // * 0 # D x --> LED 9 - 12
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}  // x x x x x --> Keine
	};
	
	//winmul(pInFrame,window,FRAMELENGTH); /* uncomment to include window function */
	rfft_fr16(pInFrame,temp,spectrum,twiddle_table,1,FRAMELENGTH,0,0);
	abs2_spec(pOutFrame,spectrum,FRAMELENGTH);

	//Zeilenmittelwerte
	zeilenWerte[0] = dtmf_mittelwert(dtmf_697);
	zeilenWerte[1] = dtmf_mittelwert(dtmf_770);
	zeilenWerte[2] = dtmf_mittelwert(dtmf_852);
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
	
/* Add the code for detection and decoding here */
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



