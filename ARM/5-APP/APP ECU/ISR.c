/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "FPEC_interface.h"
#include "CAN_interface.h"
#include "WWDG_interface.h"

#include "ISR.h"

//Recieve Struct
CAN_msg CAN_RXmsg;

void Task_voidCANRecieveISR(void)
{
	CAN_voidReceive(&CAN_RXmsg, 0);
	if(CAN_RXmsg.id==CAN_UPADTE_ID)
	{
		FPEC_voidFlashWrite(TASK_BOOT_FLAG,1,1);
		WWDG_voidReset(1);
	}
	else if(CAN_RXmsg.id==CAN_DIAG_ID)
	{
		
	}
}
