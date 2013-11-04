
#include "Types.h"
//gcf

#ifndef PWM_H_

#define PWM_H_

void PWM_init(void);    //initializes PWM
void CW_MOTOR_PWM(U8);        //takes an int between 0-100 and sets PWm to that duty cycle clockwise
void CCW_MOTOR_PWM(U8);
void BREAK_MOTOR(void);       //Breaks motor
void ENABLE_MAGNET();
void DISABLE_MAGNET();
void SET_MOTOR(float value);

//#define DEBUG_PWM

#endif 

