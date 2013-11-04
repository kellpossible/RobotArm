/*****************************************************
Termio.c for 9S12C32/128 family
 *****************************************************/

#include <termio.h>
#include "derivative.h"      /* derivative-specific definitions */

char TERMIO_GetChar(void) {
   /* receives character from the terminal channel */
   while (!SCISR1_RDRF){ /* wait for input char */
      };
   return SCIDRL; 
}

void TERMIO_PutChar(char ch) {
   /* sends a character to the terminal channel */
   while (!SCISR1_TDRE) { /* wait for output buffer empty */
      };    
   SCIDRL = ch;
}
    
#define CRYSTAL_FREQ (8000000UL)      // External Crystal used
#define BUS_FREQ     (CRYSTAL_FREQ/2) // Bus freq. derived from external Crystal
#define BAUD_RATE    (19200UL)        // Desired serial baud rate
#define BAUDDIVIDER  (BUS_FREQ/(16*BAUD_RATE))

void TERMIO_Init(void) {
  /* initializes the communication channel */ 
    SCIBD     = BAUDDIVIDER;  /* set baud rate */
    SCICR2_TE = 1; /* Enable Tx */
    SCICR2_RE = 1; /* Enable Rx */
}


