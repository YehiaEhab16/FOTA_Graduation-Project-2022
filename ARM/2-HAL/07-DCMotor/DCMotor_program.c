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






void setMotor(u8 dir){
	
  
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
  u8 ENC_PIN_VALUE=0;
  GPIO_u8GetPinValue(PWMPORT , ENC_PIN , &ENC_PIN_VALUE);
  if(ENC_PIN_VALUE > 0){
    Count_pulses++;
  }
  else{
    Count_pulses--;
  }
}
void DCMOTOR_vidIRQHandler(void){
	u8 ENC_PIN_VALUE=0;
	GPIO_u8GetPinValue(PWMPORT , ENC_PIN , &ENC_PIN_VALUE);

	if(ENC_PIN_VALUE !=0){
		MOTOR_CallBack();
	}
	else
	{
		//no thing
	}
		
	
}

u8 DCMOTOR_u8CallBackFunc(void(*pv_CallBack)(void))
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