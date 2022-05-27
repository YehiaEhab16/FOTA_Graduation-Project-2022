/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CRC 			 ***********************/
/***********************   DATA : 10-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "CRC_interface.h"
#include "CRC_private.h"
#include "CRC_config.h"
#include "CRC_register.h"

//CRC Calculation
u32 CRC_u8CalculationHardware(u32 Copy_u32Data)
{
	u32 Local_u32Crc = 0;
	
	//Reset the CRC peripheral
	SET_BIT(CRC->CR,0) ;

	//Put the data to CRC DATA REGISTER
	CRC->DR = Copy_u32Data ;

	Local_u32Crc = CRC->DR ;

	return Local_u32Crc ;
}
