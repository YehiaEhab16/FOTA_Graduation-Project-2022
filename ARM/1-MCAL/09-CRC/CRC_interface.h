/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CRC 			 ***********************/
/***********************   DATA : 10-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef CRC_INTERFACE_H_
#define CRC_INTERFACE_H_

/**
 * @def calculate the crc by the hardware
 * @param Copy_u32Data Data you want to calculate the crc
 * @return CRC Value
 */
u32 CRC_u8CalculationHardware(u32 Copy_u32Data);

#endif
