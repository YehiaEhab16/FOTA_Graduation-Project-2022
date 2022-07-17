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


#define COM_UPDATE_REQUESTED		3
#define COM_UPDATE_APPROVED			2
#define COM_IDLE					1
#define COM_UPDATE_REJECTED			0

#define COM_DAIG_REQUESTED			0
#define COM_DAIG_NOT_REQUESTED		2


void COM_voidSendUpdateRequest(void);

void COM_voidSendUpdateProgress(void);

void COM_voidSendUpdateComplete(void);

void COM_voidSendUpdateFailed(void);

void COM_voidSendDaignosticsData(u8 Copy_u8Data);

void COM_voidRecieveUpdateResponse(void);

void COM_voidRecieveDaignosticsRequest(void);


#endif
