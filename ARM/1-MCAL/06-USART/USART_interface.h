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



#define	USART1		0
#define	USART2		1
#define	USART3		2

/**
 * @def : This Function that represent the initialization of three USART Module
 * @param Copy_u8UsartPort is the Number of the USART
 */
void USART_voidInit(u8 Copy_u8UsartPort);
/**
 * @def its Function that transmit the string by sync tech
 * @param Copy_u8UsartPort	is Number of USART
 * @param Copy_u8DataArr	is the array that contain the base address
 */
void USART_voidTransmitSync(u8 Copy_u8UsartPort, u8 Copy_u8DataArr[]);
/**
 * @def its Function that receive the character by sync tech
 * @param Copy_u8UsartPort	is Number of USART
 * @return return the received character
 */
u8 USART_u8ReceiveChar(u8 Copy_u8UsartPort );
/**
 * @def its Function that receive the string by sync tech
 * @param Copy_u8UsartPort is Number of USART
 * @param buffer its Data String
 * @return ErrorFlag
 */
u8 * USART_ReceiveStr(u8 Copy_u8UsartPort);
/**
 * @def its call back function that take the address of the ISR from main
 * @param Copy_u8TypeUSART is Number of USART
 * @param Notification_Pv represent the address of ISR
 * @return ErrorFlag
 */
u8 USART_u8CallBackFunc (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void));
/**
 *  * @def its Function that receive the string by Async tech
 * @param Copy_u8TypeUSART is Number of USART
 * @param Notification_Pv is address of ISR
 * @return ErrorFlag
 */
u8 USART_u8ReceiveAsy (u8 Copy_u8TypeUSART , void(*Notification_Pv)(void));


#endif
