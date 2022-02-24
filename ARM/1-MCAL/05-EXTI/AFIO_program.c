/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_config.h"
#include "AFIO_private.h"



void	AFIO_voidSetEXTIConfiguration(u8 Copy_u8Line ,u8 Copy_u8PortMap)
{
	u8 Local_u8RegIndex = 0 ;		
	/* Assign to EXTICRX register									*/
	if(Copy_u8Line <= 3 )
	{
			Local_u8RegIndex = 0;
	}
	else if(Copy_u8Line<=7)
	{
			
		Local_u8RegIndex = 1;
		Copy_u8Line -= 4;
	}
	else if(Copy_u8Line<=11)
	{
		Local_u8RegIndex = 2;
		Copy_u8Line -= 8;
	
	}
	else if(Copy_u8Line<=15)
	{
		Local_u8RegIndex = 3;
		Copy_u8Line -= 12;
	}
	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) << (Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex]  |= ((Copy_u8PortMap) << (Copy_u8Line * 4));	
}
