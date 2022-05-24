/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):DC motor 		 **********************/
/***********************   DATA : 24-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "STD_TYPES.h"
#include "GPIO_interface.h"

#include "DCMOTOR_config.h"
#include "DCMOTOR_interface.h"
#include "DCMOTOR_private.h"


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

void DCMOTOR_vidReadEncoder(){
  int ENCB_VALUE=0;
  GPIO_u8GetPinValue(PWMPORT , ENCB , ENCB_VALUE);
  if(ENCB_VALUE > 0){
    Count_pulses++;
  }
  else{
    Count_pulses--;
  }
}
void DCMOTOR_vidIRQHandler(void){
	if(ENCA !=0){
		MOTOR_CallBack();
	}
	else
	
}

u8 CAN_u8CallBackFunc(void(*pv_CallBack)(void))
{	u8 Local_u8ErrorState  = OK;

	if (pv_CallBack != NULL)
	{
		MOTOR_CallBack = pv_CallBack;
	}
		//Wrong Input
	else
		Local_u8ErrorState  = NOK;

	return Local_u8ErrorState ;
}