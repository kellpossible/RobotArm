#include "Types.h"
#include "PWM.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"

#include <TermIO.h>
#include <stdio.h>

void PWM_init(){
//Initialization of PWM2 (Port T 2)
#ifndef DEBUG_PWM
PWME_PWME2        = 0;      //disables PWME2

MODRR_MODRR2      = 1;      //Set Port T 2 as output

PWMPRCLK_PCKB0    = 1;      //Set prescaler to divide by 2 of bus speed (Unknown)

PWMCLK_PCLK2      = 0;      //Seleckt PWMclk to be scaled by scaled b

PWMPOL_PPOL2      = 0;      //Starts low goes high NEEDS TEST

PWMCAE_CAE2       = 0;      //Set mode to be left aligned

PWMPER2           = 200;    //Sets Period to be 400

PWMDTY2           = 0;     //Sets dutycycle to 0%



//Initialization of PWM3 (Port T 3)
PWME_PWME3        = 0;      //disables PWME3

MODRR_MODRR3      = 1;      //Set Port T 3 as output

PWMCLK_PCLK3      = 0;      //seleckt clk scaled b

PWMPOL_PPOL3      = 0;     //Starts low goes high NEEDS TEST

PWMCAE_CAE3       = 0;     //Set mode to be left aligned

PWMPER3           = 200;   //Sets Period to be 400

PWMDTY3           = 0;     //Sets dutycycle to 0% 


//Initialization of PWM2 (Port T 0)

PWME_PWME0        = 0;      //disables PWME0

MODRR_MODRR0      = 1;      //Set Port T 0 as output

PWMPRCLK_PCKA0    = 1;      //Set prescaler to divide by 2 of bus speed (Unknown)

PWMCLK_PCLK0      = 0;      //Seleckt PWMclk to be scaled by scaled A

PWMPOL_PPOL0      = 0;      //Starts low goes high NEEDS TEST

PWMCAE_CAE0       = 0;      //Set mode to be left aligned

PWMPER0           = 200;    //Sets Period to be 400

PWMDTY0           = 0;     //Sets dutycycle to 0%



//Initialization of PWM1 (Port T 1)
PWME_PWME1        = 0;      //disables PWME1

MODRR_MODRR1      = 1;      //Set Port T 1 as output

PWMCLK_PCLK1      = 0;      //seleckt clk scaled A

PWMPOL_PPOL1      = 0;     //Starts low goes high NEEDS TEST

PWMCAE_CAE1       = 0;     //Set mode to be left aligned

PWMPER1           = 200;   //Sets Period to be 400

PWMDTY1           = 0;     //Sets dutycycle to 0%
#endif //DEBUG_PWM 
}

//Clockwise PWM. Takes an dutycycle as input 0-100
void CW_MOTOR_PWM(U8 dty){
PWME_PWME2    = 0;
PWME_PWME3    = 0;
PWMDTY2         = dty/2;   //Sets PWM duty cycle for CW direction
PWMDTY3         = 0;     //Set duty csycle to low in CCW direction


PWME_PWME2    = 1;
PWME_PWME3    = 0;


}

//Counterclockwise PWM. Takes an dutycycle as input 0-100
void CCW_MOTOR_PWM(U8 dty){
PWME_PWME2    = 0;
PWME_PWME3    = 0;

PWMDTY2         = 0;   //Sets PWM duty cycle for CW direction
PWMDTY3         = dty/2;     //Set duty cycle to low in CCW direction


PWME_PWME2    = 0;
PWME_PWME3    = 1;

}

void BREAK_MOTOR(){

PWMDTY2   =   0;        //Set duty cycle to low in CW direction
PWMDTY3   =   0;        //Set duty cycle to low in CCW direction
}

//value is between -1 and 1. Sign indicates motor direction.
void SET_MOTOR(float value){
  U8 dty;
  if(value == 0.0f){
    printf("BREAK");
    //BREAK_MOTOR();
    return;
  }
  
  if(value>0.0f){
    dty = (U8)(value*80.0f);
    #ifdef DEBUG_PWM
    printf("input: %f CW dty:%d\n", value, (int)dty);
    #else
    CW_MOTOR_PWM(dty);
    #endif
  }
  if(value<0.0f){
    dty = (U8)(-value*80.0f);
    #ifdef DEBUG_PWM
    printf("input: %f CCW dty:%d\n", value, (int)dty);
    #else
    CCW_MOTOR_PWM(dty);
    #endif
  }
}

void ENABLE_MAGNET(){
PWME_PWME0    = 0;
PWME_PWME1    = 0;

PWMDTY0         = 0;   //Sets PWM duty cycle for CW direction
PWMDTY1         = 200;     //Set duty cycle to low in CCW direction


PWME_PWME0    = 0;
PWME_PWME1    = 1;  
}

void DISABLE_MAGNET(){
PWME_PWME0    = 0;
PWME_PWME1    = 0;

PWMDTY0         = 0;     //Sets PWM duty cycle for CW direction
PWMDTY1         = 0;     //Set duty cycle to low in CCW direction
}