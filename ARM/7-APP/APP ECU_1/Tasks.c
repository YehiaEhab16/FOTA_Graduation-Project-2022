/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"
#include "../../2-HAL/07-FAN/FAN_interface.h"
#include "../../5-RTOS/RTOS_interface.h"

#include "Tasks.h"

//Can Flag 
extern u8 Global_u8DiagFlag;

//Motor Feedback
u8 Global_u8MotorFeedback = 0;

/*dist 0
 * temp1
 * RightMotorFB 2
 * LeftMotorFB 3
 * Direction   4
 * MainRequest 5
 */
u8 Global_pu8AppVariables[6]= {0};

//Can
CAN_msg CAN_TXmsg;

//LEDs
LED_t Global_LED_tRed = {LED_PORTB,LED_PIN1,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tForward =  {SW_PORTA,SW_PIN0,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTA,SW_PIN1,SW_PULL_UP};

//Motors
DCM_t Global_DCM_tRightMotor = {DCM_PORTA,DCM_PIN5,DCM_PIN4,DCM_PIN3,DCM_PIN2};

//Activating LED and Buzzer
void Task_voidAlert(void)
{
	u8 Local_u8Dist=255;
	Local_u8Dist = Global_pu8AppVariables[Distance];
	if(Local_u8Dist<DIST_THRESHOLD)
	{
		LED_voidLedOn(&Global_LED_tRed);
		BZR_voidOn(BZR_PORTA,BZR_PIN0);
	}
}

//Reading Distance from Ultrasonic
void Task_voidReadDistance(void)
{
	u32 Local_u32DistVal=255;
	USN_u8ReadDistance(&Local_u32DistVal);
	Global_pu8AppVariables[Distance]=Local_u32DistVal;
}

//Reading Direction from 2 switches
void Task_voidReadDirection(void)
{
	u8 Local_u8Dir;

	if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
	{
		//suspend Alert and suspend Distance
		Local_u8Dir=FORWARD;
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);
	}
	else if(SW_u8ReadSwitch(&Global_SW_tBackward)==PRESSED)
	{
		Local_u8Dir=BACKWARD;
		//Resume Alert and Distance
		RTOS_voidResumeTask((u8)READ_DISTANCE_ID);
		RTOS_voidResumeTask((u8)ALERT_ID);
	}
	else
	{
		Local_u8Dir=STOP;
		//suspend Alert and suspend Distance
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);
	}
	Global_pu8AppVariables[Direction]=Local_u8Dir;
}

//get feedback from encoder
void Task_voidMotorFeedback(void )
{
	u8 Local_u8MotorFB = 0;

	Local_u8MotorFB = Global_u8MotorFeedback ;

}

//Forward and backward motion
void Task_voidMoveVehicle(void)
{
	u8 Local_u8Dir;

	Local_u8Dir = Global_pu8AppVariables[Direction];
	if(Local_u8Dir==FORWARD)
		DCM_voidRotateCCW(&Global_DCM_tRightMotor );

	else if(Local_u8Dir==BACKWARD)
		DCM_voidRotateCW(&Global_DCM_tRightMotor );

	else if(Local_u8Dir==STOP)
		DCM_voidStop2(&Global_DCM_tRightMotor );
}


//Diagnostics Check
void Task_voidSystemCheck(void)
{
	u8 Local_u8Dist;
	u8 Local_u8Dir;
	u8 Local_u8MotorFB;
	u8 Local_u8LastError;

	for (int i=0; i<8; i++) {CAN_TXmsg.data[i] = 0;}

	Local_u8Dist=Global_pu8AppVariables[Distance];
	Local_u8MotorFB=Global_pu8AppVariables[LeftMotorFB];
	Local_u8Dir = Global_pu8AppVariables[Direction];

	if (Global_u8DiagFlag == 1)
	{
		Global_u8DiagFlag=0;
		if ( (Local_u8Dir == STOP) )	//Add Polling to move forward
			CAN_TXmsg.data[0] = DirErrorMode1;
		if(( (Local_u8Dist >=10) && (Local_u8Dist <= 14))&&(Local_u8Dir == BACKWARD))
			if(CAN_TXmsg.data[0]==DirErrorMode1)
				CAN_TXmsg.data[0] = DistDirErrorMode1;
			else
				CAN_TXmsg.data[0] = DistErrorMode1;
		else
			CAN_TXmsg.data[0] = NonError;
	}
	else
	{
		if(( (Local_u8Dir == FORWARD ) && ( ( (Local_u8MotorFB != FORWARD)) ))
				||((Local_u8Dir == BACKWARD) && ( ((Local_u8MotorFB != BACKWARD)) )))
			CAN_TXmsg.data[0] = DirErrorMode2;
		else
			CAN_TXmsg.data[0] = NonError;
	}

	if (CAN_TXmsg.data[0] != Local_u8LastError)
	{
		Local_u8LastError =CAN_TXmsg.data[0];
		if (Local_u8LastError != NonError)
			Task_voidSendDiagnostics();
	}
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{
	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.id = 0x31;
	CAN_TXmsg.type = CAN_RTR_DATA;
}
