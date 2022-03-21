/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/*Peripherals*/
//GPIOs
#define RCC_IOPA_PER				0
#define RCC_IOPB					1
#define RCC_IOPC					2
#define RCC_IOPD					3
#define RCC_IOPE					4
#define RCC_IOPF					5
#define RCC_IOPG					6
#define RCC_AFIO					7
#define RCC_SDIO					8

//ADC & DAC
#define RCC_ADC1					9
#define RCC_ADC2					10
#define RCC_ADC3					11
#define RCC_DAC						12

//Timers
#define RCC_TIM1					13
#define RCC_TIM2					14
#define RCC_TIM3					15
#define RCC_TIM4					16
#define RCC_TIM5					17
#define RCC_TIM6					18
#define RCC_TIM7					19
#define RCC_TIM8					20
#define RCC_TIM9					21
#define RCC_TIM10					22
#define RCC_TIM11					23
#define RCC_TIM12					24
#define RCC_TIM13					25
#define RCC_TIM14					26

//Communcation Protocols
#define RCC_USART1					27
#define RCC_USART2					28
#define RCC_USART3					29
#define RCC_UART4					30
#define RCC_UART5					31

#define RCC_SPI1					32
#define RCC_SPI2					33
#define RCC_SPI3					34


#define RCC_I2C1					35
#define RCC_I2C2					36

#define RCC_CAN						37

#define RCC_USB						38

//Memory Access
#define RCC_DMA1					39
#define RCC_DMA2					40
#define RCC_SRAM					41
#define RCC_FSMC					42

//Watchdog
#define RCC_WWDG					43

//Error Check
#define RCC_CRC						44
#define RCC_FLITF					45

//Power and Backup
#define RCC_PWR						46
#define RCC_BKP						47


void RCC_voidInit(void);
u8 RCC_u8DisablePeripheral(u8 Copy_u8PeripheralID);

#endif
