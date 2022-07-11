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
#define CAN_DIAG_ID						0x47

#define CAN_DIAG_ID_TX1					0x38
#define CAN_DIAG_ID_TX2					0x31

void ISR_voidCANRecieve(void);

void ISR_voidDCM(void);


#endif

