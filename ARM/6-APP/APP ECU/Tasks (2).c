/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../7-Library/STD_TYPES.h"
#include "../../7-Library/BIT_MATH.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/03-BZR/BZR_interface.h"
#include "../../2-HAL/04-TMP/TMP_interface.h"
#include "../../2-HAL/05-USN/USN_interface.h"
#include "../../2-HAL/06-SW/SW_interface.h"
#include "../../2-HAL/07-FAN/FAN_interface.h"

#include "../../4-FreeRTOS/OS/org/Source/include/FreeRTOS.h"
#include "../../4-FreeRTOS/OS/org/Source/include/task.h"
#include "../../4-FreeRTOS/OS/org/Source/include/queue.h"

#include "Tasks.h"

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
SW_t Global_SW_tForward =  {SW_PORTB,SW_PIN2,SW_PULL_UP};
SW_t Global_SW_tBackward = {SW_PORTB,SW_PIN3,SW_PULL_UP};

//Motors
DCM_t Global_DCM_tRightMotor = {DCM_PORTB,DCM_PIN4,DCM_PIN5,DCM_PIN6,DCM_PIN7};
DCM_t Global_DCM_tLeftMotor = {DCM_PORTB,DCM_PIN8,DCM_PIN9,DCM_PIN10,DCM_PIN11};

//FAN
FAN_t Global_FAN_tCoolingSystem = {FAN_PORTB,FAN_PIN12,FAN_ACTIVE_HIGH};

//Task Handles
TaskHandle_t Global_TaskHandle_tAlert;
TaskHandle_t Global_TaskHandle_tDist;
TaskHandle_t Global_TaskHandle_tSend;

//Queues
//xQueueHandle Global_xQueueHandleDistance;
//xQueueHandle Global_xQueueHandleRightMotorFB;
//xQueueHandle Global_xQueueHandleLeftMotorFB;
//
//xQueueHandle Global_xQueueHandleDirection;
//xQueueHandle Global_xQueueHandleTemperature;
//xQueueHandle Global_xQueueMainRequest;


//void Task_voidCreateQueue (void)
//{
//
//	Global_xQueueHandleDistance     = 	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//	Global_xQueueHandleDirection    = 	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//	Global_xQueueHandleTemperature  =	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//	Global_xQueueMainRequest        =	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//	Global_xQueueHandleRightMotorFB =	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//	Global_xQueueHandleLeftMotorFB  =	xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
//}

//Activating LED and Buzzer
void Task_voidAlert(void * parms)
{
	u8 Local_u8Dist=255;
	while(1)
	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_0, GPIO_PIN_HIGH);
		//LED_voidLedOn(&Global_LED_tRed);
		Local_u8Dist = Global_APPS_Variables[0];
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
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_1, GPIO_PIN_HIGH);
		if(SW_u8ReadSwitch(&Global_SW_tForward)==PRESSED)
		{
			Local_u8Dir=FORWARD;
			vTaskSuspend(Global_TaskHandle_tAlert);
			vTaskSuspend(Global_TaskHandle_tDist);
		}
		else if(SW_u8ReadSwitch(&Global_SW_tBackward)==PRESSED)
		{
			Local_u8Dir=BACKWARD;
			vTaskResume(Global_TaskHandle_tAlert);
			vTaskResume(Global_TaskHandle_tDist);
		}
		else
		{
			Local_u8Dir=STOP;
			vTaskSuspend(Global_TaskHandle_tAlert);
			vTaskSuspend(Global_TaskHandle_tDist);
		}
		Global_APPS_Variables[4]=Local_u8Dir;
	}
}

//Reading Temperature from LM35
void Task_voidReadTemperature(void * parms)
{
	u8 Local_u8TempVal;
	while(1)
	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_2, GPIO_PIN_HIGH);
		TMP_u8ReadValue(&Local_u8TempVal);
		Global_APPS_Variables[1]=Local_u8TempVal;
	}
}

//Reading Distance from Ultrasonic
void Task_voidReadDistance(void * parms)
{
	u8 Local_u8DistVal=255;
	while(1)
	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_3, GPIO_PIN_HIGH);
		USN_u8ReadDistance(&Local_u8DistVal);
		Global_APPS_Variables[0]=Local_u8DistVal;

	}
}
//get feedback from encoder
void Task_voidMotorFeedback(void * parms)
{
	u8 Local_u8RightMotorFB=0;
	u8 Local_u8LeftMotorFB=0;
	while(1)
	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_4, GPIO_PIN_HIGH);
		Local_u8RightMotorFB = DCM_voidReadEncoder(&Global_DCM_tRightMotor);
		Local_u8LeftMotorFB  = DCM_voidReadEncoder(&Global_DCM_tLeftMotor);
		Global_APPS_Variables[2]=Local_u8RightMotorFB;
		Global_APPS_Variables[3]=Local_u8LeftMotorFB;


	}
}

