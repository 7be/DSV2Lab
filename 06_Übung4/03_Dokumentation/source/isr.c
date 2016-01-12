#include <fract.h>
#include <ccblkfn.h>
#include <sys\exception.h>
#include <cdefBF561.h>
#include "codeclib.h"
#include "isr.h"

/* Add your own global variables and definitions here */

#define TRIGGER_ON      0x7FFFFFFF
#define TRIGGER_OFF     0x00000000

#define INTERNAL_ADC_R1 0x5

#define INTERNAL_DAC_L0 0x0
#define INTERNAL_DAC_R0 0x4

char cNewFrame = 0;
// Pointer für die Buffer
fract16 *pInFrame, *pOutFrame, *pInBuffer, *pOutBuffer;
// Buffer Arrays
fract16 inBuffer1[FRAMELENGTH], inBuffer2[FRAMELENGTH], 
		outBuffer1[FRAMELENGTH], outBuffer2[FRAMELENGTH];


EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
/* Add your own local variables here */
    
    static unsigned int iSampleCounter = 0;
    // confirm interrupt handling
    *pDMA2_0_IRQ_STATUS = 0x0001;

/* Add input and output and pointer setting here */
	// Bei neuem Sample Frame müssen die Pointer umgeschaltet werden
    if(iSampleCounter == 0){
        if(pInFrame == inBuffer1){
            pInBuffer   = inBuffer1;
            pInFrame    = inBuffer2;
            pOutBuffer  = outBuffer1;
            pOutFrame   = outBuffer2;
        }
        else{
            pInBuffer   = inBuffer2;
            pInFrame    = inBuffer1;
            pOutBuffer  = outBuffer2;
            pOutFrame   = outBuffer1;
            
        }
        iDMATxBuffer[INTERNAL_DAC_L0] = TRIGGER_OFF;//Trigger on DACL1
    }
    // Schreibe den aktuellen Eingangswert in den aktuellen Eingangsbuffer
    pInBuffer[iSampleCounter] = iDMARxBuffer[INTERNAL_ADC_R1] >> 16; 
    // Schreibe den aktuellen Ausgangswert in den aktuellen Ausgangsbuffer
    iDMATxBuffer[INTERNAL_DAC_R0] = pOutBuffer[iSampleCounter] << 16;
    // Zähle Samples hoch
    iSampleCounter++;
    // Wenn genug Samples vorhanden sind muss eine neue FFT angestoßen werden.
    if(iSampleCounter >= FRAMELENGTH){
        iSampleCounter = 0;
        iDMATxBuffer[INTERNAL_DAC_L0] = TRIGGER_ON; //Trigger on DACL1
        cNewFrame = 1;
    }
}

