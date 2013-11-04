#ifndef STATES_H
#define STATES_H

#include "Types.h"
#include "ADC.h"
#include "Timing.h"
#include "Timer.h"
#include "PID.h"
#include "PWM.h"
#include "Timer.h"
#include "Motor.h"

#define STATE_PICKUP 0
#define STATE_CW 1
#define STATE_CCW 2
#define STATE_DROP 3

typedef struct StateMachine StateMachine;

struct StateMachine {
 Timing* timing;
 Timer timer_s; //StateMachine has its own timer
 Timer* timer;
 Motor* motor
 ADC* adc; 
 int last_state;
 int current_state;
};

void StateMachine_init(StateMachine* this,
Timing* timing,
 Motor* motor,
 ADC* adc); 
void StateMachine_run(StateMachine* this);
void StateMachine_printstate(StateMachine* this, int state);

void state_pickup (StateMachine* this);
void state_cw (StateMachine* this);
void state_ccw (StateMachine* this);
void state_drop (StateMachine* this);

#endif //STATES_H