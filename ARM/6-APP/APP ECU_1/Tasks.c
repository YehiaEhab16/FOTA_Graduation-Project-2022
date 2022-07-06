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
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"
#include "../../2-HAL/07-FAN/FAN_interface.h"
#include "../../4-RTOS/RTOS_interface.h"




#include "Tasks_interface.h"
#include "Tasks_private.h"

//Can Flag 
extern u8 Global_CAN_DIAG_FLAG;



u8 Global_ERORR_DIAG_FLAG = 0;


u8 Global_APPS_Variables[6]= {0};



/*dist 0
 * temp1
 * RightMotorFB 2
 * LeftMotorFB 3
 * Direction   4
 * MainRequest 5
 */

//Can
CAN_msg CAN_TXmsg;

//LEDs
LED_t Global_LED_tRed = {LED_PORTB,LED_PIN1,LED_ACTIVE_HIGH};

//Switches
SW_t Global_SW_tForward =  {SW_PORTB,SW_PIN0,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTB,SW_PIN1,SW_PULL_UP};

//Motors
DCM_t Global_DCM_tRightMotor = {DCM_PORTB,DCM_PIN4,DCM_PIN5,DCM_PIN6,DCM_PIN7};
DCM_t Global_DCM_tLeftMotor = {DCM_PORTB,DCM_PIN8,DCM_PIN9,DCM_PIN10,DCM_PIN11};

//FAN
FAN_t Global_FAN_tCoolingSystem = {FAN_PORTB,FAN_PIN12,FAN_ACTIVE_HIGH};


//Activating LED and Buzzer
void Task_voidAlert(void)
{
	GPIO_u8TogglePinValue(GPIO_PORTA, GPIO_PIN_0);
	u8 Local_u8Dist=255;
	Local_u8Dist = Global_APPS_Variables[Distance];
	if(Local_u8Dist<DIST_THRESHOLD)
	{
		LED_voidLedOn(&Global_LED_tRed);
		BZR_voidOn(BZR_PORTA,BZR_PIN0);
	}

}
//Reading Distance from Ultrasonic
void Task_voidReadDistance(void)
{
	u32 Local_u8DistVal=255;
	GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_3, GPIO_PIN_HIGH);
	USN_u8ReadDistance(&Local_u8DistVal);
	Global_APPS_Variables[Distance]=Local_u8DistVal;

}

//Reading Direction from 2 switches
void Task_voidReadDirection(void)
{
	u8 Local_u8Dir;

	if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
	{
		//suspend Altert and suspend Distance
		Local_u8Dir=FORWARD;
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);


	}
	else if(SW_u8ReadSwitch(&Global_SW_tBackward)==PRESSED)
	{
		Local_u8Dir=BACKWARD;
		//ResumeAltert and dist
		RTOS_voidResumeTask((u8)READ_DISTANCE_ID);
		RTOS_voidResumeTask((u8)ALERT_ID);
	}
	else
	{
		Local_u8Dir=STOP;
		//suspend Altert and suspend Distance
		RTOS_voidSuspendTask((u8)READ_DISTANCE_ID);
		RTOS_voidSuspendTask((u8)ALERT_ID);
	}
	Global_APPS_Variables[Direction]=Local_u8Dir;

}

//get feedback from encoder
void Task_voidMotorFeedback(void )
{
	u8 Local_u8RightMotorFB=0;
	u8 Local_u8LeftMotorFB=0;

	GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_4, GPIO_PIN_HIGH);
	Local_u8RightMotorFB = DCM_voidReadEncoder(&Global_DCM_tRightMotor);
	Local_u8LeftMotorFB  = DCM_voidReadEncoder(&Global_DCM_tLeftMotor);
	Global_APPS_Variables[RightMotorFB]=Local_u8RightMotorFB;
	Global_APPS_Variables[LeftMotorFB]=Local_u8LeftMotorFB;


}



//Forward and backward motion
void Task_voidMoveVehicle(void)
{
	u8 Local_u8Dir;

	Local_u8Dir = Global_APPS_Variables[Direction];
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


//Diagnostics Check
void Task_voidSystemCheck(void)
{
	u8 Local_u8Dist;
	u8 Local_u8Dir;
	u8 Local_u8RightMotorFB;
	u8 Local_u8LeftMotorFB;


	for (int i=0; i<8; i++) {CAN_TXmsg.data[i] = 0;}

	Local_u8Dist=Global_APPS_Variables[Distance];
	Local_u8LeftMotorFB=Global_APPS_Variables[RightMotorFB];
	Local_u8RightMotorFB=Global_APPS_Variables[LeftMotorFB];
	Local_u8Dir = Global_APPS_Variables[Direction];

	CAN_TXmsg.id = 0x31;
	if (Global_CAN_DIAG_FLAG == 1)
	{
		if ( !(Local_u8Dir == FORWARD) )
		{
			SET_BIT(Global_ERORR_DIAG_FLAG,2);
		}

		if(( (Local_u8Dist >=10) && (Local_u8Dist <= 14))&&(Local_u8Dir == FORWARD))
		{
			SET_BIT(Global_ERORR_DIAG_FLAG,3);
		}
		Global_CAN_DIAG_FLAG =0 ;
	}
	else
	{
		CAN_TXmsg.id = 0x38;

		if(( (Local_u8Dir == FORWARD ) && ( ( (Local_u8RightMotorFB != FORWARD)
				||(Local_u8LeftMotorFB != FORWARD ) ) ))
				||((Local_u8Dir == BACKWARD) && ( ((Local_u8RightMotorFB != BACKWARD)
						||(Local_u8LeftMotorFB != BACKWARD) ) )))
		{
			Global_ERORR_DIAG_FLAG  = 'M';
		}
		else
		{

			Global_ERORR_DIAG_FLAG =0 ;
		}
	}

	CAN_TXmsg.data[0] = Global_ERORR_DIAG_FLAG;
	Task_voidSendDiagnostics();

}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{

	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.type = CAN_RTR_DATA;

	if (Global_ERORR_DIAG_FLAG !=0)
	{
		Global_ERORR_DIAG_FLAG =0 ;
		CAN_u8Transmit(&CAN_TXmsg);
	}

}

