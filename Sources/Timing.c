#include "Timing.h"
#include "limits.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative information */

/*for debugging*/
#include <TermIO.h>
#include <stdio.h>

void Timing_init(Timing* this, int prescaler){
	this->prescaler = prescaler;
	this->clockrate = calc_timer_clockrate(prescaler);

	// Enable timer, stop in freeze or wait mode
	TSCR1 = TSCR1_TEN_MASK|TSCR1_TSWAI_MASK|TSCR1_TSFRZ_MASK;
	TSCR2 = prescaler;
}

//return the inverted TCNT
unsigned int Timing_get_count(Timing* this){
	//sizeof(unsigned int) - 1 == UINT_MAX
	return UINT_MAX - TCNT;
}

long int Timing_get_clockrate(Timing* this){
	return this->clockrate;
}

//calculates x to the power of y (x^y)
int power(int x, int y){
	int i, answer;
	if(y == 0){
		return 1;
	}
	answer = x;
	for(i=1; i<y; i++){
		answer = answer * x;
	}
	return answer;
}

//returns the clockrate of the timer using a given prescaler
long int calc_timer_clockrate(int prescaler_val){
	long int clockrate;
	long int divider;
	clockrate = 4000000;
	divider = power(2, prescaler_val);
	//printf("divider: %ld prescaler_val: %d\n", divider, prescaler_val);
	return (clockrate/divider)/10;
}

unsigned int calc_tcnt_diff(unsigned int t1, unsigned int t2){
	//allow wrap around
	if(t2<t1){
		return (UINT_MAX-t1) + t2;
	}else{
		return t2-t1;
	}
}

float Timing_tcnt_to_seconds(Timing* this, unsigned int t){
	return ((float)t)/((float)this->clockrate);
}

float Timing_get_seconds(Timing* this){
  return ((float)Timing_get_count(this))/((float)this->clockrate);
}

//todo: use the actual TCNT timer for this delay
#define TIMECAL 1000
void delay(int t){
  long int i, x;
  x = t;
  x *= TIMECAL;
  for(i=0;i<x;i++){
  }
}