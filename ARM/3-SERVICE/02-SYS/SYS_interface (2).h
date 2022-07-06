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

/**
 * @def initializing all peripherals for Main ECU
 */
void SYS_voidMainInit(void);

/**
 * @def initializing all peripherals for Application ECU
 */
void SYS_voidAppInit(void (*Copy_pvCallBackFunc)(void));
void SYS_voidUserInit(void (*Copy_pvCallBackFunc_CAN)(void), void (*Copy_pvCallBackFunc_USART)(void));
#endif
