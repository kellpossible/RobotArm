#include "Utilities.h"
#include "ADC.h"

#include <TermIO.h>
#include <stdio.h>

float bound_f(float input, float min, float max){
 if (input >= max){
  return max;
 }
 
 if (input <= min){
  return min;
 }
 return input;
}

//returns sensor value in degrees
//340 raw 0 deg
//470 raw 90 deg
#define ZERO_ANGLE 340.0f
#define NINETY_ANGLE 470.0f
float get_motor_angle(ADC* adc){
  int raw_sensor_val;
  float retval, scale;
  scale = 90.0f/((float)(NINETY_ANGLE - ZERO_ANGLE));
  ADC_run(adc);
  raw_sensor_val = ADC_get_value(adc, 2);
  retval = (((float)raw_sensor_val)-ZERO_ANGLE)*scale;
  //printf("Sensorf: %f Sensori: %d\n", retval, raw_sensor_val);
  return retval;
}

