#include "PID.h"
#include "Types.h"
#include <TermIO.h>
#include <stdio.h>

#define DEFAULT_ERROR 1.0f

//push an error onto the previous error stack
//and rotate all the previous errors
void PID_push_prev_error(PID* this, float error){
  int i;
  float previous_error;
  for(i=0;i<(MAX_PREV_ERRORS - 1);i++){
    this->previous_errors[i+1] = this->previous_errors[i];
  }
  this->previous_errors[0]=error;
}

float PID_get_avg_error(PID* this){
 int i;
 float sum;
 sum=0.0f;
 for(i=0;i<MAX_PREV_ERRORS;i++){
  sum += this->previous_errors[i];
 }
 return sum/((float)MAX_PREV_ERRORS);
}

float PID_get_prev_error(PID* this){
 return this->previous_errors[0]; 
}

 //set all previous errors on the stack to DEFAULT_ERROR
void PID_clear_prev_errors(PID* this){
	int i;
	for(i=0;i<MAX_PREV_ERRORS;i++){
	  previous_errors[i] = DEFAULT_ERROR;
	} 
}

void PID_init(PID* this, float Kp, float Ki, float Kd, float SS_threshold){
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	this->setpoint = 0;
	this->derivative = 0;
	this->integral = 0;
	
	PID_clear_prev_errors(this);
	
	this->is_SS = 0;
	this->SS_threshold;
}

/*Should I be keeping track of dt in here?*/
float PID_update(PID* this, float measured_value, float dt) {
  float return_value = 0;
	float error = this->setpoint - measured_value;
	this->integral = this->integral + error*dt;
	
	//need to multiply numerator by 1000?
	this->derivative = (error - PID_get_prev_error(this))/dt;
	PID_push_prev_error(this, error);
	
	
	//calculate is steady state...
	if(PID_get_avg_error(this) < this->SS_threshold){
	 this->is_SS = 1; 
	}
	
	return_value += this->Kp * error;
	return_value +=	this->Ki * this->integral;
	return_value += this->Kd * this->derivative;
	return return_value;
}
/*sensor input 0 -> 426*/

void PID_set_setpoint(PID* this, float setpoint) {
	this->setpoint = setpoint;
	this->steady_state = 0;
	PID_clear_prev_errors(this);
}

float PID_get_Kp(PID* this){
  return this->Kp;
}

void PID_set_Kp(PID* this, float Kp){
  this->Kp = Kp;
}
void PID_set_Ki(PID* this, float Ki){
  this->Ki = Ki;
}
void PID_set_Kd(PID* this, float Kd){
  this->Kd
}

//returns a boolean depending on whether the PID is in a steady state
char PID_is_steady_state(PID* this){
  return this->is_SS;
}
  