//Rotate Fan
void Task_voidFanRotate(void * parms)
{
	u8 Local_u8Temp;
	while(1)
	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_5, GPIO_PIN_HIGH);

		Local_u8Temp=Global_APPS_Variables[1];
		if(Local_u8Temp > TEMP_THRESHOLD)
			FAN_voidFanOn(&Global_FAN_tCoolingSystem);
		else
			FAN_voidFanOff(&Global_FAN_tCoolingSystem);
	}
}

//Forward and backward motion
void Task_voidMoveVehicle(void * parms)
{
	u8 Local_u8Dir;
	while(1)
	{

		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_6, GPIO_PIN_HIGH);
		Local_u8Dir = Global_APPS_Variables[4];
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
	u8 Local_u8Dist;
	u8 Local_u8TempVal;
	u8 Local_u8Dir;
	u8 Local_u8RightMotorFB;
	u8 Local_u8LeftMotorFB;
    for (int i=0; i<8; i++) {CAN_TXmsg.data[i] = 0;}
	while(1)
	{


		Local_u8Dist=Global_APPS_Variables[0];
		Local_u8TempVal=Global_APPS_Variables[1];

		Local_u8LeftMotorFB=Global_APPS_Variables[2];
		Local_u8RightMotorFB=Global_APPS_Variables[3];
		Local_u8Dir = Global_APPS_Variables[4];

		if (Global_CAN_DIAG_FLAG == 1){
		    CAN_TXmsg.id = 0x31;

			if ( !( (Local_u8Dist >=10) && (Local_u8Dist <= 14)) )
				SET_BIT(Global_ERORR_DIAG_FLAG,0);


			if ( !( (Local_u8TempVal >=25)&&( Local_u8TempVal <=30) ) )
				SET_BIT(Global_ERORR_DIAG_FLAG,1);


			if ( !(Local_u8Dir == FORWARD) )
				SET_BIT(Global_ERORR_DIAG_FLAG,2);

			if(( (Local_u8Dist >=10) && (Local_u8Dist <= 14))
			 &&( (Local_u8TempVal >=25)&&( Local_u8TempVal <=30))
			 &&(Local_u8Dir == FORWARD)    ){
				Global_ERORR_DIAG_FLAG =0 ;
				SET_BIT(Global_ERORR_DIAG_FLAG,3);
			}

		    CAN_TXmsg.data[0] = Global_ERORR_DIAG_FLAG;
		    Global_ERORR_DIAG_FLAG =0 ;
			GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_6, GPIO_PIN_HIGH);

		    Task_voidSendDiagnostics();

		}
		else {

		    CAN_TXmsg.id = 0x38;
			if (  !((Local_u8TempVal>=20) && (Local_u8TempVal <=70) )  ){
			    CAN_TXmsg.data[0] = 'T';
			   // vTaskResume(Global_TaskHandle_tSend);

			}


			else if(( (Local_u8Dir == FORWARD ) && ( ( (Local_u8RightMotorFB != FORWARD)
													||(Local_u8LeftMotorFB != FORWARD ) ) ))
				   ||((Local_u8Dir == BACKWARD) && ( ((Local_u8RightMotorFB != BACKWARD)
                                                    ||(Local_u8LeftMotorFB != BACKWARD) ) ))){
			    CAN_TXmsg.data[0]  = 'M';
			 //   vTaskResume(Global_TaskHandle_tSend);
			}
			GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_6, GPIO_PIN_HIGH);


			GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_7, GPIO_PIN_HIGH);


		}

}
}

//Sending Diagnostics Data
void Task_voidSendDiagnostics()
{

	CAN_TXmsg.len = 1;
    CAN_TXmsg.format = CAN_ID_STD;
    CAN_TXmsg.type = CAN_RTR_DATA;
//	while(1)
//	{
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_6, GPIO_PIN_HIGH);
		if ((CAN_TXmsg.data[0]=='T')
		  ||(CAN_TXmsg.data[0]=='M')
		  ||(CAN_TXmsg.data[0]<9))
		CAN_u8Transmit(&CAN_TXmsg);

	//	vTaskSuspend(Global_TaskHandle_tSend);
	//}
}

