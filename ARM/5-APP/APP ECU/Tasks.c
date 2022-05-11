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

//Activating LED and Buzzer
void Task_voidAlert(void)
{
	
}

//Reading Direction from 2 switches
u8 Task_u8ReadDirection(void)
{
	
}

//Reading Temperature from LM35
u8 Task_u8ReadTemperature(void)
{
	
}

//Reading Dstance from Ultrasonic
u8 Task_u8ReadDistance(void)
{
	
}

//Diagnostics Check
u8 Task_u8SystemCheck(void)
{
	
}

//Forward and backward motion
u8 Task_u8MoveVehicle(u8 Copy_u8Direction)
{
	
}

//Recieving update or diagnostics rewuest
u8 Task_u8RecieveRequest(void)
{
	
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(u8 Copy_u8Message)
{
	
}


