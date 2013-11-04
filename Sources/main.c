#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative information */
#include <TermIO.h>
#include <stdio.h>
#include "limits.h"
#include <stdlib.h>

#include "Utilities.h"
#include "Types.h"
#include "ADC.h"
#include "Timing.h"
#include "Timer.h"
#include "PID.h"
#include "PWM.h"
#include "Timer.h"
#include "States.h"
#include "Motor.h"

#define PRESCALER (3) // Prescale value mask (0-7)

void Timer_test() {
  Timing timing;
  Timer timer;
  
  Timing_init(&timing, PRESCALER);
  Timer_init(&timer, &timing);
  
  delay(125);
  
  for(;;){
    Timer_update(&timer);
   printf("Seconds: %f\n", Timer_get_seconds(&timer));
    delay(125);
  }
}

void PID_test() {
  float seconds, pid_output, measured_val;
  int i;
  Timing timing_s;
  Timing* timing = &timing_s;
  Timer timer;
  PID pid_s;
  PID* pid = &pid_s;
  long int clockrate; 
  
  PID_init(pid, 3.7f, 1.0f, 0.0f);
  
  
  
  Timing_init(timing, PRESCALER);
  Timer_init(&timer, timing);

  delay(100);
  
  i=2;
  
  measured_val = 0.0;
  PID_set_setpoint(pid, 0.0);
  pid_output = PID_update(pid, measured_val, 1.0);
  PID_set_setpoint(pid, 1.0);
  for(;;) {
      Timer_update(&timer);
      measured_val += 0.05;
	    printf("dt: %f pid_output: %f measured: %f\n", Timer_get_seconds(&timer), pid_output, measured_val);
	    pid_output = PID_update(pid, measured_val, Timer_get_seconds(&timer));
	    SET_MOTOR(bound_f(pid_output, -1.0f, 1.0f));
	    delay(120);
         
  } // loop forever
}

void PID_PWM_ADC_test() {
  float seconds, pid_output, measured_val;
  int i;
  long int clockrate; 
  
  ADC adc_s;
  ADC* adc = &adc_s; 
  Timing timing_s;
  Timing* timing = &timing_s;
  Timer timer_s;
  Timer* timer = &timer_s;
  PID pid_s;
  PID* pid = &pid_s;
  
  PID_init(pid, 1.0f, 0.0f, 0.0f);
  ADC_init(adc);
  Timing_init(timing, PRESCALER);
  Timer_init(timer, timing);

  delay(100);
  
  i=2;
  
  measured_val = 0.0;
  PID_set_setpoint(pid, 0.0);
  pid_output = PID_update(pid, measured_val, 1.0);
  PID_set_setpoint(pid, 1.0);
  for(;;) {
      ADC_run(adc);
      for(i=0;i<4;i++){   //only using 4 ports1
        printf("port%d:%d\r\n", i, ADC_get_value(adc, i));
      }
      
      Timer_update(timer);
      measured_val += 0.05;
	    printf("dt: %f pid_output: %f measured: %f\n", Timer_get_seconds(timer), pid_output, measured_val);
	    pid_output = PID_update(pid, measured_val, Timer_get_seconds(timer));
	    SET_MOTOR(bound_f(pid_output, -1.0f, 1.0f));
	    delay(120);
         
  } // loop forever
}

void StateMachine_test(){
  float seconds, pid_output, measured_val;
  int i;
  long int clockrate; 
  
  ADC adc_s;
  ADC* adc = &adc_s; 
  Timing timing_s;
  Timing* timing = &timing_s;
  Motor motor_s;
  Motor* motor = &motor_s;
  PID pid_s;
  PID* pid = &pid_s;
  StateMachine statemachine_s;
  StateMachine* statemachine = &statemachine_s;
  
  PWM_init();
  ADC_init(adc); 
  Timing_init(timing, PRESCALER);
  Motor_init(motor, timing);
  StateMachine_init(statemachine, timing, motor, adc);
  
  delay(100);
 
  for(;;){
    StateMachine_run(statemachine);
  }
}

void ADC_test(){
  int i;
  ADC adc_s;
  ADC* adc = &adc_s;
  
  ADC_init(adc);
  delay(100);
  for(;;){
   ADC_run(adc);
   for(i=1;i<2;i++){
     printf("sensor %d: %d\n", i, ADC_get_value(adc, i));
   }
  
   delay(120);
  }
}

void main(void) {
  TERMIO_Init();
  //ADC_test();
  StateMachine_test();
}

