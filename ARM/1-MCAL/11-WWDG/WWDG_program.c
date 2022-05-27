/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):WWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "WWDG_interface.h"
#include "WWDG_config.h"
#include "WWDG_private.h"
#include "WWDG_register.h"

//Reset Function
void WWDG_voidReset(u8 Copy_u8TimeoutValue)
{
	//Seting Prescalar
	switch(WWDG_PRESCALAR_VALUE)
	{
		case WWDG_DIVIDE_BY_1:CLR_BIT(WWDG->CFR,WWDG_CFR_WDGTB1);CLR_BIT(WWDG->CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_2:CLR_BIT(WWDG->CFR,WWDG_CFR_WDGTB1);SET_BIT(WWDG->CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_4:SET_BIT(WWDG->CFR,WWDG_CFR_WDGTB1);CLR_BIT(WWDG->CFR,WWDG_CFR_WDGTB0);break;
		case WWDG_DIVIDE_BY_8:SET_BIT(WWDG->CFR,WWDG_CFR_WDGTB1);SET_BIT(WWDG->CFR,WWDG_CFR_WDGTB0);break;
	}
	
	//Seting Window Value
	WWDG->CFR = WWDG_MAX_WINDOW_VALUE;
	
	//Setting Counter Value
	if(Copy_u8TimeoutValue>=WWDG_MAX_WINDOW_VALUE)
		WWDG->CR = WWDG_MAX_WINDOW_VALUE;
	
	else if(Copy_u8TimeoutValue<=WWDG_MIN_TIMEOUT_VALUE)
		WWDG->CR = WWDG_MIN_TIMEOUT_VALUE;
	
	else
		WWDG->CR = Copy_u8TimeoutValue;
	
	//Setting Early Wakeup Interrupt
	if(WWDG_EARLY_WAKEUP_INTERRUPT==1)
		SET_BIT(WWDG->CFR,WWDG_CFR_EWI);
	
	//Enabling Watchdog
	SET_BIT(WWDG->CR,WWDG_CR_WDGA);
}
