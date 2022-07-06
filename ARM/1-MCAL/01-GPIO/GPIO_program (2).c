/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):GPIO 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../7-Library/STD_TYPES.h"
#include "../../7-Library/BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_register.h"

//Initializing all pins direction
void GPIO_voidDirectionInit()
{
	//PortA Direction
	GPIOA->CRL  = PORTA_DIR1;
	GPIOA->CRH  = PORTA_DIR;

	//PortB Direction
	GPIOB->CRL  = PORTB_DIR1;
	GPIOB->CRH  = PORTB_DIR;
	
	//PortC Direction
	GPIOB->CRH  = PORTC_DIR;
	
	//Ports Initial Value
	GPIOA->ODR  = PORTA_VAlUE;
	GPIOB->ODR  = PORTB_VALUE;
	GPIOC->ODR  = PORTC_VALUE;
}

//Seting Output value for certain pin
u8 GPIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8Pin <= GPIO_PIN_15)	//Input Validation
		//Output High
		if(Copy_u8Value == GPIO_PIN_HIGH)
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : SET_BIT(GPIOA->ODR,Copy_u8Pin);break;
				case GPIO_PORTB : SET_BIT(GPIOB->ODR,Copy_u8Pin);break;
				case GPIO_PORTC : if (Copy_u8Pin >= GPIO_PIN_13)SET_BIT(GPIOC->ODR,Copy_u8Pin);else Local_u8ErrorState=NOK;break;
				default : Local_u8ErrorState =NOK ;
			}
		//Output Low
		else if(Copy_u8Value == GPIO_PIN_LOW)
			switch (Copy_u8Port)
			{
				case GPIO_PORTA : CLR_BIT(GPIOA->ODR,Copy_u8Pin);break;
				case GPIO_PORTB : CLR_BIT(GPIOB->ODR,Copy_u8Pin);break;
				case GPIO_PORTC : if (Copy_u8Pin >= GPIO_PIN_13)CLR_BIT(GPIOC->ODR,Copy_u8Pin);else Local_u8ErrorState=NOK;break;
				default : Local_u8ErrorState =NOK;		
			}
		//Wrong Input	
		else 
			Local_u8ErrorState =NOK;
	//Wrong Input
	else 
		Local_u8ErrorState =NOK ;
	
	return Local_u8ErrorState ;
}

//Setting Output for a certain port
u8 GPIO_u8SetPortValue(u8 Copy_u8Port,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState =OK;
	//Output High
	if(Copy_u8Value == GPIO_PIN_HIGH)
		switch (Copy_u8Port)
		{
			case GPIO_PORTA : GPIOA->ODR = Copy_u8Port;break;
			case GPIO_PORTB : GPIOB->ODR = Copy_u8Port;break;
			case GPIO_PORTC : GPIOC->ODR = Copy_u8Port;break;
			default : Local_u8ErrorState =NOK;		   break;	
		}
	//Output Low	
	else if(Copy_u8Value == GPIO_PIN_LOW)
		switch (Copy_u8Port)
		{
			case GPIO_PORTA : GPIOA->ODR = Copy_u8Port;break;
			case GPIO_PORTB : GPIOB->ODR = Copy_u8Port;break;	
			case GPIO_PORTC : GPIOC->ODR = Copy_u8Port;break;	
			default : Local_u8ErrorState =NOK ; break;
		} 			
	//Wrong Input	
	else 
		Local_u8ErrorState =NOK;
		
	return Local_u8ErrorState;
}

//Toggling output on a certin pin
u8 GPIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	u8 Local_u8ErrorState = OK; 
	if (Copy_u8Pin <= GPIO_PIN_15)	//Input Validation
		switch (Copy_u8Port)
		{
			case GPIO_PORTA : TOGGLE_BIT(GPIOA->ODR,Copy_u8Pin);break;
			case GPIO_PORTB : TOGGLE_BIT(GPIOB->ODR,Copy_u8Pin);break;
			case GPIO_PORTC :if (Copy_u8Pin >= GPIO_PIN_13)TOGGLE_BIT(GPIOC->ODR,Copy_u8Pin);else Local_u8ErrorState=NOK;break;
		    default: Local_u8ErrorState = NOK;
		}
	//Wrong Input
	else
		Local_u8ErrorState = NOK ;
	
	return Local_u8ErrorState ;
}

//Reading Input Value from a certain pin
u8 GPIO_u8GetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8*Copy_pu8Value)
{
	u8 Local_u8ErrorState =OK ;
	if(Copy_u8Pin <= GPIO_PIN_15)	//Input Validation
		switch (Copy_u8Port)
			{
				case GPIO_PORTA :*Copy_pu8Value=GET_BIT(GPIOA->IDR,Copy_u8Pin);break;
				case GPIO_PORTB :*Copy_pu8Value=GET_BIT(GPIOB->IDR,Copy_u8Pin);break;
				case GPIO_PORTC :if (Copy_u8Pin >= GPIO_PIN_13)*Copy_pu8Value=GET_BIT(GPIOC->IDR,Copy_u8Pin);else Local_u8ErrorState=NOK;break;
				default: Local_u8ErrorState=NOK;break;
			}
	//Wrong Input
	else 
		Local_u8ErrorState = NOK;	
	
	return Local_u8ErrorState ; 
}
