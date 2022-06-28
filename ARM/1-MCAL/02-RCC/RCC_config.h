/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/*Peripheral States: RCC_ENABLE / RCC_DISABLE*/
//GPIIOs
#define RCC_IOPA_STATE	                 RCC_ENABLE
#define RCC_IOPB_STATE	                 RCC_ENABLE
#define RCC_IOPC_STATE	                 RCC_DISABLE
#define RCC_IOPD_STATE	                 RCC_DISABLE
#define RCC_IOPE_STATE	                 RCC_DISABLE
#define RCC_IOPF_STATE	                 RCC_DISABLE
#define RCC_IOPG_STATE	                 RCC_DISABLE
#define RCC_AFIO_STATE	                 RCC_DISABLE
#define RCC_SDIO_STATE		             RCC_DISABLE

//ADCs
#define RCC_ADC1_STATE	                 RCC_DISABLE
#define RCC_ADC2_STATE	                 RCC_DISABLE
#define RCC_ADC3_STATE	                 RCC_DISABLE
#define RCC_DAC_STATE					 RCC_DISABLE

//Timers
#define RCC_TIM1_STATE	                 RCC_DISABLE
#define RCC_TIM2_STATE	                 RCC_DISABLE
#define RCC_TIM3_STATE	                 RCC_DISABLE
#define RCC_TIM4_STATE	                 RCC_DISABLE
#define RCC_TIM5_STATE	                 RCC_DISABLE
#define RCC_TIM6_STATE	                 RCC_DISABLE
#define RCC_TIM7_STATE	                 RCC_DISABLE
#define RCC_TIM8_STATE	                 RCC_DISABLE
#define RCC_TIM9_STATE	                 RCC_DISABLE
#define RCC_TIM10_STATE	             	 RCC_DISABLE
#define RCC_TIM11_STATE	             	 RCC_DISABLE
#define RCC_TIM12_STATE	             	 RCC_DISABLE
#define RCC_TIM13_STATE	             	 RCC_DISABLE
#define RCC_TIM14_STATE	             	 RCC_DISABLE

//Communication Protocols
#define RCC_USART1_STATE	             RCC_DISABLE
#define RCC_USART2_STATE	             RCC_DISABLE
#define RCC_USART3_STATE	             RCC_DISABLE
#define RCC_UART4_STATE	             	 RCC_DISABLE
#define RCC_UART5_STATE	              	 RCC_DISABLE

#define RCC_SPI1_STATE	                 RCC_DISABLE
#define RCC_SPI2_STATE	                 RCC_DISABLE
#define RCC_SPI3_STATE	                 RCC_DISABLE

#define RCC_I2C1_STATE	                 RCC_DISABLE
#define RCC_I2C2_STATE	                 RCC_DISABLE

#define RCC_CAN_STATE	                 RCC_ENABLE
#define RCC_USB_STATE	                 RCC_ENABLE

//Watchdog
#define RCC_WWDG_STATE	                 RCC_DISABLE

//Memory Access
#define RCC_DMA1_STATE		             RCC_DISABLE
#define RCC_DMA2_STATE		             RCC_DISABLE
#define RCC_SRAM_STATE		             RCC_DISABLE
#define RCC_FLITF_STATE		             RCC_DISABLE
#define RCC_FSMC_STATE		             RCC_DISABLE

//Error Check
#define RCC_CRC_STATE		             RCC_DISABLE

//Power & Backup
#define RCC_PWR_STATE	                 RCC_DISABLE
#define RCC_BKP_STATE	                 RCC_DISABLE

/*
 * Prescaler speed of APB1
 * 	SELECT : 1- RCC_APB1_DIV1
 * 			 2- RCC_APB1_DIV2
 * 			 3- RCC_APB1_DIV4
 * 			 4- RCC_APB1_DIV6
 * 			 5- RCC_APB1_DIV8
 * */
#define  RCC_APB1_PRESCALER					 RCC_APB1_DIV1

/*
 * Prescaler speed of APB1
 * 	SELECT : 1-RCC_APB2_DIV1
 * 			 2-RCC_APB2_DIV2
 * 			 3-RCC_APB2_DIV4
 * 			 4-RCC_APB2_DIV6
 * 			 5-RCC_APB2_DIV8
 * */
#define RCC_APB2_PRESCALER					 RCC_APB2_DIV1

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

#define RCC_AHB_PRESCALER 					 RCC_APB2_DIV1


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
 */

#define RCC_PLL_MULL						 RCC_PLL_MUL_2

/*
 * Select the Clock System
 * Clock SYSTEM :
 *					1- RCC_HSI_SELECTION
 *					2- RCC_HSE_SELECTION
 *					3- RCC_PLL_SELECTION
 */

#define RCC_CLOCK_SYS 						 RCC_HSI_SELECTION

/*
 * Select the SECURITY MODE :
 * 							1- RCC_ENABLE
 * 							2- RCC_DISABLE
 * */
#define RCC_SECURITY 						 RCC_DISABLE

/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSE_1
 * 			2- RCC_PLL_HSE_12
 * */

#define RCC_PLL_HSE_ENTRY					 RCC_PLL_HSE_12


/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSI
 * 			2- RCC_PLL_HSE_ENTRY
 * */

#define RCC_PLL_ENTRY						 RCC_PLL_HSE_ENTRY


#endif

