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
#include "../../1-MCAL/07-STK/STK_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"
#include "../../2-HAL/07-FAN/FAN_interface.h"
#include "../../5-RTOS/RTOS_interface.h"


#include "Tasks.h"
#include "ISR.h"

//Can Flag 
extern u8 Global_u8DiagFlag;

//Motor Feedback
extern u8 Global_u8MotorFeedback;

/*dist 0
 * temp1
 * RightMotorFB 2
 * LeftMotorFB 3
 * Direction   4
 * MainRequest 5
 */
u8 Global_pu8AppVariables[6]= {2};

//Can
CAN_msg CAN_TXmsg;

//LEDs
LED_t Global_LED_tRed = {LED_PORTC,LED_PIN13,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tBackward =  {SW_PORTA,SW_PIN0,SW_PULL_UP};
SW_t Global_SW_tForward = {SW_PORTA,SW_PIN1,SW_PULL_UP};


u8 Global_u8Flag =0 ;
//Activating LED and Buzzer
void Task_voidAlert(void)
{
	u8 Local_u8Dist=255;
	Local_u8Dist = Global_pu8AppVariables[Distance];
	if(Local_u8Dist<DIST_THRESHOLD)
	{
		LED_voidLedOn(&Global_LED_tRed);
		BZR_voidOn(BZR_PORTB,BZR_PIN5);
	}
	else
	{
		BZR_voidOff(BZR_PORTB,BZR_PIN5);
	}
}

//Reading Distance from Ultrasonic
void Task_voidReadDistance(void)
{
	if(Global_u8Flag)
	{
		Global_u8Flag =0 ;
		u32 Local_u32DistVal=255;
		USN_u8ReadDistance(&Local_u32DistVal);
		Global_pu8AppVariables[Distance]=Local_u32DistVal;
	}
}

//Reading Direction from 2 switches
void Task_voidReadDirection(void)
{
	u8 Local_u8Dir;

	if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
	{
		BZR_voidOff(BZR_PORTB,BZR_PIN5);

		//suspend Alert and suspend Distance
		Local_u8Dir=FORWARD;
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);
	}
	else if(SW_u8ReadSwitch(&Global_SW_tBackward)==PRESSED)
	{

		Global_u8Flag = 1 ;
		Local_u8Dir=BACKWARD;
		//Resume Alert and Distance
		RTOS_voidResumeTask((u8)READ_DISTANCE_ID);
		RTOS_voidResumeTask((u8)ALERT_ID);
	}
	else
	{
		BZR_voidOff(BZR_PORTB,BZR_PIN5);

		Local_u8Dir=STOP;
		//suspend Alert and suspend Distance
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);
	}
	Global_pu8AppVariables[Direction]=Local_u8Dir;
}

//Forward and backward motion
void Task_voidMoveVehicle(void)
{
	u8 Local_u8Dir;

	Local_u8Dir = Global_pu8AppVariables[Direction];
	if(Local_u8Dir==FORWARD)
		DCM_voidRotateCCW();

	else if(Local_u8Dir==BACKWARD)
		DCM_voidRotateCW();

	else if(Local_u8Dir==STOP)
		DCM_voidStop2();
}


//Diagnostics Check
void Task_voidSystemCheck(void)
{
	u8 Local_u8Dist =0 ;
	u8 Local_u8Dir = 0 ;
	u8 Local_u8MotorFB=0 ;
	static u8 Local_u8LastError =0 ;

	for (int i=0; i<8; i++) {CAN_TXmsg.data[i] = 0;}
	Local_u8Dist=Global_pu8AppVariables[Distance];
	Local_u8Dir = Global_pu8AppVariables[Direction];
	Local_u8MotorFB=Global_u8MotorFeedback;

	if (Global_u8DiagFlag == 1)
	{
		Global_u8DiagFlag=0;
		if ((( (Local_u8Dist >=10) && (Local_u8Dist <= 14))&&(Local_u8Dir == BACKWARD))&&(Local_u8MotorFB != DCM_DIR_CW))
			CAN_TXmsg.data[0] = DistDirErrorMode1;
		else if ( (Local_u8MotorFB != DCM_DIR_CW)&&(Local_u8Dir == BACKWARD) )	//Add Polling to move forward
			CAN_TXmsg.data[0] = DirErrorMode1;
		else if((!((Local_u8Dist >=10) && (Local_u8Dist <= 14)))&&(Local_u8Dir == BACKWARD))
			CAN_TXmsg.data[0] = DistErrorMode1;
		else
			CAN_TXmsg.data[0] = NonError;
		Task_voidSendDiagnostics();
	}
	else
	{
		if (CAN_TXmsg.data[0] == NonError)
		{
			if((( (Local_u8Dir == FORWARD ) && ( ( (Local_u8MotorFB == DCM_DIR_CW)) ))
					||((Local_u8Dir == BACKWARD) && ( ((Local_u8MotorFB == DCM_DIR_CCW)) ))))
				CAN_TXmsg.data[0] = DirErrorMode2;
			else
				CAN_TXmsg.data[0] = NonError;
			if (CAN_TXmsg.data[0] != Local_u8LastError)
			{
				if (CAN_TXmsg.data[0] != NonError)
				{
					Local_u8LastError =CAN_TXmsg.data[0];

					Task_voidSendDiagnostics();
				}
			}
		}
	}
	Global_u8MotorFeedback =2 ;

}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{
	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.id = CAN_DIAG_ID_TX1;
	CAN_TXmsg.type = CAN_RTR_DATA;
	CAN_u8Transmit(&CAN_TXmsg);
}
