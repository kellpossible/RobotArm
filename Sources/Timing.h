#ifndef TIMING_H
#define TIMING_H

//get the time as inverted TCNT
struct Timing {
	int prescaler;
	long int clockrate;
};

typedef struct Timing Timing;

void Timing_init(Timing* this, int prescaler);
unsigned int Timing_get_count(Timing* this);
float Timing_tcnt_to_seconds(Timing* this, unsigned int t);
long int Timing_get_clockrate(Timing* this);
float Timing_get_seconds(Timing* this);

long int calc_timer_clockrate(int prescaler_val);
unsigned int calc_tcnt_diff(unsigned int t1, unsigned int t2);
void delay(int t);


#endif //TIMING_H