#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_register.h"



void (*USART_voidCallBackFunc[3])(void) ={NULL} ;


static USART_t *const usart_ports[] = {
		(USART_t*) USART1_BASE,
		(USART_t*)USART2_BASE,
		(USART_t*)USART3_BASE,
};

static USART_t *USART_Get(u8 usart) {
	switch(usart) {
	case USART1: return (USART_t*)USART1_BASE;
	case USART2: return (USART_t*)USART2_BASE;
	case USART3: return (USART_t*)USART3_BASE;
	default:     return (USART_t*)USART1_BASE;
	}
}

void USART_voidInit( u8 Copy_u8UsartPort )
{
	//USART_t *USART = usart_ports[Copy_u8UsartPort];
	USART_t *USART = USART_Get(Copy_u8UsartPort);
	/*FCK = 8 MHZ   baudrate = 9600*/
	USART->BRR =BAUD_RATE ;
	/*USART enable        */
	SET_BIT(USART -> CR1,UE);
	/*Transmitter enable  */
	SET_BIT(USART -> CR1,TE);
	/*Receiver enable     */
	SET_BIT(USART -> CR1,RE);
	/* Clear All The Register*/
	USART -> SR =0;
}



void USART_voidTransmitSync(u8 Copy_u8UsartPort, u8 Copy_u8DataArr[])
{
	USART_t *USART = usart_ports[Copy_u8UsartPort];
	u8 Local_u8Iterator = 0;
	while (Copy_u8DataArr[Local_u8Iterator] != '\0')
	{
		USART -> DR = Copy_u8DataArr[Local_u8Iterator];
		while(GET_BIT (USART -> SR , TC) == 0);
		Local_u8Iterator++;
	}

}
/*recieve data as character*/
//u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort)
//{
//	USART_t *USART = USART_Get(Copy_u8UsartPort);
//	while (GET_BIT(USART -> SR , RXNE) == 0);
//	return (0xFF & (USART -> DR));
//
//}
u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort )
{
	u8  Copy_u8Data;
	USART_t *USART = USART_Get(Copy_u8UsartPort);


	while((GET_BIT((USART -> SR), RXNE) == 0));

	Copy_u8Data = USART -> DR;

	return Copy_u8Data ;
}






/*Recieve data as string*/
u8 data[30];
u8 * USART_ReceiveStr(u8 Copy_u8UsartPort)
{
	u8 i = 0 , RecData ;
	while( ( RecData = USART_u8ReceiveChar(Copy_u8UsartPort) ) != '\r' ){

		data[ i ] = RecData ;
		i++;
	}

	data[i] = '\0';

	return ( data );

}

u8 USART_u8ReceiveAsy (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void))
{
	u8 Local_u8ErrorState =OK ;
	if (Notification_Pv !=NULL)
	{
		SET_BIT(USART_Get(Copy_u8TypeUSART)->CR1,RXNIE);
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;

}

u8 USART_u8CallBackFunc (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void))
{
	u8 Local_u8ErrorState  =OK ;

	if (Notification_Pv != NULL)
	{
		USART_voidCallBackFunc[Copy_u8TypeUSART] = Notification_Pv ;

	}
	else
	{
		Local_u8ErrorState  =NOK;
	}

	return Local_u8ErrorState ;

}



void USART1_IRQHandler (void)
{

	if (GET_BIT(USART_Get(USART1)->CR1,RXNIE))
	{
		USART_voidCallBackFunc[USART1]();
	}
	else
	{
		//Nothing

	}

}

void USART2_IRQHandler (void)
{
	if (GET_BIT(USART_Get(USART2)->CR1,RXNIE))
	{
		USART_voidCallBackFunc[USART2]();
	}
	else
	{
		//Nothing

	}
}

void USART3_IRQHandler (void)
{

	if (GET_BIT(USART_Get(USART3)->CR1,RXNIE))
	{
		USART_voidCallBackFunc[USART3]();
	}
	else
	{
		//Nothing

	}

}

