#include <ccblkfn.h>
#include <sys\exception.h>
#include <cdefBF561.h>
#include "codeclib.h"
#include "gensinus.h"
#include "limits.h"

#define INTERNAL_DAC_R0 0x4

#define AMPLITUDE 0.5
#define FREQ_MIN 0      // 0 Hz
#define FREQ_MAX 50     // 10 kHz

short Freq200=1;        // 200 Hz

#define SW6_BIT 0x0020
#define SW7_BIT 0x0040

typedef enum {OFF, ON} Switch_States;
Switch_States state_sw6=OFF, state_sw7=OFF;
                                // state variables for switch 6 and 7

EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
    // confirm interrupt handling
    *pDMA2_0_IRQ_STATUS = 0x0001;

    switch (state_sw6) {                    // State of SW6
        case OFF:                           // is off
        if (*pFIO0_FLAG_D & SW6_BIT) {      // current state = on
            state_sw6 = ON;                 // set State of SW6 to on
            if (Freq200 < FREQ_MAX)
                Freq200++;                  // Increase Frequency
        }
        break;
        case ON:                            // is on
        if (!(*pFIO0_FLAG_D & SW6_BIT)) {   // current state = off
            state_sw6 = OFF;                // set State of SW6 to off
        }
        break;
    }
                                        
    switch (state_sw7) {                    // State of SW7
        case OFF:                           // is off
        if (*pFIO0_FLAG_D & SW7_BIT) {      // current state = on
            state_sw7 = ON;                 // set State of SW7 to on
            if (Freq200 > FREQ_MIN)
                Freq200--;                  // Decrease Frequency
        }
        break;
        case ON:                            // is on
        if (!(*pFIO0_FLAG_D & SW7_BIT)) {   // current state = off
            state_sw7 = OFF;                // set State of SW7 to off
        }
        break;
    }
            
    if (Freq200 == 1)
        *pFIO2_FLAG_S = 0x0100;
    // !! set control register so that LED 5 is on
    else if (Freq200 == 2)
        *pFIO2_FLAG_S = 0x0200;
    // !! set control register so that LED 6 is on
    else if (Freq200 == 20)
        *pFIO2_FLAG_S = 0x0400;
    // !! set control register so that LED 7 is on
    else
        *pFIO2_FLAG_C = 0x0700;
        // !! set control register so that no LED is on
    ssync();
    
    // copy sine value to dma output buffer
    iDMATxBuffer[4] = genSinus(AMPLITUDE, Freq200) * LONG_MAX;
}
