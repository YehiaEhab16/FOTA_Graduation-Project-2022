/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef PARSING_INTERFACE_H_
#define PARSING_INTERFACE_H_


/**
 * @def convert from string to hex
 * @param Copy_u8Asci character
 * @return hex Number
 */
u8 PARSING_u8AsciToHex (u8 Copy_u8Asci);


/**
 * @def Function that Serve the write the code on the flash
 * @param Copy_u8Data the record  that received from the Main ECU
 */
void PARSING_voidWriteData (u8* Copy_u8Data);


#endif
