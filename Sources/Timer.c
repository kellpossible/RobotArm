#include "Timer.h"
#include "Timing.h"

/*Initialises and starts the timer*/
void Timer_init(Timer* this, Timing* timing){
	this->timing = timing;
	Timer_reset(this);
	this->t1 = Timing_get_count(this->timing);
}

/*resets the timer*/
void Timer_reset(Timer* this){
	this->t1 = 0;
	this->t2 = 0;
	this->count = 0;
}

/*updates the timer value*/
void Timer_update(Timer* this){
	this->t2 = Timing_get_count(this->timing);
	this->count = calc_tcnt_diff(this->t1, this->t2);
	this->t1 = this->t2;
}

/*gets the timer value in seconds*/
float Timer_get_seconds(Timer* this){
	return Timing_tcnt_to_seconds(this->timing, this->count);
}

/*gets the timer count*/
unsigned int Timer_get_count(Timer* this){
	return this->count;
}
