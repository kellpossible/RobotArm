#ifndef ADC_H_
#define ADC_H_

#include "Types.h"

#define ATDDR ((volatile U16*) 0x090)


struct ADC {
	U8 atdctl2_init;
	U8 atdctl3_init;
	U8 atdctl4_init;
	U8 atdctl5_init;
};

typedef struct ADC ADC;

int ADC_conversion_complete(ADC* this);
void ADC_run(ADC* this);
int ADC_get_value(ADC* this, int port);
void ADC_init(ADC* this);

#endif //ADC_H_