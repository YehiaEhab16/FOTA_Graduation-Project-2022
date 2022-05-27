/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"
#include "../../1-MCAL/11-WWDG/WWDG_interface.h"

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
