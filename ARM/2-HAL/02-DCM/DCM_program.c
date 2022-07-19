/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):DCM 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Functions Implementation */
#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "DCM_config.h"
#include "DCM_interface.h"
#include "DCM_private.h"


u8 Global_u8MotorFeedback=0;
u8 Global_u8Counter1 =DCM_INITIAL_VALUE;
DCM_t Global_DCM_tMotor;

//Controlling motor direction (2 pins)
void DCM_voidRotateCCW(void)
{
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinB, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinA, GPIO_PIN_HIGH);
}
void DCM_voidRotateCW(void)
{
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinB, GPIO_PIN_HIGH);
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinA, GPIO_PIN_LOW);
}
void DCM_voidStop2(void)
{
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinA, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinB, GPIO_PIN_LOW);}

//Controlling motor from 1 pin (1 direction)
void DCM_voidRotate(void)
{
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinA, GPIO_PIN_HIGH);
}
void DCM_voidStop(void)
{
	GPIO_u8SetPinValue(Global_DCM_tMotor.DCM_u8Port, Global_DCM_tMotor.DCM_u8PinA, GPIO_PIN_LOW);
}

//Initialize Encoder
void DCM_voidInit(DCM_t* Copy_pDCM_tStructMotor)
{
	Global_DCM_tMotor = *Copy_pDCM_tStructMotor;
}

//Motor feedback
u8 DCM_u8DetectDirection(void){
  u8 ENCB_PIN_VALUE=0;

  GPIO_u8GetPinValue(Global_DCM_tMotor.DCM_u8Port , Global_DCM_tMotor.DCM_u8PinENCB , &ENCB_PIN_VALUE);

  if(ENCB_PIN_VALUE > 0)
  {
	  Global_u8Counter1++;
	  if (Global_u8Counter1 > DCM_INITIAL_VALUE+DCM_OFFEST-1)
	  {
		  Global_u8Counter1=DCM_INITIAL_VALUE;
		  return DCM_DIR_CCW;
	  }
  }
  else
  {
	  Global_u8Counter1--;
	  if (Global_u8Counter1 < DCM_INITIAL_VALUE-DCM_OFFEST+1)
	  {
		  Global_u8Counter1=DCM_INITIAL_VALUE;
		  return DCM_DIR_CW;
	  }
  }

  return DCM_IDLE;
}

void DCM_voidMotorISR(void)
{
	Global_u8MotorFeedback = DCM_u8DetectDirection();
}
