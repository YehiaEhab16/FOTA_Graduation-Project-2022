#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PORT_interface.h"
#include "PORT_register.h"
#include "delay.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"


int main(){


  /*Enable USART RCC*/
  RCC_voidInit();
  PORT_voidInit();
  USART_voidInit(USART1);

  /*TX push pull alternative function*/
  GPIO_u8SetPinMode(USART1_PORT , USART1_TX_PIN , OUTPUT_SPEED_2MHZ_AFPP);
  GPIO_u8SetPinMode(GPIO_PORTB , GPIO_PIN_1 , OUTPUT_SPEED_2MHZ_PP);
  GPIO_u8SetPinMode(GPIO_PORTC , GPIO_PIN_13 , OUTPUT_SPEED_2MHZ_PP);
  GPIO_u8SetPinMode(GPIO_PORTA , GPIO_PIN_10 , INPUT_FLOATING);
  GPIO_u8SetPinValue(GPIO_PORTB , GPIO_PIN_1 , GPIO_PIN_LOW);
  GPIO_u8SetPinValue(GPIO_PORTB , GPIO_PIN_3 , GPIO_PIN_LOW);

  //u8 data = 0 ;
  //USART_voidTransmittChar('A');
  while (1){

    USART_voidTransmitChar(USART1_BASE, "Mayar Alaa Esraa\r\n");
    GPIO_u8SetPinValue(GPIO_PORTC , GPIO_PIN_13 , GPIO_PIN_HIGH);
    delay(200000);
    USART_voidTransmitChar(USART1_BASE, " ");
    delay(500000);
  }
  return 0;
}