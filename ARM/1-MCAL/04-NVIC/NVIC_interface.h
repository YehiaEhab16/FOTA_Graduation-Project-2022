/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):NVIC 			 ***********************/
/***********************   DATA : 2-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_
/**
 *  @def this represent he position of the Maskable interrupt
 */
typedef enum
{
		WWDG_IRQ    = 0       ,
		PVD_IRQ               ,
		TAMPER_IRQ            ,
		RTC_IRQ               ,
		FLASH_IRQ             ,
		RCC_IRQ               ,
		EXTI0_IRQ             ,
		EXTI1_IRQ             ,
		EXTI2_IRQ             ,
		EXTI3_IRQ             ,
		EXTI4_IRQ             ,
		DMA1_Channel1_IRQ     ,
		DMA1_Channel2_IRQ     ,
		DMA1_Channel3_IRQ     ,
		DMA1_Channel4_IRQ     ,
		DMA1_Channel5_IRQ     ,
		DMA1_Channel6_IRQ     ,
		DMA1_Channel7_IRQ     ,
		ADC1_2_IRQ            ,
		USB_HP_CAN_IRQ        ,
		USB_LP_CAN_IRQ        ,
		CAN_RX1_IRQ           ,
		CAN_SCE_IRQ           ,
		EXTI9_5_IRQ           ,
		TIM1_BRK_IRQ          ,
		TIM1_UP_IRQ           ,
		TIM1_TRG_COM_IRQ      ,
		TIM1_CC_IRQ           ,
		TIM2_IRQ              ,
		TIM3_IRQ              ,
		TIM4_IRQ              ,
		I2C1_EV_IRQ           ,
		I2C1_ER_IRQ           ,
		I2C2_EV_IRQ           ,
		I2C2_ER_IRQ           ,
		SPI1_IRQ              ,
		SPI2_IRQ              ,
		USART1_IRQ            ,
		USART2_IRQ            ,
		USART3_IRQ            ,
		EXTI15_10_IRQ         ,
		RTCAlarm_IRQ          ,
		USBWakeup_IRQ         ,
		TIM8_BRK_IRQ          ,
		TIM8_UP_IRQ           ,
		TIM8_TRG_COM_IRQ      ,
		TIM8_CC_IRQ           ,
		ADC3_IRQ              ,
		FSMC_IRQ              ,
		SDIO_IRQ              ,
		TIM5_IRQ              ,
		SPI3_IRQ              ,
		UART4_IRQ             ,
		UART5_IRQ             ,
		TIM6_IRQ              ,
		TIM7_IRQ              ,
		DMA2_Channel1_IRQ     ,
		DMA2_Channel2_IRQ     ,
		DMA2_Channel3_IRQ     ,
		DMA2_Channel4_5_IRQ

}NVIC_I;
/**
 * @def this is represent of NVIC core peripheral initialization
 */
void NVIC_voidInit (void);
/**
 * @def Enable the interrupt
 * @param Copy_u8NameInterrupt Number of the interrupt
 * @return ErrprFlag
 */
u8 NVIC_u8EnableInterrupt (u8 Copy_u8NameInterrupt);
/**
 * @def Disable the interrupt
 * @param Copy_u8NameInterrupt Number of the interrupt
 * @return Error Flag
 */
u8 NVIC_u8disableInterrupt (u8 Copy_u8NameInterrupt);
/**
 * @def Set the pending flag
 * @param Copy_u8NameInterrupt Number of the interrupt
 * @return Error Flag
 */
u8 NVIC_u8EnablePendingFlag (u8 Copy_u8NameInterrupt);
/**
 * @def Clear the pending flag
 * @param Copy_u8NameInterrupt  Number of the interrupt
 * @return Error Flag
 */
u8 NVIC_u8disablePendingFlag (u8 Copy_u8NameInterrupt);

/**
 * @def Get Value of active flag
 * @param Copy_u8NameInterrupt  Number of the interrupt
 * @param Copy_u8ActiveFlagVal  Value of state of the Active Flag
 * @return Error Flag
 */
u8 NVIC_u8GetActiveFlage (u8 Copy_u8NameInterrupt , u8*Copy_u8ActiveFlagVal);
/**
 * @def Set the priority of interrupt
 * @param Copy_u8NameInterrupt   Number of the interrupt
 * @param Copy_u8NumbePriority   Value of Priority
 * @return Error Flag
 */
u8 NVIC_u8SetPriority (u8 Copy_u8NameInterrupt , u8 Copy_u8NumbePriority);
/**
 * @def GetRegisterNumbe
 * @param Copy_u8NameInterrupt  Number of the interrupt
 * @return Error Flag
 */
u8 NVIC_u8GetRegisterNumber (u8 Copy_u8NameInterrupt,u8*Copy_u8RegisterNumberVal );
/**
 * @def GetRegisterBit
 * @param Copy_u8NameInterrupt  Number of the interrupt
 * @return Error Flag
 */
u8 NVIC_u8GetRegisterBit (u8 Copy_u8NameInterrupt,u8*Copy_u8RegisterBitVal );










#endif
