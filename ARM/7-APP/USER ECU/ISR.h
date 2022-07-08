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
#define CAN_UPDATE_ID 				0x32
#define CAN_DIAG_ID_1 				0x38
#define CAN_DIAG_ID_2 				0x31

#define ISR_UPDATE_APPROVED			30
#define ISR_UPDATE_REJECTED			35

#define ISR_DAIG_REQUESTED			40

/**
 * @def STM to RPI
 */

void ISR_voidCanRecieve(void);

/**
 * @def RPI to CAN
 */
void ISR_voidUsartRecieve(void);

#endif
