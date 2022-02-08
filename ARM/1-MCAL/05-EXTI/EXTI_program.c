/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"



void EXTI_voidInit()
{
	#if 	EXTI_MODE	== 	RISING
		SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif 	EXTI_MODE	== 	FALLING
		SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#elif	EXTI_MODE	==	ON_CHANGE
		SET_BIT(EXTI -> RTSR , EXTI_LINE);
		SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else 	
		#error "Wrong Mode and Line Choice"
	#endif
	/*Disable interrupt*/
	CLR_BIT(EXTI->IMR , EXTI_LINE);
}

void EXTI_voidEnableEXTI(u8 Copy_u8Line)
{
	SET_BIT(EXTI->IMR , Copy_u8Line);
}
void EXTI_voidDisableEXTI(u8 Copy_u8Line)
{
	CLR_BIT(EXTI->IMR , Copy_u8Line);
}
void EXTI_voidSwTrigger(u8 Copy_u8Line)
{
	SET_BIT(EXTI -> SWIER , Copy_u8Line);
}
void EXTI_voidSetSignalLatch(u8 Copy_u8Line , u8 Copy_u8Mode) /*To change the mode in the run time*/
{
	switch(Copy_u8Mode)
	{
		case RISING 	:	SET_BIT(EXTI -> RTSR , Copy_u8Line); 	break;
		case FALLING	:	SET_BIT(EXTI -> FTSR , Copy_u8Line); 	break;
		case ON_CHANGE 	:	SET_BIT(EXTI -> RTSR , Copy_u8Line); 
							SET_BIT(EXTI -> RTSR , Copy_u8Line); 	break;
	}
}
