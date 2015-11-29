#include <ccblkfn.h>
#include "isr.h"
#include "codeclib.h"

void main(void)
{
	// initialize AD1836
	start_AD1836();
	
	// !! set control register so that PF5 ... 
	// 8 are enabled as input, all LED PF are directed as output
	// !! and all LED are switched off
	ssync();
	
	//Anfang Modifizierter Code
	*pFIO2_DIR = 0xFFFF;    //Setze alle LED als Ausgaenge.
	*pFIO0_DIR &= 0xFF0F;   //Setze die Taster als Eingang. 
	*pFIO0_INEN |= 0x00F0;  //Aktiviere den Input Buffer fuer die Taster.
	//Ende Modifizierter Code
	
	// loop forever
	while(1) {
		idle();	// go asleep and wake up when external 
				//interrupt and ISR have been
	}
}
