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

float abs_f(float val){
  if(val < 0.0f){
    return -val;
  }else{
    return val;
  }
}
