#ifndef ADC_H_
#define ADC_H_

#include "Types.h"

#define ATDDR ((volatile U16*) 0x090)
#define MAX_AVG 8

struct ADC {
	int avg[MAX_AVG];
	int calculated_avg;
	char avg_port;
};

typedef struct ADC ADC;

int ADC_conversion_complete(ADC* this);
void ADC_run(ADC* this, char calc_avg);
int ADC_get_value(ADC* this, char port);
void ADC_init(ADC* this);

int ADC_calc_avg(ADC* this);
void ADC_push_value(ADC* this, int value);

#endif //ADC_H_