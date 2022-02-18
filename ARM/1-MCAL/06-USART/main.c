/*
 * main.c
 *
 *  Created on: Feb 17, 2022
 *      Author: saraa
 */




#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "PORT_interface.h"
#include "PORT_register.h"
#include "delay.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "USART_register.h"


int main(){


  /*Enable USART RCC*/
  RCC_voidInit();
  RCC_voidEnableClock(RCC_APB2, 2);
  RCC_voidEnableClock(RCC_APB2, 14);
  RCC_voidEnableClock(RCC_APB2,RCC_APB2_IOPA_EN);

  PORT_voidInit();
  USART_voidInit(USART1);

  /*TX push pull alternative function*/
  GPIO_u8SetPinMode(USART1_PORT, USART1_TX_PIN , OUTPUT_SPEED_2MHZ_AFPP);
  /*RX push pull alternative function*/
  GPIO_u8SetPinMode(USART1_PORT, USART1_RX_PIN , OUTPUT_SPEED_2MHZ_AFPP);
  /*CHECK PINS MODE*/
  GPIO_u8SetPinMode(GPIO_PORTB , GPIO_PIN_1 , OUTPUT_SPEED_2MHZ_PP);
  GPIO_u8SetPinMode(GPIO_PORTC , GPIO_PIN_15 , OUTPUT_SPEED_2MHZ_PP);
  GPIO_u8SetPinMode(GPIO_PORTA , GPIO_PIN_0 , OUTPUT_SPEED_2MHZ_PP);

  /*SET PINS AS LOW*/
  GPIO_u8SetPinValue(GPIO_PORTA,  GPIO_PIN_0 , GPIO_PIN_LOW);
  GPIO_u8SetPinValue(GPIO_PORTB , GPIO_PIN_1 , GPIO_PIN_LOW);
  GPIO_u8SetPinValue(GPIO_PORTB , GPIO_PIN_3 , GPIO_PIN_LOW);
  GPIO_u8SetPinValue(GPIO_PORTC , GPIO_PIN_15, GPIO_PIN_LOW);


  //u8 data = 0 ;
  //USART_voidTransmittChar('A');
	u8 data1='0' ;

  while (1)
  	{

	//  USART_voidTransmitSync(USART1, "e");

//	  GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_HIGH);
//
	 // data1= USART_u8ReceiveChar(USART1);
	  USART_u8Receive(USART1,&data1 );

//
//	  GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_LOW);
//
//
//
  		if (data1 == 'e')
  		{
  			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_HIGH);
  			delay(300000);
  			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_LOW);
  			delay(300000);


  		}
  		else
  		{
  			GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_LOW);


  		}
//
//  	}
}
return 0;
}
