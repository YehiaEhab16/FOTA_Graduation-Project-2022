/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "CAN_interface.h"

#include "SW_interface.h"
#include "LED_interface.h"
#include "BZR_interface.h"
#include "DCM_interface.h"
#include "TMP_interface.h"
#include "USN_interface.h"

#include "../OS/org/Source/include/queue.h"

#include "Tasks.h"

//LEDs
LED_t Global_LED_tRed = {LED_PORTA,LED_PIN1,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tForward =  {SW_PORTA,SW_PIN2,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTA,SW_PIN3,SW_PULL_UP};

//Motors
DCM_t Global_DCM_tRightMotor = {DCM_PORTA,DCM_PIN4,DCM_PIN5};
DCM_t Global_DCM_tLeftMotor = {DCM_PORTA,DCM_PIN6,DCM_PIN7};

//Queues
xQueueHandle Global_xQueueHandleDistance=0;
xQueueHandle Global_xQueueHandleDirection=0;
xQueueHandle Global_xQueueHandleTemperature=0;
xQueueHandle Global_xQueueMainRequest=0;

//Create Queues
Global_xQueueHandleDistance =    xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
Global_xQueueHandleDirection =   xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
Global_xQueueHandleTemperature = xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
Global_xQueueMainRequest =		 xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);

//Activating LED and Buzzer
void Task_voidAlert(void)
{
	u8 Local_u8Dist;
	while(1)
	{	xQueueRecieve(Global_xQueueHandleDistance,&Local_u8Dist,QUEUE_READ_TIME);
		if(Local_u8Dist<DIST_THRESHOLD)
		{
			BZR_voidOn(BZR_PORTA,BZR_PIN0);
			LED_voidLedOn(&Global_LED_tRed);
		}
	}
}

//Reading Direction from 2 switches
void Task_voidReadDirection(void)
{
	u8 Local_u8Dir;
	while(1)
	{
		if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
			Local_u8Dir=FORWARD;
		else if(SW_u8ReadSwitch(Global_SW_tBackward)==PRESSED)
			Local_u8Dir=BACKWARD;
		else
			Local_u8Dir=STOP;
		
		xQueueSendToFront(Global_xQueueHandleDirection,&Local_u8Dir,QUEUE_WRITE_TIME);
	}
}

//Reading Temperature from LM35
void Task_voidReadTemperature(void)
{
	u8 Local_u8TempVal;
	while(1)
	{
		TMP_u8ReadValue(&Local_u8TempVal);
		xQueueSendToFront(Global_xQueueHandleTemperature,&Local_u8TempVal,QUEUE_WRITE_TIME);
	}
}

//Reading Dstance from Ultrasonic
void Task_voidReadDistance(void)
{
	u8 Local_u8DistVal;
	while(1)
	{
		USN_u8ReadDistance(&Local_u8DistVal);
		xQueueSendToFront(Global_xQueueHandleDistance,&Local_u8DistVal,QUEUE_WRITE_TIME);
	}
}

//Forward and backward motion
void Task_voidMoveVehicle(void)
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
void Task_voidSystemCheck(void)
{
	while(1)
	{

	}
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{
	while(1)
	{
		
	}
}


