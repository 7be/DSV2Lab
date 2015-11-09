#include <stdio.h> 
#include <math.h>
const double Pi = 3.141592653;
const double Interruptf=0; // habs in keinem manual gefunden muss die interruptfreg sein
float rad= -1;
float genSinus(float A, short Freq200){
	rad=rad+(freq200*200)/Interruptf;	//normiert zwischen -1 und 1 hochzählen
	if(rad>=1) {rad=-1;}				//überlauf vermeiden
	return A*sin(Pi*rad);				//sinus zurück geben
}