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
void DCM_voidRotateCCW(DCM_t* Copy_pDCM_tStructMotor)
{
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinB, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinA, GPIO_PIN_HIGH);
}
void DCM_voidRotateCW(DCM_t* Copy_pDCM_tStructMotor)
{
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinB, GPIO_PIN_HIGH);
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinA, GPIO_PIN_LOW);
}
void DCM_voidStop2(DCM_t* Copy_pDCM_tStructMotor)
{
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinB, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinA, GPIO_PIN_LOW);
}

//Controlling motor from 1 pin (1 direction)
void DCM_voidRotate(DCM_t* Copy_pDCM_tStructMotor)
{
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinA, GPIO_PIN_HIGH);
}
void DCM_voidStop(DCM_t* Copy_pDCM_tStructMotor)
{
	GPIO_u8SetPinValue(Copy_pDCM_tStructMotor->DCM_u8Port, Copy_pDCM_tStructMotor->DCM_u8PinA, GPIO_PIN_LOW);
}