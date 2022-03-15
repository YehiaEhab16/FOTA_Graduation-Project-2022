/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 15-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef FPEC_S_INTERFACE_H_
#define FPEC_S_INTERFACE_H_


void FPEC_S_voidInit(void);
void FPEC_S_voidDisable(void);

/**
 * @def convert from string to hex
 * @param Copy_u8Asci character
 * @return hex Number
 */
u8 FPEC_S_u8AsciToHex (u8 Copy_u8Asci);


/**
 * @def Function that Serve the write the code on the flash
 * @param Copy_u8Data the record  that received from the Main ECU
 */
void FPEC_S_voidWriteData (u8* Copy_u8Data);


#endif