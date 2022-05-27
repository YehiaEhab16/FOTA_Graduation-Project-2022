/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):USART 			 ***********************/
/***********************   DATA : 09-04-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_register.h"

//Array of ISR Functions
void (*USART_voidCallBackFunc[3])(void) ={NULL} ;

//Array including all USART Base Addresses
static USART_t *const usart_ports[] = {
		(USART_t*)USART1_BASE,
		(USART_t*)USART2_BASE,
		(USART_t*)USART3_BASE,
};

//Geting USART Port and setting correct base address
static USART_t *USART_Get(u8 usart) {
	switch(usart) {
	case USART1: return (USART_t*)USART1_BASE;
	case USART2: return (USART_t*)USART2_BASE;
	case USART3: return (USART_t*)USART3_BASE;
	default:     return (USART_t*)USART1_BASE;
	}
}

//Initializing USART Communication
void USART_voidInit( u8 Copy_u8UsartPort )
{
	//USART_t *USART = usart_ports[Copy_u8UsartPort];
	USART_t *USART = USART_Get(Copy_u8UsartPort);
	/*FCK = 8 MHZ   baudrate = 9600*/
	USART->BRR =BAUD_RATE ;
	/*USART enable        */
	SET_BIT(USART -> CR1,USART_UE);
	/*Transmitter enable  */
	SET_BIT(USART -> CR1,USART_TE);
	/*Receiver enable     */
	SET_BIT(USART -> CR1,USART_RE);
	/* Clear All The Register*/
	USART -> SR =0;
}

//Synchronous Transmition 
void USART_voidTransmitSync(u8 Copy_u8UsartPort, u8 Copy_u8DataArr[])
{
	USART_t *USART = usart_ports[Copy_u8UsartPort];
	u8 Local_u8Iterator = 0;
	while (Copy_u8DataArr[Local_u8Iterator] != USART_NULL_CHAR)
	{
		USART -> DR = Copy_u8DataArr[Local_u8Iterator];
		while(GET_BIT (USART -> SR , USART_TC) == 0);
		Local_u8Iterator++;
	}
}

//Recieve data as character
u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort)
{
	u8 Local_u8Data;
	USART_t *USART = USART_Get(Copy_u8UsartPort);
	
	while((GET_BIT((USART -> SR), USART_RXNE) == 0));

	Local_u8Data = USART -> DR;

	return Local_u8Data;
}

//Recieve data as string
u8 *USART_ReceiveStr(u8 Copy_u8UsartPort)
{
	u8 Local_u8Iterator = 0 , Local_u8ReceivedData, Local_u8Data[30];
	while( ( Local_u8ReceivedData = USART_u8ReceiveChar(Copy_u8UsartPort) ) != USART_STOP_CHAR)
	{
		Local_u8Data[Local_u8Iterator] = Local_u8ReceivedData ;
		Local_u8Iterator++;
	}

	Local_u8Data[Local_u8Iterator] = USART_NULL_CHAR;

	return Local_u8Data;

}

//Asynchronous Transmition 
u8 USART_u8ReceiveAsy (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void))
{
	u8 Local_u8ErrorState =OK ;
	if (Notification_Pv !=NULL)
		SET_BIT(USART_Get(Copy_u8TypeUSART)->CR1,USART_RXNIE);
	//Wrong Input
	else
		Local_u8ErrorState = NOK ;

	return Local_u8ErrorState ;

}

//Setting Callcack Function
u8 USART_u8CallBackFunc (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void))
{
	u8 Local_u8ErrorState  = OK;

	if (Notification_Pv != NULL)
		USART_voidCallBackFunc[Copy_u8TypeUSART] = Notification_Pv ;
	
	//Wrong Input
	else
		Local_u8ErrorState  = NOK;

	return Local_u8ErrorState ;
}

//ISR for USART1
void USART1_IRQHandler (void)
{
	if (GET_BIT(USART_Get(USART1)->CR1,USART_RXNIE))
		USART_voidCallBackFunc[USART1]();
}

//ISR for USART2
void USART2_IRQHandler (void)
{
	if (GET_BIT(USART_Get(USART2)->CR1,USART_RXNIE))
		USART_voidCallBackFunc[USART2]();
}

//ISR for USART3
void USART3_IRQHandler (void)
{
	if (GET_BIT(USART_Get(USART3)->CR1,USART_RXNIE))
		USART_voidCallBackFunc[USART3]();
}
