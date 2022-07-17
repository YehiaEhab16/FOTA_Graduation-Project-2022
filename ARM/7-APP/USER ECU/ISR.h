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
#define CAN_UPDATE_ID 					0x33
#define CAN_DIAG_ID	 					0x73

// Can IDs Send
#define CAN_UPDATE_ID_TX				0X46
#define CAN_DIAG_ID_TX	 				0x36

#define ISR_UPDATE_APPROVED				30
#define ISR_UPDATE_REJECTED				35

#define ISR_DIAG_REQUESTED				40

#define ISR_UPDATE_NOTF					45
#define ISR_UPDATE_PROG					50
#define ISR_UPDATE_COMP					55
#define ISR_UPDATE_NOT_COMP				60

#define ISR_UPDATE_REQUESTED			65

/**
 * @def STM to RPI
 */

void ISR_voidCanRecieve(void);

/**
 * @def RPI to CAN
 */
void ISR_voidUsartRecieve(void);

#endif
