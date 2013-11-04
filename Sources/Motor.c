#include "Motor.h"
#include "PID.h"
#include "Timer.h"
#include "Timing.h"
#include "PWM.h"

void Motor_init(Motor* this, Timing* timing, 
ADC* adc, int adc_port){
 this->pid = &(this->pid_s)
 //default motor pid
 PID_init(this->pid, 1.0f, 0.0f, 0.0f, 0.5f); 
 this->timer = &(this->timer_s);
 Timer_init(this->timer, timing);
 this->adc = adc;
 this->adc_port = adc_port;
}

PID* Motor_get_pid(Motor* this){
  return this->pid;
}

/* Would be good to have this spawn a new thread 
or use a Motor_update() to make this non-blocking*/
//run a pid to turn the motor to the specific angle
void Motor_set_angle(Motor* this, float target_angle){
  float sensor_angle, pid_output;
  
  PID_set_setpoint(this->pid, target_angle);
  
  for(;;){
   Timer_update(this->timer);
   sensor_angle = get_motor_angle(this->adc);
   pid_output = PID_update(this->pid, sensor_angle, Timer_get_seconds(this->timer));
   
   //TODO: make PWM module allow for multiple motors
   //so SET_MOTOR(int pwm_port_for_motor ...);
   SET_MOTOR(bound_f(pid_output, -1.0f, 1.0f));
    
   
   //stop this loop when PID reaches steady state
   if(PID_is_steady_state(this->pid)){
    break;
   }
  }
}

//returns sensor value in degrees
//340 raw 0 deg
//470 raw 90 deg
#define ZERO_ANGLE 340.0f
#define NINETY_ANGLE 470.0f
float Motor_get_angle(Motor* this){
  int raw_sensor_val;
  float retval, scale;
  scale = 90.0f/((float)(NINETY_ANGLE - ZERO_ANGLE));
  ADC_run(this->adc);
  raw_sensor_val = ADC_get_value(this->adc, 2);
  retval = (((float)raw_sensor_val)-ZERO_ANGLE)*scale;
  //printf("Sensorf: %f Sensori: %d\n", retval, raw_sensor_val);
  return retval;
}
