/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):DCM 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_


#define DCM_PORTA					GPIO_PORTA
#define DCM_PORTB					GPIO_PORTB
#define DCM_PORTC					GPIO_PORTC

#define DCM_PIN0					GPIO_PIN_0
#define DCM_PIN1					GPIO_PIN_1
#define DCM_PIN2					GPIO_PIN_2
#define DCM_PIN3					GPIO_PIN_3
#define DCM_PIN4					GPIO_PIN_4
#define DCM_PIN5					GPIO_PIN_5
#define DCM_PIN6					GPIO_PIN_6
#define DCM_PIN7					GPIO_PIN_7
#define DCM_PIN8					GPIO_PIN_8
#define DCM_PIN9					GPIO_PIN_9
#define DCM_PIN10					GPIO_PIN_10
#define DCM_PIN11					GPIO_PIN_11
#define DCM_PIN12					GPIO_PIN_12
#define DCM_PIN13					GPIO_PIN_13
#define DCM_PIN14					GPIO_PIN_14
#define DCM_PIN15					GPIO_PIN_15

typedef struct
{
	u8 DCM_u8Port;
	u8 DCM_u8PinA;
	u8 DCM_u8PinB;
}DCM_t;

//Controlling motor direction (2 pins)
void DCM_voidRotateCCW(DCM_t* Copy_pDCM_tStructMotor);
void DCM_voidRotateCW(DCM_t* Copy_pDCM_tStructMotor);
void DCM_voidStop2(DCM_t* Copy_pDCM_tStructMotor);

//Controlling motor from 1 pin (1 direction)
void DCM_voidRotate(DCM_t* Copy_pDCM_tStructMotor);
void DCM_voidStop(DCM_t* Copy_pDCM_tStructMotor);

#endif