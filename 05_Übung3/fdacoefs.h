/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 8.3 and the Signal Processing Toolbox 6.21.
 * Generated on: 21-Dec-2015 10:20:34
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 4
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2014a\extern\include\tmwtypes.h 
 */
#define MWSPT_NSEC 9
const int NL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1 };
const real64_T NUM[MWSPT_NSEC][3] = {
  {
    0.02043947882985,                 0,                 0 
  },
  {
                   1,                 0,                -1 
  },
  {
    0.02043947882985,                 0,                 0 
  },
  {
                   1,                 0,                -1 
  },
  {
    0.02021881641525,                 0,                 0 
  },
  {
                   1,                 0,                -1 
  },
  {
    0.02021881641525,                 0,                 0 
  },
  {
                   1,                 0,                -1 
  },
  {
                   1,                 0,                 0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1 };
const real64_T DEN[MWSPT_NSEC][3] = {
  {
                   1,                 0,                 0 
  },
  {
                   1,    -1.81768444585,   0.9836465239584 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.847929303926,   0.9850722601925 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.806715933748,   0.9619429222893 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.819862361978,   0.9633409060843 
  },
  {
                   1,                 0,                 0 
  }
};
