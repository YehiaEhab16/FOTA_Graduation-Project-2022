/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):SYS 			 ***********************/
/***********************   DATE : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/02-RCC/RCC_interface.h"
#include "../../1-MCAL/03-NVIC/NVIC_interface.h"
#include "../../1-MCAL/05-USART/USART_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"

#include "SYS_interface.h"
#include "SYS_private.h"
#include "SYS_config.h"


extern CAN_Init_t CAN_InitStruct;
extern CAN_FilterInit_t CAN_FilterUserResponse;
extern CAN_FilterInit_t CAN_FilterAppAck;
extern CAN_FilterInit_t CAN_FilterUserRequest;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE1;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE2;

//Initializing All Peripherals
void SYS_voidMainInit(void)
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	USART_voidInit(USART1);
	USART_voidInit(USART2);
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterUserResponse);
	CAN_VoidFilterSet(&CAN_FilterAppAck);
	CAN_VoidFilterSet(&CAN_FilterUserRequest);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE1);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE2);
	NVIC_u8EnableInterrupt(USART1_IRQ);
	NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
	NVIC_u8EnableInterrupt(CAN_RX1_IRQ);
}

void SYS_voidAppInit(void (*Copy_pvCallBackFunc)(void))
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	FPEC_voidInit();
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE1);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE2);
	NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
	if(Copy_pvCallBackFunc!=NULL)
		CAN_voidCallBackFunc(CAN_FIFO_0, Copy_pvCallBackFunc);
}
