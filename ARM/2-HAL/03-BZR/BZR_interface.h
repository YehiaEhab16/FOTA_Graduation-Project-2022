/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):BZR 			 ***********************/
/***********************   DATA : 5-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef BZR_INTERFACE_H_
#define BZR_INTERFACE_H_


#define BZR_PORTA					GPIO_PORTA
#define BZR_PORTB					GPIO_PORTB
#define BZR_PORTC					GPIO_PORTC

#define BZR_PIN0					GPIO_PIN_0
#define BZR_PIN1					GPIO_PIN_1
#define BZR_PIN2					GPIO_PIN_2
#define BZR_PIN3					GPIO_PIN_3
#define BZR_PIN4					GPIO_PIN_4
#define BZR_PIN5					GPIO_PIN_5
#define BZR_PIN6					GPIO_PIN_6
#define BZR_PIN7					GPIO_PIN_7
#define BZR_PIN8					GPIO_PIN_8
#define BZR_PIN9					GPIO_PIN_9
#define BZR_PIN10					GPIO_PIN_10
#define BZR_PIN11					GPIO_PIN_11
#define BZR_PIN12					GPIO_PIN_12
#define BZR_PIN13					GPIO_PIN_13
#define BZR_PIN14					GPIO_PIN_14
#define BZR_PIN15					GPIO_PIN_15


/**
 * @def   Turn On BZR
 * @param Copy_u8Port: Buzzer Port
 * @param Copy_u8Pin:  Buzzer Pin
 */
void BZR_voidOn(u8 Copy_u8Port,u8 Copy_u8Pin);

/**
 * @def   Turn Off BZR
 * @param Copy_u8Port: Buzzer Port
 * @param Copy_u8Pin:  Buzzer Pin
 */
void BZR_voidOff(u8 Copy_u8Port,u8 Copy_u8Pin);

/**
 * @def   Toggle BZR
 * @param Copy_u8Port: Buzzer Port
 * @param Copy_u8Pin:  Buzzer Pin
 */
void BZR_voidToggle(u8 Copy_u8Port,u8 Copy_u8Pin);


#endif