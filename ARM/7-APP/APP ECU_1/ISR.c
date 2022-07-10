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
#include "../../2-HAL/02-DCM/DCM_interface.h"

#include "../../1-MCAL/08-FPEC/FPEC_interface.h"
#include "../../1-MCAL/11-WWDG/WWDG_interface.h"
#include "ISR.h"
#include "Tasks_interface.h"


//Recieve Struct
CAN_msg CAN_RXmsg;
u8 Global_CAN_DIAG_FLAG = 0;
void Task_voidCANRecieveISR(void)
{
	u16 Local_u16Data=1;
	CAN_voidReceive(&CAN_RXmsg, 0);
	Global_CAN_DIAG_FLAG = 0;
	if(CAN_RXmsg.id==CAN_UPADTE_ID)
	{
		FPEC_voidFlashWrite(TASK_BOOT_FLAG,&Local_u16Data,1);
		WWDG_voidReset(1);
	}
	else if(CAN_RXmsg.id==CAN_DIAG_ID)
	{
		Global_CAN_DIAG_FLAG = 1;
	//	Task_voidSendDiagnostics();
		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_7, GPIO_PIN_HIGH);
	}
}


void DCM_voidEXTI_ISR (void)
{
	//u8 ENCA_PIN_VALUE=0;
		DCM_u8DetectDirection();
}
