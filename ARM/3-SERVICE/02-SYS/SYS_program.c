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
#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"

#include "SYS_interface.h"
#include "SYS_private.h"
#include "SYS_config.h"


extern CAN_Init_t CAN_InitStruct;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics;

//Initializing All Peripherals
void SYS_voidMainInit(void)
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics);
	
}

void SYS_voidAppInit(void (*Copy_pvCallBackFunc)(void))
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	FPEC_voidInit();
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics);
	NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
	if(Copy_pvCallBackFunc!=NULL)
		CAN_voidCallBackFunc(Copy_pvCallBackFunc);
}
