   /*****************************************************/
  /* AUTHOR         : GP2022                           */
 /* VERSION        : V01                              */
/*****************************************************/
#ifndef  USRT_INTERFACE_H_
#define  USRT_INTERFACE_H_

#define USART1_PORT			GPIO_PORTA
#define USART1_TX_PIN		GPIO_PIN_9
#define USART1_RX_PIN		GPIO_PIN_10

#define USART2_PORT			GPIO_PORTA
#define USART2_TX_PIN		GPIO_PIN_2
#define USART2_RX_PIN		GPIO_PIN_3

#define USART3_PORT			GPIO_PORTB
#define USART3_TX_PIN		GPIO_PIN_10
#define USART3_RX_PIN		GPIO_PIN_11


void USART_voidInit(u8 Copy_u8UsartPort);
void USART_voidTransmitSync(u8 Copy_u8UsartPort, u8 Copy_u8DataArr[]);
u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort);
u8 *USART_ReceiveStr(u8 Copy_u8UsartPort, u8 *buffer);


#endif