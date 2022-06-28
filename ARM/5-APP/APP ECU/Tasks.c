/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
//#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"

#include "../../4-FreeRTOS/OS/org/Source/include/FreeRTOS.h"
#include "../../4-FreeRTOS/OS/org/Source/include/queue.h"

#include "Tasks.h"


//LEDs
LED_t Global_LED_tRed = {LED_PORTB,LED_PIN1,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tForward =  {SW_PORTB,SW_PIN2,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTB,SW_PIN3,SW_PULL_UP};

//Motors
DCM_t Global_DCM_tRightMotor = {DCM_PORTB,DCM_PIN4,DCM_PIN5};
DCM_t Global_DCM_tLeftMotor = {DCM_PORTB,DCM_PIN6,DCM_PIN7};

//Queues
xQueueHandle Global_xQueueHandleDistance;
xQueueHandle Global_xQueueHandleDirection;
xQueueHandle Global_xQueueHandleTemperature;
xQueueHandle Global_xQueueMainRequest;


void Task_voidCreateQueue (void)
{

	Global_xQueueHandleDistance =    xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueHandleDirection =   xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueHandleTemperature = xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueMainRequest =		 xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
}
//Activating LED and Buzzer
void Task_voidAlert(void * parms)
{
	u8 Local_u8Dist=255;
	while(1)
	{
		LED_voidLedOn(&Global_LED_tRed);
		xQueueReceive(Global_xQueueHandleDistance,&Local_u8Dist,QUEUE_READ_TIME);
		if(Local_u8Dist<DIST_THRESHOLD)
		{
			BZR_voidOn(BZR_PORTA,BZR_PIN0);
		}
	}
}

//Reading Direction from 2 switches
void Task_voidReadDirection(void * parms)
{
	u8 Local_u8Dir;
	while(1)
	{
		if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
			Local_u8Dir=FORWARD;
		else if(SW_u8ReadSwitch(&Global_SW_tBackward)==PRESSED)
			Local_u8Dir=BACKWARD;
		else
			Local_u8Dir=STOP;
		
		xQueueSendToFront(Global_xQueueHandleDirection,&Local_u8Dir,QUEUE_WRITE_TIME);
	}
}

//Reading Temperature from LM35
void Task_voidReadTemperature(void * parms)
{
	u8 Local_u8TempVal;
	while(1)
	{
		TMP_u8ReadValue(&Local_u8TempVal);
		xQueueSendToFront(Global_xQueueHandleTemperature,&Local_u8TempVal,QUEUE_WRITE_TIME);
	}
}

//Reading Dstance from Ultrasonic
void Task_voidReadDistance(void * parms)
{
	u8 Local_u8DistVal=255;
	while(1)
	{
		//USN_u8ReadDistance(&Local_u8DistVal);
		xQueueSendToFront(Global_xQueueHandleDistance,&Local_u8DistVal,QUEUE_WRITE_TIME);
	}
}

//Forward and backward motion
void Task_voidMoveVehicle(void * parms)
{
	u8 Local_u8Dir;
	while(1)
	{
		xQueuePeek(Global_xQueueHandleDirection,&Local_u8Dir,QUEUE_READ_TIME);
		if(Local_u8Dir==FORWARD)
		{
			DCM_voidRotateCCW(&Global_DCM_tRightMotor);
			DCM_voidRotateCCW(&Global_DCM_tLeftMotor);
		}
		else if(Local_u8Dir==BACKWARD)
		{
			DCM_voidRotateCW(&Global_DCM_tRightMotor);
			DCM_voidRotateCW(&Global_DCM_tLeftMotor);
		}
		else if(Local_u8Dir==STOP)
		{
			DCM_voidStop2(&Global_DCM_tRightMotor);
			DCM_voidStop2(&Global_DCM_tLeftMotor);
		}
	}
}

//Diagnostics Check
void Task_voidSystemCheck(void * parms)
{
	while(1)
	{

	}
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void * parms)
{
	while(1)
	{
		
	}
}

