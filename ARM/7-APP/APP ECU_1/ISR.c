/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"
#include "../../1-MCAL/11-WWDG/WWDG_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"

#include "ISR.h"
#include "Tasks.h"

extern LED_t LED1 ;

//Recieve Struct
CAN_msg CAN_RXmsg;
u8 Global_u8CanDiagFlag = 0;
void Task_voidCANRecieveISR(void)
{
	//LED_voidLedToggle(&LED1);
	u16 Local_u16Data=0;
	CAN_voidReceive(&CAN_RXmsg, 0);
	Global_u8CanDiagFlag = 0;
	if(CAN_RXmsg.id==CAN_UPADTE_ID)
	{
		FPEC_voidFlashPageErase(10);
		FPEC_voidFlashWrite(TASK_BOOT_FLAG,&Local_u16Data,1);
		WWDG_voidReset(1);
	}
	else if(CAN_RXmsg.id==CAN_DIAG_ID)
	{
		Global_u8CanDiagFlag = 1;
		//GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_7, GPIO_PIN_HIGH);
	}
}
