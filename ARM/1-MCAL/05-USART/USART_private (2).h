/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):USART 			 ***********************/
/***********************   DATA : 09-04-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
 
#ifndef  USART_PRIVATE_H_
#define  USART_PRIVATE_H_


#define	USART1				0
#define	USART2				1
#define	USART3				2

#define USART_UE      			13
#define USART_TE      			3
#define USART_RE      			2
#define USART_TC      			6
#define USART_RXNE    			5
#define USART_RXNIE				5

#define BR_9600				0x341
#define BR_115200			0x45

#define USART_STOP_CHAR		'\r'
#define USART_NULL_CHAR		'\0'

#endif
