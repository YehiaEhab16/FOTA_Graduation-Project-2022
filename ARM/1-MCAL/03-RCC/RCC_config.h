/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/*
 * Prescaler speed of APB1
 * 	SELECT : 1- RCC_APB1_DIV1
 * 			 2- RCC_APB1_DIV2
 * 			 3- RCC_APB1_DIV4
 * 			 4- RCC_APB1_DIV6
 * 			 5- RCC_APB1_DIV8
 * */
#define  RCC_APB1_PRESCALER		    RCC_APB1_DIV1

/*
 * Prescaler speed of APB1
 * 	SELECT : 1-RCC_APB2_DIV1
 * 			 2-RCC_APB2_DIV2
 * 			 3-RCC_APB2_DIV4
 * 			 4-RCC_APB2_DIV6
 * 			 5-RCC_APB2_DIV8
 * */
#define RCC_APB2_PRESCALER			RCC_APB2_DIV1

/*
 * Prescaler speed of APB1
 * 	SELECT : 1- RCC_APB2_DIV1
 * 			 2- RCC_APB2_DIV2
 * 			 3- RCC_APB2_DIV4
 * 			 4- RCC_APB2_DIV8
 * 			 5- RCC_APB2_DIV16
 * 			 6- RCC_APB2_DIV64
 * 			 7- RCC_APB2_DIV128
 * 			 8- RCC_APB2_DIV256
 * */

#define RCC_AHB_PRESCALER 			RCC_APB2_DIV1


/*
 * Multiplication of PLL
 * Select :
 * 			1  -RCC_PLL_MUL_2
 * 			2  -RCC_PLL_MUL_3
 * 			3  -RCC_PLL_MUL_4
 * 			4  -RCC_PLL_MUL_5
 * 			5  -RCC_PLL_MUL_6
 * 			6  -RCC_PLL_MUL_7
 * 			7  -RCC_PLL_MUL_8
 * 			8  -RCC_PLL_MUL_9
 * 			9  -RCC_PLL_MUL_10
 * 			10 -RCC_PLL_MUL_11
 * 			11 -RCC_PLL_MUL_12
 * 			12 -RCC_PLL_MUL_13
 * 			13 -RCC_PLL_MUL_14
 * 			14 -RCC_PLL_MUL_15
 * 			15 -RCC_PLL_MUL_16
 * 			16 -RCC_PLL_MUL_16
 * */

#define RCC_PLL_MULL				RCC_PLL_MUL_2

/*
 * Select the Clock System
 * Clock SYSTEM :
 *					1- RCC_HSI_SELECTION
 *					2- RCC_HSE_SELECTION
 *					3- RCC_PLL_SELECTION
 */

#define RCC_CLOCK_SYS 				RCC_HSI_SELECTION

/*
 * Select the SECURITY MODE :
 * 							1- ENABLE : RCC_ENABLE
 * 							2- DISABLE : RCC_DISABLE
 * */
#define RCC_SECURITY 				RCC_DISABLE

/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSE_1
 * 			2- RCC_PLL_HSE_12
 * */

#define RCC_PLL_HSE_ENTRY			RCC_PLL_HSE_1


/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSI
 * 			2- RCC_PLL_HSE_ENTRY
 * */

#define RCC_PLL_ENTRY				RCC_PLL_HSI

/*
 * Selection of Peripherals
 * Select : 1- RCC_ENABLE
 * 			2- RCC_DISABLE
 * */
 
//GPIOs
#define RCC_IOPA					RCC_DISABLE
#define RCC_IOPB					RCC_DISABLE
#define RCC_IOPC					RCC_DISABLE
#define RCC_IOPD					RCC_DISABLE
#define RCC_IOPE					RCC_DISABLE
#define RCC_IOPF					RCC_DISABLE
#define RCC_IOPG					RCC_DISABLE
#define RCC_AFIO					RCC_DISABLE
#define RCC_SDIO					RCC_DISABLE

//ADC & DAC
#define RCC_ADC1					RCC_DISABLE
#define RCC_ADC2					RCC_DISABLE
#define RCC_ADC3					RCC_DISABLE
#define RCC_DAC						RCC_DISABLE

//Timers
#define RCC_TIM1					RCC_DISABLE
#define RCC_TIM2					RCC_DISABLE
#define RCC_TIM3					RCC_DISABLE
#define RCC_TIM4					RCC_DISABLE
#define RCC_TIM5					RCC_DISABLE
#define RCC_TIM6					RCC_DISABLE
#define RCC_TIM7					RCC_DISABLE
#define RCC_TIM8					RCC_DISABLE
#define RCC_TIM9					RCC_DISABLE
#define RCC_TIM10					RCC_DISABLE
#define RCC_TIM11					RCC_DISABLE
#define RCC_TIM12					RCC_DISABLE
#define RCC_TIM13					RCC_DISABLE
#define RCC_TIM14					RCC_DISABLE

//Communcation Protocols
#define RCC_USART1					RCC_DISABLE
#define RCC_USART2					RCC_DISABLE
#define RCC_USART3					RCC_DISABLE
#define RCC_UART4					RCC_DISABLE
#define RCC_UART5					RCC_DISABLE

#define RCC_SPI1					RCC_DISABLE
#define RCC_SPI2					RCC_DISABLE
#define RCC_SPI3					RCC_DISABLE


#define RCC_I2C1					RCC_DISABLE
#define RCC_I2C2					RCC_DISABLE

#define RCC_CAN						RCC_DISABLE

#define RCC_USB						RCC_DISABLE

//Memory Access
#define RCC_DMA1					RCC_DISABLE
#define RCC_DMA2					RCC_DISABLE
#define RCC_SRAM					RCC_DISABLE
#define RCC_FSMC					RCC_DISABLE

//Watchdog
#define RCC_WWDG					RCC_DISABLE

//Error Check
#define RCC_CRC						RCC_DISABLE
#define RCC_FLITF					RCC_DISABLE

//Power and Backup
#define RCC_PWR						RCC_DISABLE
#define RCC_BKP						RCC_DISABLE


#endif

