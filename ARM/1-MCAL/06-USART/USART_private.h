   /*****************************************************/
  /* AUTHOR         : GP2022                           */
 /* VERSION        : V01                              */
/*****************************************************/
 
#ifndef  USART_PRIVATE_H_
#define  USART_PRIVATE_H_



#define	USART1		0
#define	USART2		1
#define	USART3		2


#define UE      13
#define TE      3
#define RE      2
#define TC      6
#define RXNE    5

#define BR_9600			0x341
#define BR_115200		0x45

typedef struct
{
	volatile u32    SR    ;
	volatile u32    DR    ;
	volatile u32    BRR   ;
	volatile u32    CR1   ;
	volatile u32    CR2   ;
	volatile u32    CR3   ;
	volatile u32    GRPR  ;
}USART_t;

static struct Peripheral USART_Peripherals[3] = {
		{RCC_APB2, RCC_APB2_USART1_EN},
		{RCC_APB1, RCC_APB1_USART2_EN},
		{RCC_APB1, RCC_APB1_USART3_EN}
};





#endif