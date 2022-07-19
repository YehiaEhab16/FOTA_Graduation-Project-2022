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
#include "../../1-MCAL/04-EXTI/EXTI_interface.h"
#include "../../1-MCAL/05-USART/USART_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"
#include "../../1-MCAL/13-ADC/ADC_interface.h"

#include "../../2-HAL/02-DCM/DCM_interface.h"
#include "../../2-HAL/08-COM/COM_interface.h"

#include "../../5-RTOS/RTOS_interface.h"

#include "../../7-APP/APP ECU_1/ISR.h"

#include "SYS_interface.h"
#include "SYS_private.h"
#include "SYS_config.h"

//Motor
DCM_t Global_DCM_tMotorVehicle = {DCM_PORTA,DCM_PIN5,DCM_PIN4,DCM_PIN3,DCM_PIN2};

extern CAN_Init_t CAN_InitStruct;
extern CAN_FilterInit_t CAN_FilterUserResponse;
extern CAN_FilterInit_t CAN_FilterAppAck;
extern CAN_FilterInit_t CAN_FilterUserRequest;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE1;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE2;
extern CAN_FilterInit_t CAN_FilterUpdateNotifcation;
extern CAN_FilterInit_t CAN_FilterUserDiagnostics;
extern CAN_FilterInit_t CAN_FilterApp1Update;
extern CAN_FilterInit_t CAN_FilterApp2Update;
extern CAN_FilterInit_t CAN_FilterAppDiagnostics;

// Initializing All Peripherals
void SYS_voidMainInit(void)
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	USART_voidInit(USART1);
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterUserResponse);
	CAN_VoidFilterSet(&CAN_FilterAppAck);
	CAN_VoidFilterSet(&CAN_FilterUserRequest);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE1);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics_MODE2);
}

void SYS_voidBootInit(u8 Copy_u8Target)
{
	RCC_voidInit();
	GPIO_voidDirectionInit();

	CAN_voidInit(&CAN_InitStruct);
	if(Copy_u8Target==SYS_BOOT_APP1)
		CAN_VoidFilterSet(&CAN_FilterApp1Update);
	else if(Copy_u8Target==SYS_BOOT_APP2)
		CAN_VoidFilterSet(&CAN_FilterApp2Update);

	FPEC_voidInit();
}

void SYS_voidApp1Init(void (*Copy_pvCallBackFunc)(void))
{
	u16 Local_u16Val;
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	FPEC_voidInit();
	ADC_voidInit();
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics);
	CAN_VoidFilterSet(&CAN_FilterApp2Update);
	NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
	if (Copy_pvCallBackFunc != NULL)
		CAN_voidCallBackFunc(CAN_FIFO_0, Copy_pvCallBackFunc);

	RTOS_voidInit();
}

void SYS_voidApp2Init(u8 Copy_u8InterruptLine, void (*Copy_pvCallBackFuncCan)(void))
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	FPEC_voidInit();
	DCM_voidInit(&Global_DCM_tMotorVehicle);
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterAppDiagnostics);
	CAN_VoidFilterSet(&CAN_FilterApp1Update);
	SYS_voidEnableInterruptNVIC(Global_DCM_tMotorVehicle.DCM_u8PinENCA,SYS_NONE);
	EXTI_voidInit(Global_DCM_tMotorVehicle.DCM_u8PinENCA,EXTI_RISING_EDGE);
	EXTI_voidSetCallBack(Global_DCM_tMotorVehicle.DCM_u8PinENCA, &DCM_voidMotorISR);

	if (Copy_pvCallBackFuncCan != NULL)
		CAN_voidCallBackFunc(CAN_FIFO_0, Copy_pvCallBackFuncCan);

	RTOS_voidInit();
}

void SYS_voidUserInit(void (*Copy_pvCallBackFunc_CAN)(void))
{
	RCC_voidInit();
	GPIO_voidDirectionInit();
	NVIC_voidInit();
	USART_voidInit(USART1);
	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterUserDiagnostics);
	CAN_VoidFilterSet(&CAN_FilterUpdateNotifcation);
	SYS_voidEnableInterruptNVIC(SYS_COM_DIAG, SYS_COM_UPDATE);
	EXTI_voidInit(SYS_COM_DIAG,EXTI_RISING_EDGE);
	EXTI_voidInit(SYS_COM_UPDATE,EXTI_RISING_EDGE);
	EXTI_voidSetCallBack(SYS_COM_DIAG,  &COM_voidRecieveDaignosticsRequest);
	EXTI_voidSetCallBack(SYS_COM_UPDATE, &COM_voidRecieveUpdateResponse);

	if (Copy_pvCallBackFunc_CAN != NULL)
		CAN_voidCallBackFunc(CAN_FIFO_0, Copy_pvCallBackFunc_CAN);
}

void SYS_voidEnableInterruptNVIC(u8 Copy_u8Interrupt1, u8 Copy_u8Interrupt2)
{
	NVIC_u8EnableInterrupt(TIM1_UP_IRQ);
	NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
	switch (Copy_u8Interrupt1)
	{
		case EXTI_LINE0:NVIC_u8EnableInterrupt(EXTI0_IRQ);break;
		case EXTI_LINE1:NVIC_u8EnableInterrupt(EXTI1_IRQ);break;
		case EXTI_LINE2:NVIC_u8EnableInterrupt(EXTI2_IRQ);break;
		case EXTI_LINE3:NVIC_u8EnableInterrupt(EXTI3_IRQ);break;
		default:break;
	}

	switch (Copy_u8Interrupt2)
	{
		case EXTI_LINE0:NVIC_u8EnableInterrupt(EXTI0_IRQ);break;
		case EXTI_LINE1:NVIC_u8EnableInterrupt(EXTI1_IRQ);break;
		case EXTI_LINE2:NVIC_u8EnableInterrupt(EXTI2_IRQ);break;
		case EXTI_LINE3:NVIC_u8EnableInterrupt(EXTI3_IRQ);break;
		default:break;
	}
}
