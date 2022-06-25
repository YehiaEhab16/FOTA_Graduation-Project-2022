/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_config.h"
#include "FPEC_private.h"
#include "FPEC_register.h"

//Initializing FPEC
void FPEC_voidInit(void)
{
	//Enter the latency of the flash
	FPEC->FLASH_ACR = FPEC_LATENCY ;

	//Unlock the flash and FPEC_CR
	if (GET_BIT(FPEC->FLASH_CR,7)== 1)
	{
		FPEC->FLASH_KEYR =  0x45670123;
		FPEC->FLASH_KEYR =  0xCDEF89AB;
	}
}

//Erase Flash Area
u8 FPEC_voidEraseFlashArea(u32 Copy_u32StartPageAddress , u32 Copy_u32EndPageAdress)
{
	u8 Local_u8ErrorState = OK;

	if ((Copy_u32StartPageAddress>=FPEC_START_PAGE_BOOT)&&(Copy_u32EndPageAdress<=FPEC_END_PAGE_BOOT))
	{
		while (GET_BIT(FPEC->FLASH_SR ,0)==1);

		for (u8 Local_u8Counter = 0 ;Local_u8Counter<=Copy_u32EndPageAdress;Local_u8Counter++)
		{
			//Start the erase operation
			SET_BIT(FPEC->FLASH_CR,1);

			FPEC->FLASH_AR = Copy_u32StartPageAddress + (Local_u8Counter *1024);
			//Start operation erase
			SET_BIT(FPEC->FLASH_CR ,6) ;
			//Waiiting until the operation is finished
			while (GET_BIT(FPEC->FLASH_SR ,0)==1);
			//END OPERATION
			SET_BIT(FPEC->FLASH_SR ,5);
			CLR_BIT(FPEC->FLASH_CR,1);
		}
	}
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Erase Flash
void FPEC_voidEraseFlash(void)
{
	u8 Local_u8Counter = 0;
	
	for (Local_u8Counter= FPEC_START_NUM_PAGE_FLASH;Local_u8Counter<=FPEC_END_NUM_PAGE_FLASH;Local_u8Counter++)
		FPEC_voidFlashPageErase(Local_u8Counter);
}

//Erase Flash Page
u8 FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	u8 Local_u8ErrorState = OK;

	if (Copy_u8PageNumber<=FPEC_MAX_NUM_PAGE)
	{
		while (GET_BIT(FPEC->FLASH_SR ,0)==1);

		SET_BIT(FPEC->FLASH_CR,1);

		FPEC->FLASH_AR = (u32)(Copy_u8PageNumber*1024)+0x08000000 ;
		//Start operation erase
		SET_BIT(FPEC->FLASH_CR ,6) ;

		while (GET_BIT(FPEC->FLASH_SR ,0)==1);

		//END OPERATION
		SET_BIT(FPEC->FLASH_SR ,5);
		CLR_BIT(FPEC->FLASH_CR,1);
	}
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Write to flash
void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	for (u8 Local_u8Counter = 0 ; Local_u8Counter<Copy_u8Length ; Local_u8Counter++)
	{

		SET_BIT(FPEC->FLASH_CR,0);

		*((volatile u16 *)(Copy_u32Address)) =  Copy_u16Data[Local_u8Counter];

		/*Waitting util the write operation is end*/

		while (GET_BIT(FPEC->FLASH_SR,0) == 1);

		SET_BIT(FPEC->FLASH_SR,5);
		CLR_BIT(FPEC->FLASH_CR,0);

		Copy_u32Address=Copy_u32Address+2;

	}
}
