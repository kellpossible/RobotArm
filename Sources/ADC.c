#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative information */

#include <TermIO.h>
#include <stdio.h>

#include "ADC.h"

int ADC_conversion_complete(ADC* this){ 
    return ATDSTAT0&(1<<7);
}

void wait_adc(ADC* this){
  ATDCTL5 = (1<<7) | (3<<4); //trigger conversion
  while(!ADC_conversion_complete(this)){
    //this is an empty loop
  }
  return;
}


//boolean calculate average
void ADC_run(ADC* this, char calc_avg){
  char i;
  if(calc_avg){
    //create an array of values for avg calc
    for(i=0;i<MAX_AVG;i++){
      wait_adc(this);
      ADC_push_value(this, ATDDR[this->avg_port]);
    }
    this->calculated_avg = ADC_calc_avg(this);
  }else{
  //do normal wait until finished adc
   wait_adc(this); 
  }
}

void ADC_push_value(ADC* this, int value){
   char i;
   int prev_val;
   for(i=0;i<MAX_AVG-1;i++){
    this->avg[i+1] = this->avg[i];
   }
   this->avg[0] = value;
}

int ADC_calc_avg(ADC* this){
  char i;
  long int sum=0;
  for(i=0;i<MAX_AVG;i++){
    sum += this->avg[i];
  }
  return sum/MAX_AVG;
}

/*returns a value for a given port.
port must be <= 0 and >= 3*/
int ADC_get_value(ADC* this, char port){
  if(port == this->avg_port){
    return this->calculated_avg;
  }else{
   return ATDDR[port];
  }
}


void ADC_init(ADC* this, char avg_port){
	ATDCTL2 = (1<<7);//ATD power up
	ATDCTL3 =  0x00; 
	//16 clock period for conversion
	ATDCTL4 = (3<<5) | (1<<0);
		//right justified result, and sample multiple channels
	ATDDIEN = 0;
	
	this->calculated_avg = 0;
	this->avg_port = avg_port;
}