#ifndef TIMER_H
#define TIMER_H

#include "Timing.h"

struct Timer {
	unsigned int t1; //count 1
	unsigned int t2; //count 2
	unsigned int count;
	Timing* timing;
};

typedef struct Timer Timer;

void Timer_init(Timer* this, Timing* timing);
void Timer_reset(Timer* this);
void Timer_update(Timer* this);
float Timer_get_seconds(Timer* this);
unsigned int Timer_get_count(Timer* this);

#endif