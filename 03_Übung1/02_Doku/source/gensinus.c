#include <stdio.h>
#include <math.h>

#define PI 3.141592653 //Definition der Zahl Pi
#define FABTAST 48000  //Definition der Abtastrate des Codec

/*  @function genSinus
*   @brief  Diese Funktion generiert fortlaufend einen Sinussignal.
*   
*   @param  A ist die Amplitude des gewünschten Sinussignal zwischen 0 und 1.
*   @param  Freq200 ist die gewünschte Frequenz des Sinussignal 
*   in Schritten von 200Hz.
*   @return Ist der aktuell berechnete Wert des Sinussignals
*/
float genSinus(float A, short Freq200)
{
    float sinusValue;
    float omegaNormNeu;
    static float omegaNorm = 0;
    
    //Die Stellung des Zeigers wird neu berechnet.
    omegaNormNeu = 2 * PI * ((Freq200 * 200.)/FABTAST); 
    omegaNorm += omegaNormNeu;
    
    //Ermittlung des Sinuswertes anhand des neuen Zeigers.
    sinusValue = A * sin(omegaNorm);
    
    //Bei durchschreiten einer Periode von omegaNorm wird das Signal 
    //um 2Pi zurückgesetzt
    if(omegaNorm > 2 * PI)
    {
        omegaNorm -= 2 * PI;
    }
    
    return sinusValue;
}
