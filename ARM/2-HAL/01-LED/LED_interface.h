/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):LED 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


#define LED_ACTIVE_HIGH				1
#define LED_ACTIVE_LOW 				0

#define LED_PORTA					GPIO_PORTA
#define LED_PORTB					GPIO_PORTB
#define LED_PORTC					GPIO_PORTC

#define LED_PIN0					GPIO_PIN_0
#define LED_PIN1					GPIO_PIN_1
#define LED_PIN2					GPIO_PIN_2
#define LED_PIN3					GPIO_PIN_3
#define LED_PIN4					GPIO_PIN_4
#define LED_PIN5					GPIO_PIN_5
#define LED_PIN6					GPIO_PIN_6
#define LED_PIN7					GPIO_PIN_7
#define LED_PIN8					GPIO_PIN_8
#define LED_PIN9					GPIO_PIN_9
#define LED_PIN10					GPIO_PIN_10
#define LED_PIN11					GPIO_PIN_11
#define LED_PIN12					GPIO_PIN_12
#define LED_PIN13					GPIO_PIN_13
#define LED_PIN14					GPIO_PIN_14
#define LED_PIN15					GPIO_PIN_15


typedef struct
{
	u8 LED_u8Port;
	u8 LED_u8Pin;
	u8 LED_u8Connection;
}LED_t;

void LED_voidLedOn(LED_t* Copy_pLED_tStructLed);
void LED_voidLedOff(LED_t* Copy_pLED_tStructLed);

void LED_voidLedToggle(LED_t* Copy_pLED_tStructLed);


#endif