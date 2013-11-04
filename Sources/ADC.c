#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative information */

#include "ADC.h"

int ADC_conversion_complete(ADC* this){ 
    return ATDSTAT0&(1<<7);
}

void ADC_run(ADC* this){
   ATDCTL5 = this->atdctl5_init; //trigger conversion
   while(!ADC_conversion_complete(this)){
      //this is an empty loop
   }
   return;
}

/*returns a value for a given port.
port must be <= 0 and >= 3*/
int ADC_get_value(ADC* this, int port){
	return ATDDR[port];
}


void ADC_init(ADC* this){
	this->atdctl2_init = (1<<7); //ATD power up
	this->atdctl3_init = 0x00; 
	//16 clock period for conversion
	this->atdctl4_init = (3<<5) | (1<<0);
	//right justified result, and sample multiple channels
	this->atdctl5_init = (1<<7) | (3<<4); 

	ATDCTL2 = this->atdctl2_init;
	ATDCTL3 = this->atdctl3_init;
	ATDCTL4 = this->atdctl4_init;
	ATDDIEN = 0;
}