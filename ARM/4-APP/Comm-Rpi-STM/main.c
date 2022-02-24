
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "NVIC_interface.h"
#include "USART_interface.h"


void ISR (void);

void main (void)
{


	RCC_voidInit();

	struct Peripheral Uart = {RCC_APB2,RCC_APB2_USART1_EN};
	struct Peripheral GPIO_PORTA1 = {RCC_APB2,RCC_APB2_IOPA_EN};

	RCC_u8EnableClock(&GPIO_PORTA1);
	RCC_u8EnableClock(&Uart);

	PORT_voidInit() ;

	NVIC_voidInit();

	USART_voidInit (USART1);

	 NVIC_u8EnableInterrupt(USART1_IRQ);

	 USART_u8ReceiveAsy(USART1,ISR);

	 USART_u8CallBackFunc(USART1,ISR);



	GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_LOW);
	//const char data[2] = {'1','2'} ;

	//u8 data =  'a' ;
	while (1)
	{

		/* //USART1_voidTransmitString("fefewdw");


			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_HIGH);

			USART1_u8Receive(&data1);
			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_LOW);



		if (data1 == '1')
		{
			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_HIGH);
		}
		else
		{
			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_LOW);

		}
		 */

	}

}
void ISR (void)
{
	u8 data =0  ;
	GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_LOW);


	while (data < '0')
	{
		data = USART_u8ReceiveChar(USART1);
	}

	if (data == '2')
	{
		USART_voidTransmitSync(USART1, (u8 *)"1");
		while (USART_u8ReceiveChar(USART1)=='2')
		{
			USART_voidTransmitSync(USART1, (u8 *)"1");
		}
		GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_HIGH);

	}
	else
	{
		GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_LOW);

	}


}
