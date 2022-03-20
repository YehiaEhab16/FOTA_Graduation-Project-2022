/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):USART 			 ***********************/
/***********************   DATE : 15-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"

#include "USART_S_interface.h"
#include "USART_S_private.h"
#include "USART_S_config.h"

void USART_S_voidInit(void)
{
		
  RCC_voidInit();
  RCC_voidEnableClock((u8)RCC_APB2,(u8) RCC_APB2_USART1_EN);
  RCC_voidEnableClock((u8)RCC_APB2,(u8) RCC_APB2_IOPA_EN);
  PORT_voidInit();
  
/*Option1 Select : 	1- USART1
					2- USART2
					3- USART3	
					*/
  USART_voidInit(USART1);
  
}



void USART_S_voidDisable(void)
{
	RCC_u8DisableClock ((u8)RCC_APB2);
}
