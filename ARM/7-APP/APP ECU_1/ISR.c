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

#include "../../2-HAL/02-DCM/DCM_interface.h"

#include "ISR.h"
#include "Tasks.h"

//Recieve Struct
CAN_msg CAN_RXmsg;
u8 Global_u8DiagFlag=0;

u16 Update = 0;
u16 No_update =1 ;
u16 Corruption =2 ;

void ISR_voidCANRecieve(void)
{
	u16 Local_u16Data=1;
	CAN_voidReceive(&CAN_RXmsg, 0);
	if(CAN_RXmsg.id==CAN_UPADTE_ID)
	{
		FPEC_voidFlashPageErase(10);
		FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG,&Update,1);
		WWDG_voidReset(1);
	}
	else if(CAN_RXmsg.id==CAN_DIAG_ID)
		Global_u8DiagFlag = 1;
}
