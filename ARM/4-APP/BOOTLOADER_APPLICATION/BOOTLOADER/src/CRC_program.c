/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CRC 			 ***********************/
/***********************   DATA : 10-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CRC_interface.h"
#include "CRC_private.h"
#include "CRC_register.h"

void CRC_voidInit (void)
{
	CRC->CRC_CR = 0xFFFFFFFF;
}

u32 CRC_u8CalculationHardware(u32 Copy_u32Data)
{
	SET_BIT(CRC->CRC_CR,0);
	u32 Local_u32Crc =0 ;
	/*Put the data to CRC DATA REGISTER*/

	CRC->CRC_DR = Copy_u32Data ;

	Local_u32Crc = CRC->CRC_DR ;


	return Local_u32Crc ;



}

