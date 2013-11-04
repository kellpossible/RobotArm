#include "States.h"

#include "Utilities.h"
#include "Types.h"
#include "ADC.h"
#include "Timing.h"
#include "Timer.h"
#include "PID.h"
#include "PWM.h"
#include "Timer.h"
#include "Motor.h"

#include <TermIO.h>
#include <stdio.h>

void StateMachine_init(StateMachine* this,
Timing* timing,
 Motor* motor,
 ADC* adc){
  this->timing = timing;
  this->timer = &(this->timer_s);
  Timer_init(this->timer, this->timing);
  this->adc = adc;
  this->motor = motor;
  this->last_state = STATE_PICKUP;
  this->current_state = STATE_CW;
 }
 
//switch to a new state 
void StateMachine_switch_state(StateMachine* this, int new_state){
  this->last_state = this->current_state; //sets this state as the last state
  this->current_state = new_state;
}


void StateMachine_printstate(StateMachine* this, int state){
  switch(this->current_state){
    case STATE_PICKUP:
      printf("STATE_PICKUP\n");
      return;
    case STATE_CW:
      printf("STATE_CW\n"); 
      return;
    case STATE_CCW:
      printf("STATE_CCW\n");
      return;
    case STATE_DROP:
      printf("STATE_DROP\n");
      return;
  }
}

void StateMachine_run(StateMachine* this){
//todo should probably switch to function pointers
//to represent the state switching
  printf("Current State: ");
  StateMachine_printstate(this, this->current_state);
  switch(this->current_state){
    case STATE_PICKUP:
      state_pickup(this);
      return;
    case STATE_CW:
      state_cw(this); 
      return;
    case STATE_CCW:
      state_ccw(this);
      return;
    case STATE_DROP:
      state_drop(this);
      return;
  }
}

//state where the magnet is getting picked up
void state_pickup (StateMachine* this){
  printf("Running state PICKUP\n");
  delay(500);
  StateMachine_switch_state(this, STATE_CW);
}

//state where the arm is moving clockwise
void state_cw (StateMachine* this){
  printf("Running state CW\n");
  
  Motor_set_angle(this->motor, 0.0f);
  
  StateMachine_switch_state(this, STATE_DROP);
}

//state where the arm is moving counter-clockwise
void state_ccw (StateMachine* this){
  printf("Running state CCW\n");
  
  Motor_set_angle(this->motor, 90.0f);
  
  StateMachine_switch_state(this, STATE_PICKUP);
}

//state where the arm is moving counter-clockwise
void state_drop (StateMachine* this){
  printf("Running state DROP\n");
  
  delay(500);
  StateMachine_switch_state(this, STATE_CCW);
}
