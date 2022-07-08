/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):COM 			 ***********************/
/***********************   DATE : 8-7-2022	 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef COM_INTERFACE_H_
#define COM_INTERFACE_H_


#define COM_UPDATE_APPROVED			0
#define COM_UPDATE_REJECTED			2

#define COM_DAIG_REQUESTED			0
#define COM_DAIG_NOT_REQUESTED		2


void COM_voidSendUpdateRequest(void);

void COM_voidSendDaignosticsData(u8 Copy_u8Data);

u8 COM_u8RecieveUpdateResponse(void);

u8 COM_u8RecieveDaignosticsRequest(void);


#endif
