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


//Peripheral States: RCC_ENABLE / RCC_DISABLE
#define RCC_ENABLE			1
#define RCC_DISABLE 		0

/*Peripherals*/
//GPIIOs
#define RCC_IOPA			32
#define RCC_IOPB			33
#define RCC_IOPC			34
#define RCC_IOPD			35
#define RCC_IOPE			36
#define RCC_IOPF			37
#define RCC_IOPG			38
#define RCC_AFIO			30
#define RCC_SDIO			20

//ADCs
#define RCC_ADC1			39
#define RCC_ADC2			40
#define RCC_ADC3			45
#define RCC_DAC				99

//Timers
#define RCC_TIM1			41
#define RCC_TIM2			70
#define RCC_TIM3			71
#define RCC_TIM4			72
#define RCC_TIM5			73
#define RCC_TIM6			74
#define RCC_TIM7			75
#define RCC_TIM8			43
#define RCC_TIM9			49
#define RCC_TIM10			50
#define RCC_TIM11			51
#define RCC_TIM12			76
#define RCC_TIM13			77
#define RCC_TIM14			78
	
//Communication Protocols
#define RCC_USART1			44
#define RCC_USART2			87
#define RCC_USART3			88
#define RCC_UART4			89
#define RCC_UART5			90

#define RCC_SPI1			42
#define RCC_SPI2			84
#define RCC_SPI3			85

#define RCC_I2C1			92
#define RCC_I2C2			91

#define RCC_CAN				95
#define RCC_USB				93


//Watchdog
#define RCC_WWDG			81

//Memory Access
#define RCC_DMA1			10
#define RCC_DMA2			11
#define RCC_SRAM			12
#define RCC_FSMC			18
#define RCC_FLITF			14

//Error Check
#define RCC_CRC				16

//Power & Backup
#define RCC_PWR				98
#define RCC_BKP				97


/**
 * @def function to initialize RCC peripheral and provide clock for all needed peripherals
 */
void RCC_voidInit (void);

/**
 * @def function to disable certain peripheral
 * @param Copy_u8PeripheralID required peripheral
 * @return ErrorFlag
 */
u8 RCC_u8DisableClock(u8 Copy_u8PeripheralID);

/**
 * @def function to Enable certain peripheral
 * @param Copy_u8PeripheralID required peripheral
 * @return ErrorFlag
 */
u8 RCC_u8EnableClock(u8 Copy_u8PeripheralID);
/**
 * @def function to change bus mode
 * @param Copy_u8Bus required Bus
 * @param Copy_u8StateBus required Bus State
 * @return ErrorFlag
 */
u8 RCC_u8ChangeModeBuses (u8 Copy_u8Bus , u8 Copy_u8StateBus);


#endif
