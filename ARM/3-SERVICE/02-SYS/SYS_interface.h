/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):SYS 			 ***********************/
/***********************   DATE : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef SYS_INTERFACE_H_
#define SYS_INTERFACE_H_


#define SYS_NONE			10

/**
 * @def initializing all peripherals for Main ECU
 */
void SYS_voidMainInit(void);

/**
 * @def initializing all peripherals for Bootloader
 */
void SYS_voidBootInit(u8 Copy_u8Target);

/**
 * @def Initializing all the peripherals in APP ECU
 * @param Copy_pvCallBackFunc : Call Back Function : Can Interrupt on the Bus
 *
 */
void SYS_voidApp1Init(void (*Copy_pvCallBackFunc)(void));

/**
 * @def Initializing all the peripherals in APP ECU
 * @param Copy_pvCallBackFunc : Call Back Function : Can Interrupt on the Bus
 *
 */
void SYS_voidApp2Init(u8 Copy_u8InterruptLine, void (*Copy_pvCallBackFuncCan)(void));

/**
 * @def : Initializing all the peripherals in USER ECU
 * @param Copy_pvCallBackFunc_CAN Call Back Function : Can Interrupt on the Bus
 * @param Copy_pvCallBackFunc_USARTCall Back Function :USART between the STM32 and RPI
 */

void SYS_voidUserInit( void (*Copy_pvCallBackFunc_USART)(void));


#endif
