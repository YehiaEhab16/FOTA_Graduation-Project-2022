/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):IWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "IWDG_interface.h"
#include "IWDG_config.h"
#include "IWDG_private.h"
#include "IWDG_register.h"

void IWDG_voidReset(u16 Copy_u16TimeoutValue)
{
	IWDG_KR = 0x5555;
	
	//Updating Prescalar
	CLR_BIT(IWDG_SR,IWDG_SR_PVU);
	IWDG_PR &= IWDG_PRESCALAR_MASK;
	IWDG_PR |= IWDG_PRESCALAR_VALUE;
	
	//Reload Counter
	CLR_BIT(IWDG_SR,IWDG_SR_RVU);
	if(Copy_u16TimeoutValue<=IWDG_MAX_RELOAD_VALUE)
		IWDG_RLR = Copy_u16TimeoutValue;
	else
		IWDG_RLR = IWDG_MAX_RELOAD_VALUE;
	IWDG_KR = 0xAAAA;
	
	//Staring Counter
	IWDG_KR = 0xCCCC;
}
