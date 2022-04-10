/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):GPIO 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

//Port Options
#define GPIO_PORTA          0
#define GPIO_PORTB          1
#define GPIO_PORTC          2

//Pin Options
#define GPIO_PIN_0			0
#define GPIO_PIN_1          1
#define GPIO_PIN_2          2
#define GPIO_PIN_3          3
#define GPIO_PIN_4          4
#define GPIO_PIN_5          5
#define GPIO_PIN_6          6
#define GPIO_PIN_7          7
#define GPIO_PIN_8          8
#define GPIO_PIN_9          9
#define GPIO_PIN_10         10
#define GPIO_PIN_11         11
#define GPIO_PIN_12         12
#define GPIO_PIN_13         13
#define GPIO_PIN_14         14
#define GPIO_PIN_15         15

//Pin and Port States
#define GPIO_PORT_HIGH		0xff
#define GPIO_PORT_LOW		0

#define GPIO_PIN_HIGH		1
#define GPIO_PIN_LOW		0

/**
 * @def initialize all pin directions and initial values
 */
void GPIO_voidDirectionInit();

/**
 * @def function that sets output value to specific pin
 * @param Copy_u8Port required GPIO Port
 * @param Copy_u8Pin required GPIO Pin
 * @param Copy_u8Value required Output Value
 * @return ErrorFlag
 */
u8 GPIO_u8SetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8Value);

/**
 * @def function that sets output value to specific port
 * @param Copy_u8Port required GPIO Port
 * @param Copy_u8Value required Output Value
 * @return ErrorFlag
 */
u8 GPIO_u8SetPortValue (u8 Copy_u8Port,u8 Copy_u8Value);

/**
 * @def function that gets toggles output on specific pin
 * @param Copy_u8Port required GPIO Port
 * @param Copy_u8Pin required GPIO Pin
 * @return ErrorFlag
 */
u8 GPIO_u8TogglePinValue (u8 Copy_u8Port, u8 Copy_u8Pin);

/**
 * @def function that sets output value to specific pin
 * @param Copy_u8Port required GPIO Port
 * @param Copy_u8Pin required GPIO Pin
 * @param Copy_pu8Value is the read input value
 * @return ErrorFlag
 */
u8 GPIO_u8GetPinValue (u8 Copy_u8Port , u8 Copy_u8Pin , u8 *Copy_pu8Value);


#endif