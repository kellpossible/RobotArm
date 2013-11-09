#include "Motor.h"
#include "PID.h"
#include "Timer.h"
#include "Timing.h"
#include "PWM.h"
#include "Utilities.h"

#include <TermIO.h>
#include <stdio.h>


void Motor_init(Motor* this, Timing* timing, 
ADC* adc, int adc_port){
 this->pid = &(this->pid_s);
 //default motor pid
 //Works!!!
 //PID_init(this->pid, 0.5f, 0.0f, 0.0f, 0.4f);
 
// KD works goooooood!
 PID_init(this->pid, 1.3f, 0.0f, 2.0f, 0.2f); 
 
 //KI
 //PID_init(this->pid, 1.8f, 0.0f, 0.0f, 25.0f); 
 
 this->adc = adc;
 this->adc_port = adc_port;
}

PID* Motor_get_pid(Motor* this){
  return this->pid;
}

void Motor_set_accuracy(Motor* this, float accuracy){
  PID_set_SS_threshold(this->pid, accuracy);
}

/* Would be good to have this spawn a new thread 
or use a Motor_update() to make this non-blocking*/
//run a pid to turn the motor to the specific angle
void Motor_set_angle(Motor* this, float target_angle){
  float sensor_angle, pid_output;
  
  PID_set_setpoint(this->pid, target_angle);
  
  for(;;){
   Timer_update(this->timer);
   sensor_angle = Motor_get_angle(this);
   pid_output = PID_update(this->pid, sensor_angle, Timer_get_seconds(this->timer));
   
   //TODO: make PWM module allow for multiple motors
   //so SET_MOTOR(int pwm_port_for_motor ...);
   
   SET_MOTOR(bound_f(pid_output, -1.0f, 1.0f));
   
   //PID_print_errors(this->pid);
   
   //printf("Angle: %f\n", sensor_angle);
   
   //printf("Error: %f\n", PID_get_avg_error(this->pid));
   //printf("Avg Error: %f\n", PID_get_avg_error(this->pid));
   //printf("SS: %i\n", (int)PID_is_steady_state(this->pid));
   
   
   //if(PID_get_prev_error(this->pid) < 5.0f){
    //break;
   //}
   
   //stop this loop when PID reaches steady state
   if(PID_is_steady_state(this->pid)){
    Motor_break(this);
    break;
    }
  }
}

/* -- Sensor Calibration Values -- */
//340 raw 0 deg
#define ZERO_ANGLE 373.0f
//470 raw 180 deg
#define ONE_EIGHTY_ANGLE 590.0f

//returns sensor value in degrees
float Motor_get_angle(Motor* this){
  int raw_sensor_val;
  float retval, scale;
  scale = 180.0f/((float)(ONE_EIGHTY_ANGLE - ZERO_ANGLE));
  ADC_run(this->adc, 1);
  raw_sensor_val = ADC_get_value(this->adc, this->adc_port);
  retval = (((float)raw_sensor_val)-ZERO_ANGLE)*scale;
  //printf("Sensorf: %f Sensori: %d\n", retval, raw_sensor_val);
  return retval;
}

void Motor_break(Motor* this){
 BREAK_MOTOR(); 
}