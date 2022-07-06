
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "motor.h"

u8 Count_pulses=0;
void (*MOTOR_CallBack)(void) = NULL;






void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  GPIO_u8SetPinValue (PWMPORT, PWM_PIN,Copy_u16PWMValue);  //this pin is analog pin
  if(dir == 1){
    GPIO_u8SetPinValue (PWMPORT, DR1_PIN, HIGH);  
	GPIO_u8SetPinValue (PWMPORT, DR2_PIN, LOW);  

  }
  else if(dir == -1){
    GPIO_u8SetPinValue (PWMPORT, DR1_PIN, LOW );  
	GPIO_u8SetPinValue (PWMPORT, DR2_PIN, HIGH);  
  }
  else{
	GPIO_u8SetPinValue (PWMPORT, DR1_PIN, LOW);  
	GPIO_u8SetPinValue (PWMPORT, DR2_PIN, LOW);  
  }  
}

void readEncoder(){
  int ENCB_VALUE=0;
  GPIO_u8GetPinValue(PWMPORT , ENCB , ENCB_VALUE);
  if(ENCB_VALUE > 0){
    Count_pulses++;
  }
  else{
    Count_pulses--;
  }
}