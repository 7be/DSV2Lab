#include <stdio.h>
#include <math.h>

#define PI 3.141592653
#define FABTAST 48000

float genSinus(float A, short Freq200)
{
	float sinusValue;
	float omegaNormNeu;
	static float omegaNorm = 0;
	
	omegaNormNeu = 2 * PI * ((Freq200 * 200.)/FABTAST);
	
	omegaNorm += omegaNormNeu;
	
	sinusValue = A * sin(omegaNorm);
	
	if(omegaNorm > 2 * PI)
	{
		omegaNorm -= 2 * PI;
	}
	
	return sinusValue;
}
