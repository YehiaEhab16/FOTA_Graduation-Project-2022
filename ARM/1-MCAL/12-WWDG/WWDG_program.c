/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):WWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WWDG_interface.h"
#include "WWDG_config.h"
#include "WWDG_private.h"
#include "WWDG_register.h"

void WWDG_voidReset(u8 Copy_u8WindowValue, u8 Copy_u8TimeoutValue)
{
	//Seting Prescalar
	switch(WWDG_PRESCALAR_VALUE)
	{
		case WWDG_DIVIDE_BY_1:CLR_BIT(WWDG_CFR,WWDG_CFR_WDGTB1);CLR_BIT(WWDG_CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_2:CLR_BIT(WWDG_CFR,WWDG_CFR_WDGTB1);SET_BIT(WWDG_CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_4:SET_BIT(WWDG_CFR,WWDG_CFR_WDGTB1);CLR_BIT(WWDG_CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_8:SET_BIT(WWDG_CFR,WWDG_CFR_WDGTB1);SET_BIT(WWDG_CFR,WWDG_CFR_WDGTB0);break;
	}
	
	//Seting Window Value
	if(Copy_u8WindowValue<=WWDG_MAX_WINDOW_VALUE)
		WWDG_CFR = Copy_u8WindowValue;
	else
		WWDG_CFR = WWDG_MAX_WINDOW_VALUE;
	
	//Setting Early Wakeup Interrupt
	if(WWDG_EARLY_WAKEUP_INTERRUPT==1)
		SET_BIT(WWDG_CFR,WWDG_CFR_EWI);
	
	//Setting Counter Value
	if(Copy_u8TimeoutValue<=WWDG_MAX_TIMEOUT_VALUE)
		WWDG_CR = Copy_u8TimeoutValue;
	else
		WWDG_CR = WWDG_MAX_TIMEOUT_VALUE;
	
	SET_BIT(WWDG_CR,WWDG_CR_T6);
	
	//Enabling Watchdog
	SET_BIT(WWDG_CR,WWDG_CR_WDGA);
}
