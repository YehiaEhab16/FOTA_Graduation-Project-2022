/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/**
 *
 * ENABLE : enable the peripheral
 * DISABLE : disable the peripheral
 *
 */


/**
 * @def buss iD of Periherial for AHB
 */
#define RCC_AHB_SDIO_STATE		             DISABLE
#define RCC_AHB_FSMC_STATE		             DISABLE
#define RCC_AHB_CRC_STATE		             DISABLE
#define RCC_AHB_FLITF_STATE		             DISABLE
#define RCC_AHB_SRAM_STATE		             DISABLE
#define RCC_AHB_DMA2_STATE		             DISABLE
#define RCC_AHB_DMA1_STATE		             DISABLE

/**
 * @def buss iD of Periherial for APB2
 */
#define RCC_APB2_TIM11_STATE	             DISABLE
#define RCC_APB2_TIM10_STATE	             DISABLE
#define RCC_APB2_TIM9_STATE	                 DISABLE
#define RCC_APB2_ADC3_STATE	                 DISABLE
#define RCC_APB2_USART1_STATE	             DISABLE
#define RCC_APB2_TIM8_STATE	                 DISABLE
#define RCC_APB2_SPI1_STATE	                 DISABLE
#define RCC_APB2_TIM1_STATE	                 DISABLE
#define RCC_APB2_ADC2_STATE	                 DISABLE
#define RCC_APB2_ADC1_STATE	                 DISABLE
#define RCC_APB2_IOPG_STATE	                 DISABLE
#define RCC_APB2_IOPF_STATE	                 DISABLE
#define RCC_APB2_IOPE_STATE	                 DISABLE
#define RCC_APB2_IOPD_STATE	                 DISABLE
#define RCC_APB2_IOPC_STATE	                 DISABLE
#define RCC_APB2_IOPB_STATE	                 DISABLE
#define RCC_APB2_IOPA_STATE	                 DISABLE
#define RCC_APB2_AFIO_STATE	                 DISABLE

/**
 * @def buss iD of Periherial for APB1
 */
#define RCC_APB1_DAC_STATE					 DISABLE
#define RCC_APB1_PWR_STATE	                 DISABLE
#define RCC_APB1_BKP_STATE	                 DISABLE
#define RCC_APB1_CAN_STATE	                 DISABLE
#define RCC_APB1_USB_STATE	                 DISABLE
#define RCC_APB1_I2C1_STATE	                 DISABLE
#define RCC_APB1_I2C2_STATE	                 DISABLE
#define RCC_APB1_UART5_STATE	             DISABLE
#define RCC_APB1_UART4_STATE	             DISABLE
#define RCC_APB1_USART3_STATE	             DISABLE
#define RCC_APB1_USART2_STATE	             DISABLE
#define RCC_APB1_SPI3_STATE	                 DISABLE
#define RCC_APB1_SPI2_STATE	                 DISABLE
#define RCC_APB1_WWDG_STATE	                 DISABLE
#define RCC_APB1_TIM14_STATE	             DISABLE
#define RCC_APB1_TIM13_STATE	             DISABLE
#define RCC_APB1_TIM12_STATE	             DISABLE
#define RCC_APB1_TIM7_STATE	                 DISABLE
#define RCC_APB1_TIM6_STATE	                 DISABLE
#define RCC_APB1_TIM5_STATE	                 DISABLE
#define RCC_APB1_TIM4_STATE	                 DISABLE
#define RCC_APB1_TIM3_STATE	                 DISABLE
#define RCC_APB1_TIM2_STATE	                 DISABLE


/*
 * Prescaler speed of APB1
 * 	SELECT : 1- RCC_APB1_DIV1
 * 			 2- RCC_APB1_DIV2
 * 			 3- RCC_APB1_DIV4
 * 			 4- RCC_APB1_DIV6
 * 			 5- RCC_APB1_DIV8
 *
 * */
#define  RCC_APB1_PRESCALER		    RCC_APB1_DIV1

/*
 * Prescaler speed of APB1
 * 	SELECT : 1-RCC_APB2_DIV1
 * 			 2-RCC_APB2_DIV2
 * 			 3-RCC_APB2_DIV4
 * 			 4-RCC_APB2_DIV6
 * 			 5-RCC_APB2_DIV8
 *
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
 *
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
 *
 *
 * */

#define RCC_PLL_MULL	RCC_PLL_MUL_2

/*
 * Select the Clock System
 * Clock SYSTEM :
 *					1- RCC_HSI_SELECTION
 *					2- RCC_HSE_SELECTION
 *					3- RCC_PLL_SELECTION
 */

#define RCC_CLOCK_SYS 		RCC_HSI_SELECTION

/*
 * Select the SECURITY MODE :
 * 							1- ENABLE : RCC_ENABLE
 * 							2- DISABLE : RCC_DISABLE
 *
 * */
#define RCC_SECURITY 			RCC_DISABLE

/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSE_1
 * 			2- RCC_PLL_HSE_12
 *
 * */

#define RCC_PLL_HSE_ENTRY		RCC_PLL_HSE_12


/*
 * Selection of Chooses of PLL
 * Select : 1- RCC_PLL_HSI
 * 			2- RCC_PLL_HSE_ENTRY
 *
 * */

#define RCC_PLL_ENTRY			RCC_PLL_HSE_ENTRY




#endif

