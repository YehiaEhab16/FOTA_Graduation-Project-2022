#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "PORT_register.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"


static USART_t *const usart_ports[] = {
    USART1_BASE,
    USART2_BASE,
    USART3_BASE,
};

static USART_t *USART_Get(u8 usart) {
    switch(usart) {
        case USART1: return usart1;
        case USART2: return usart2;
        case USART3: return usart3;
        default: return usart1;
    }
}

void USART_voidInit( u8 Copy_u8UsartPort )
{
	RCC_u8EnableClock(&USART_Peripherals[Copy_u8UsartPort]);
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
			while(GET_BIT (USART -> SR , 6) == 0);
			Local_u8Iterator++;
		}

}
/*recieve data as character*/
u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort)
{
	USART_t *USART = USART_Get(Copy_u8UsartPort);
	while (GET_BIT(USART -> SR , RXNE) == 0);
	return (0xFF & (USART -> DR));

}
/*Recieve data as string*/
u8 *USART_ReceiveStr(u8 Copy_u8UsartPort, u8 *buffer) {
    while(*buffer) {
        *buffer++ = USART_u8ReceiveChar(Copy_u8UsartPort);
    }
    return buffer;
}

