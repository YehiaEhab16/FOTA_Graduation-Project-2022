/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ISR_H_
#define ISR_H_


#define TASK_BOOT_FLAG					0x080028C0

#define CAN_UPADTE_ID					0x34
#define CAN_DIAG_ID						0x48

#define CAN_DIAG_ID_TX					0x38

void Task_voidCANRecieveISR(void);


#endif

