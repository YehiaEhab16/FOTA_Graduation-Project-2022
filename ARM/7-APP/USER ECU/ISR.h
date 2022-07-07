/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE :  3/7/2022  			***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ISR_H_
#define ISR_H_

// Can IDs
#define CAN_UPDATE_ID 0x32
#define CAN_DIAG_ID_1 0x38
#define CAN_DIAG_ID_2 0x31

// User Macros
#define USER_APPROVE_ID 0
#define USER_REQUEST_ID 1
#define USER_DIAG_ID 2
#define USER_UPDATE_ID 10
#define USER_REQUEST 11
#define USER_REJECTED 12
#define USER_APPROVED 30

typedef enum {

	USER_APPROVE = 0 ,
	USER_REJECT,
	USER_UPDATE_REQUEST,
	USER_DIAG,
	MAIN_Notification,



}TO_MAIN_ECU ;





/**
 * @def STM to RPI
 */

void ISR_voidCanRecieve(void);

/**
 * @def RPI to CAN
 */
void ISR_voidUsartRecieve(void);

#endif
