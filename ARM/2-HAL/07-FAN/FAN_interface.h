/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):FAN 			 ***********************/
/***********************   DATE : 29-6-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef FAN_INTERFACE_H_
#define FAN_INTERFACE_H_


#define FAN_ACTIVE_HIGH				1
#define FAN_ACTIVE_LOW 				0

#define FAN_PORTA					GPIO_PORTA
#define FAN_PORTB					GPIO_PORTB
#define FAN_PORTC					GPIO_PORTC

#define FAN_PIN0					GPIO_PIN_0
#define FAN_PIN1					GPIO_PIN_1
#define FAN_PIN2					GPIO_PIN_2
#define FAN_PIN3					GPIO_PIN_3
#define FAN_PIN4					GPIO_PIN_4
#define FAN_PIN5					GPIO_PIN_5
#define FAN_PIN6					GPIO_PIN_6
#define FAN_PIN7					GPIO_PIN_7
#define FAN_PIN8					GPIO_PIN_8
#define FAN_PIN9					GPIO_PIN_9
#define FAN_PIN10					GPIO_PIN_10
#define FAN_PIN11					GPIO_PIN_11
#define FAN_PIN12					GPIO_PIN_12
#define FAN_PIN13					GPIO_PIN_13
#define FAN_PIN14					GPIO_PIN_14
#define FAN_PIN15					GPIO_PIN_15


typedef struct
{
	u8 FAN_u8Port;
	u8 FAN_u8Pin;
	u8 FAN_u8Connection;
}FAN_t;

/**
 * @def   Turn On FAN
 * @param Copy_pFAN_tStructLed: struct contains FAN Info
 */
void FAN_voidFanOn(FAN_t* Copy_pFAN_tStructLed);

/**
 * @def   Turn Off FAN
 * @param Copy_pFAN_tStructLed: struct contains FAN Info
 */
void FAN_voidFanOff(FAN_t* Copy_pFAN_tStructLed);


#endif