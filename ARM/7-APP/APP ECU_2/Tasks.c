/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"
#include "../../2-HAL/07-FAN/FAN_interface.h"

#include "../../4-RTOS/RTOS_interface.h"

#include "Tasks2.h"
#include "Tasks2.h"

//Can Flag 
extern u8 Global_u8CanDiagFlag;

u8 Global_u8ErrorDiagFlag = 0;

u8 Global_pu8AppsVariables[6]= {0};

/*dist 0
 * temp1
 * RightMotorFB 2
 * LeftMotorFB 3
 * Direction   4
 * MainRequest 5
 */

//Can
CAN_msg CAN_TXmsg;

//FAN
FAN_t Global_FAN_tCoolingSystem = {FAN_PORTB,FAN_PIN12,FAN_ACTIVE_HIGH};

//Reading Temperature from LM35
void Task_voidReadTemperature(void )
{
	u8 Local_u8TempVal;
	TMP_u8ReadValue(&Local_u8TempVal);
	Global_pu8AppsVariables[1]=Local_u8TempVal;
}

//Rotate Fan
void Task_voidFanRotate(void )
{
	u8 Local_u8Temp;

	Local_u8Temp=Global_pu8AppsVariables[1];
	if(Local_u8Temp > TEMP_THRESHOLD)
		FAN_voidFanOn(&Global_FAN_tCoolingSystem);
	else
		FAN_voidFanOff(&Global_FAN_tCoolingSystem);
}

//Diagnostics Check
void Task_voidSystemCheck(void)
{
	u8 Local_u8TempVal;
	
	for (int i=0; i<8; i++) 
		CAN_TXmsg.data[i] = 0;
	
	Local_u8TempVal=Global_pu8AppsVariables[1];
	
	if (Global_u8CanDiagFlag == 1)
	{
		CAN_TXmsg.id = CAN_DIAG_ID_TX1;
		SET_BIT(Global_u8ErrorDiagFlag,7);
		if ( !( (Local_u8TempVal >=25)&&( Local_u8TempVal <=30) ) )
			SET_BIT(Global_u8ErrorDiagFlag,1);	//Error Occured
		else
			CLR_BIT(Global_u8ErrorDiagFlag,1);
	}
	else
	{
		CAN_TXmsg.id = CAN_DIAG_ID_TX2;
		if (  !((Local_u8TempVal>=20) && (Local_u8TempVal <=70) ) )
		    CAN_TXmsg.data[0] = 'T';			//Error Occured

		else
			Global_u8ErrorDiagFlag =0;
	}

	CAN_TXmsg.data[0] = Global_u8ErrorDiagFlag;
	Task_voidSendDiagnostics();
	Global_u8ErrorDiagFlag=0;
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{
	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.type = CAN_RTR_DATA;
	if (Global_u8ErrorDiagFlag !=0)
	{
		Global_u8ErrorDiagFlag =0
		CAN_u8Transmit(&CAN_TXmsg);
	}
}
