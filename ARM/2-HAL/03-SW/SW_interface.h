/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):SW 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_


#define SW_PORTA					GPIO_PORTA
#define SW_PORTB					GPIO_PORTB
#define SW_PORTC					GPIO_PORTC

#define SW_PIN0						GPIO_PIN_0
#define SW_PIN1						GPIO_PIN_1
#define SW_PIN2						GPIO_PIN_2
#define SW_PIN3						GPIO_PIN_3
#define SW_PIN4						GPIO_PIN_4
#define SW_PIN5						GPIO_PIN_5
#define SW_PIN6						GPIO_PIN_6
#define SW_PIN7						GPIO_PIN_7
#define SW_PIN8						GPIO_PIN_8
#define SW_PIN9						GPIO_PIN_9
#define SW_PIN10					GPIO_PIN_10
#define SW_PIN11					GPIO_PIN_11
#define SW_PIN12					GPIO_PIN_12
#define SW_PIN13					GPIO_PIN_13
#define SW_PIN14					GPIO_PIN_14
#define SW_PIN15					GPIO_PIN_15

#define PRESSED					1
#define NOT_PRESSED				0

#define SW_u8PULL_UP 			0
#define SW_u8PULL_DOWN			1

typedef struct
{
	u8 SW_u8Port;
	u8 SW_u8Pin;
	u8 SW_u8Connection;
	u32 SW_u32DebounceTime;
}SW_t;

u8 SW_u8ReadSwicth(SW_t* Copy_pSW_tStruct);

#endif