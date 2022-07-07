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




#include "Tasks2_interface.h"
#include "Tasks2_private.h"

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



//FAN
FAN_t Global_FAN_tCoolingSystem = {FAN_PORTB,FAN_PIN12,FAN_ACTIVE_HIGH};


//Reading Temperature from LM35
void Task_voidReadTemperature(void )
{
	GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_1, GPIO_PIN_HIGH);

	u8 Local_u8TempVal;

		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_2, GPIO_PIN_HIGH);
		TMP_u8ReadValue(&Local_u8TempVal);
		Global_APPS_Variables[1]=Local_u8TempVal;

}

//Rotate Fan
void Task_voidFanRotate(void )
{
	u8 Local_u8Temp;

		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_5, GPIO_PIN_HIGH);

		Local_u8Temp=Global_APPS_Variables[1];
		if(Local_u8Temp > TEMP_THRESHOLD)
			FAN_voidFanOn(&Global_FAN_tCoolingSystem);
		else
			FAN_voidFanOff(&Global_FAN_tCoolingSystem);

}




//Diagnostics Check
void Task_voidSystemCheck(void)
{

	u8 Local_u8TempVal;


	for (int i=0; i<8; i++) {CAN_TXmsg.data[i] = 0;}


	Local_u8TempVal=Global_APPS_Variables[1];

	if (Global_CAN_DIAG_FLAG == 1)
	{
		if ( !( (Local_u8TempVal >=25)&&( Local_u8TempVal <=30) ) )
			SET_BIT(Global_ERORR_DIAG_FLAG,1);
		else
			CLR_BIT(Global_ERORR_DIAG_FLAG,1);


	}
	else
	{

		if (  !((Local_u8TempVal>=20) && (Local_u8TempVal <=70) )  ){
		    CAN_TXmsg.data[0] = 'T';

		}
		else
		{

			Global_ERORR_DIAG_FLAG =0 ;
		}
	}

	CAN_TXmsg.data[0] = Global_ERORR_DIAG_FLAG;
	Global_ERORR_DIAG_FLAG=0;
	Task_voidSendDiagnostics();

}

//Sending Diagnostics Data
void Task_voidSendDiagnostics(void)
{

	GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_0, GPIO_PIN_HIGH);

	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.id = 0x38;
	CAN_TXmsg.type = CAN_RTR_DATA;

	if (Global_ERORR_DIAG_FLAG !=0 )
	{
		Global_ERORR_DIAG_FLAG =0 ;
		CAN_u8Transmit(&CAN_TXmsg);
	}

}

