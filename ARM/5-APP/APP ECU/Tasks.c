/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATA : 10/5/2022 			***********************/
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

#include "Tasks.h"

//LEDs
LED_t Global_LED_tRed = {LED_PORTA,LED_PIN1,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tForward =  {SW_PORTA,SW_PIN2,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTA,SW_PIN3,SW_PULL_UP};


//Activating LED and Buzzer
void Task_voidAlert(void)
{
	while(1)
	{
		BZR_voidOn(BZR_PORTA,BZR_PIN0);
		LED_voidLedOn(&Global_LED_tRed);
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
	}
}

//Reading Temperature from LM35
void Task_voidReadTemperature(void)
{
	u8 Local_u8TempVal;
	while(1)
	{
		TMP_u8ReadValue(&Local_u8TempVal);
	}
}

//Reading Dstance from Ultrasonic
void Task_voidReadDistance(void)
{
	u8 Local_u8DistVal;
	while(1)
	{
		USN_u8ReadDistance(&Local_u8DistVal);
	}
}

//Diagnostics Check
void Task_voidSystemCheck(void)
{
	while(1)
	{
		
	}
}

//Forward and backward motion
void Task_voidMoveVehicle(void)
{
	while(1)
	{
		
	}
}

//Recieving update or diagnostics rewuest
void Task_voidRecieveRequest(void)
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


