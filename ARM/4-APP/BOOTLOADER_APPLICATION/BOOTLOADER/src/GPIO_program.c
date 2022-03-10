/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):GPIO 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_register.h"


u8 GPIO_u8TogglePinValue (u8 Copy_u8Port, u8 Copy_u8Pin)
{
	u8 Local_u8ErrorState = OK ; 
	if (Copy_u8Pin <= GPIO_PIN_15)
	{
		switch (Copy_u8Port)
		{
			case GPIO_PORTA : TOGGLE_BIT(PORTA_ODR,Copy_u8Pin);break;
			case GPIO_PORTB : TOGGLE_BIT(PORTB_ODR,Copy_u8Pin);break;
			case GPIO_PORTC :if (Copy_u8Pin >= GPIO_PIN_13){TOGGLE_BIT(PORTC_ODR,Copy_u8Pin);}else{Local_u8ErrorState =NOK ;}break;
		    default : Local_u8ErrorState =NOK ;
		}
		
	}
	else 
	{
		Local_u8ErrorState = NOK ;
	}

	
	return Local_u8ErrorState ;
}

u8 GPIO_u8SetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8Pin <= GPIO_PIN_15)
	{
		
		if (Copy_u8Value == GPIO_PIN_HIGH)
		{
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : SET_BIT(PORTA_ODR,Copy_u8Pin);break;
				case GPIO_PORTB : SET_BIT(PORTB_ODR,Copy_u8Pin);break;
				case GPIO_PORTC : if (Copy_u8Pin >= GPIO_PIN_13){SET_BIT(PORTC_ODR,Copy_u8Pin);}else{Local_u8ErrorState =NOK ;}break;
				default : Local_u8ErrorState =NOK ;
				
				
			}
		}
		else if (Copy_u8Value == GPIO_PIN_LOW)
		{
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : CLR_BIT(PORTA_ODR,Copy_u8Pin);break;
				case GPIO_PORTB : CLR_BIT(PORTB_ODR,Copy_u8Pin);break;
				case GPIO_PORTC : if (Copy_u8Pin >= GPIO_PIN_13){CLR_BIT(PORTC_ODR,Copy_u8Pin);}else{Local_u8ErrorState =NOK ;}break;
				default : Local_u8ErrorState =NOK ;
					
					
			}
		}	
		else 
		{
			Local_u8ErrorState =NOK;
		}
	
	
	}
	else 
	{
		
		Local_u8ErrorState =NOK ;
	}
	
	
	
	return Local_u8ErrorState ;
}


u8 GPIO_u8SetPortValue (u8 Copy_u8Port,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState =OK;
	if (Copy_u8Value == GPIO_PIN_HIGH)
		{
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : PORTA_ODR = Copy_u8Port;break;
				case GPIO_PORTB : PORTB_ODR = Copy_u8Port;break;
				case GPIO_PORTC : PORTC_ODR = Copy_u8Port;break;
				default : Local_u8ErrorState =NOK ; break ;
				
				
			}
		}
	else if (Copy_u8Value == GPIO_PIN_LOW)
		{
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : PORTA_ODR = Copy_u8Port;break;
				case GPIO_PORTB : PORTB_ODR = Copy_u8Port;break;	
				case GPIO_PORTC : PORTC_ODR = Copy_u8Port;break;	
				default : Local_u8ErrorState =NOK ; break;
			} 			
			
		}	
	else 
		{
			Local_u8ErrorState =NOK;
		}
	
	
	
	
	return Local_u8ErrorState;
}


u8 GPIO_u8GetPinValue (u8 Copy_u8Port , u8 Copy_u8Pin , u8*Copy_pu8Value)
{
	u8 Local_u8ErrorState =OK ;
	
	if (Copy_u8Pin <= GPIO_PIN_15)
	{
		switch (Copy_u8Port)
			{
				case GPIO_PORTA :*Copy_pu8Value=GET_BIT(PORTA_IDR,Copy_u8Pin);break;
				case GPIO_PORTB :*Copy_pu8Value=GET_BIT(PORTB_IDR,Copy_u8Pin);break;
				case GPIO_PORTC :if (Copy_u8Pin >= GPIO_PIN_13){*Copy_pu8Value=GET_BIT(PORTC_IDR,Copy_u8Pin);}else{Local_u8ErrorState =NOK ;}break;
				default : Local_u8ErrorState =NOK ; break ;
				
				
			}
	}
	else 
	{
		Local_u8ErrorState =NOK ;
	}

	
	
	
	
	
	return Local_u8ErrorState ; 
}
