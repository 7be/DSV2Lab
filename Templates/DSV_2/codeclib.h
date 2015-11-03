#ifndef  __AD1836_DEFINED
	#define __AD1836_DEFINED

// prototype for codec initialization
extern void start_AD1836(void);

// SPORT0 DMA transmit buffer for data transfer
extern volatile int iDMATxBuffer[8];
// SPORT0 DMA receive buffer for data transfer
extern volatile int iDMARxBuffer[8];

#endif //__AD1836_DEFINED
