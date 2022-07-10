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


//Controlling motor direction (2 pins)
void DCM_voidRotateCCW()
{
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN4, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN5, GPIO_PIN_HIGH);
}
void DCM_voidRotateCW()
{
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN4, GPIO_PIN_HIGH);
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN5, GPIO_PIN_LOW);
}
void DCM_voidStop2()
{
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN4, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN5, GPIO_PIN_LOW);
}

//Controlling motor from 1 pin (1 direction)
void DCM_voidRotate()
{
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN5, GPIO_PIN_HIGH);
}
void DCM_voidStop()
{
	GPIO_u8SetPinValue(DCM_PORTA, DCM_PIN5, GPIO_PIN_LOW);
}

//Motor feedback


//u8 DCM_voidReadEncoder(DCM_t* Copy_pDCM_tStructMotor){
//	u8 ENCA_PIN_VALUE=0;
//	u8 Local_FB =0;
//
//	GPIO_u8GetPinValue(DCM_PORTA , Copy_pDCM_tStructMotor->DCM_u8PinENCA , &ENCA_PIN_VALUE);
//
//	if(ENCA_PIN_VALUE !=0)
//		Local_FB = DCM_u8DetectDirection(Copy_pDCM_tStructMotor);
//	return Local_FB;
//}




//Motor feedback
u8 DCM_u8DetectDirection(){
  u8 ENCB_PIN_VALUE=0;

  GPIO_u8GetPinValue(DCM_PORTA , DCM_PIN2 , &ENCB_PIN_VALUE);
  if(ENCB_PIN_VALUE > 0)
    return DCM_DIR_CCW;

  else
    return DCM_DIR_CW;
}

//u8 DCM_voidReadEncoder(DCM_t* Copy_pDCM_tStructMotor){
//	u8 ENCA_PIN_VALUE=0;
//	u8 Local_FB =0;
//
//	GPIO_u8GetPinValue(DCM_PORTA , Copy_pDCM_tStructMotor->DCM_u8PinENCA , &ENCA_PIN_VALUE);
//
//	if(ENCA_PIN_VALUE !=0)
//		Local_FB = DCM_u8DetectDirection(Copy_pDCM_tStructMotor);
//	return Local_FB;
//}
