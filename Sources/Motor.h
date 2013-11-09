#ifndef MOTOR_H
#define MOTOR_H

#include "PID.h"
#include "Timer.h"
#include "Timing.h"
#include "ADC.h"

struct Motor {
 PID pid_s; //each motor has its own pid
 PID* pid;
 Timer timer_s; //each motor has its own timer
 Timer* timer;
 ADC* adc;
 int adc_port;
};

typedef struct Motor Motor;

void Motor_init(Motor* this, Timing* timing, 
ADC* adc, int adc_port);
PID* Motor_get_pid(Motor* this);
void Motor_set_angle(Motor* this, float target_angle);
float Motor_get_angle(Motor* this);
void Motor_break(Motor* this);
void Motor_set_accuracy(Motor* this, float accuracy);

#endif //MOTOR_H