/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


//Max number of peripherals
#define RCC_NUM_REGISTER 		32

//The speed of high speed internal
#define RCC_HSI_SPEED 			8000000

//AHB Range
#define AHB_START		10
#define AHB_END			20

//APB1 Range
#define APB1_START		70
#define APB1_END		99

//APB2 Range
#define APB2_START		30
#define APB2_END		51

//Bus Offsets
#define RCC_AHB_OFFSET			10
#define RCC_APB2_OFFSET			30
#define RCC_APB1_OFFSET			70

//Clock Control Registers
#define RCC_PLL_READY 			25
#define RCC_HSE_READY			17
#define RCC_HSI_READY			1

//Clock Control Registers
#define RCC_PLL_ON 				24
#define RCC_HSE_ON				16
#define RCC_HSI_ON 				0

//Clock Selection
#define RCC_HSE_SELECTION		0b01
#define RCC_PLL_SELECTION		0b10
#define RCC_HSI_SELECTION		0b00

//APB1 Prescalar
#define RCC_APB1_DIV1		0b000
#define RCC_APB1_DIV2		0b100
#define RCC_APB1_DIV4		0b101
#define RCC_APB1_DIV6      0b110
#define RCC_APB1_DIV8      0b111

//APB2 Prescalar
#define RCC_APB2_DIV1		0b000
#define RCC_APB2_DIV2		0b100
#define RCC_APB2_DIV4		0b101
#define RCC_APB2_DIV6       0b110
#define RCC_APB2_DIV8       0b111

//AHB Prescalar
#define RCC_AHB_DIV1		0b0000
#define RCC_AHB_DIV2		0b1000
#define RCC_AHB_DIV4		0b1001
#define RCC_AHB_DIV8        0b1010
#define RCC_AHB_DIV16		0b1011
#define RCC_AHB_DIV64		0b1100
#define RCC_AHB_DIV128		0b1101
#define RCC_AHB_DIV256      0b1110

//Multiplication of PLL
#define RCC_PLL_MUL_2       0b0000
#define RCC_PLL_MUL_3       0b0001
#define RCC_PLL_MUL_4       0b0010
#define RCC_PLL_MUL_5       0b0011
#define RCC_PLL_MUL_6       0b0100
#define RCC_PLL_MUL_7       0b0101
#define RCC_PLL_MUL_8       0b0110
#define RCC_PLL_MUL_9       0b0111
#define RCC_PLL_MUL_10      0b1000
#define RCC_PLL_MUL_11      0b1001
#define RCC_PLL_MUL_12      0b1010
#define RCC_PLL_MUL_13      0b1011
#define RCC_PLL_MUL_14      0b1100
#define RCC_PLL_MUL_15      0b1101
#define RCC_PLL_MUL_16_1    0b1110
#define RCC_PLL_MUL_16_2    0b1111

//PLL Entry
#define RCC_PLL_HSI 	 100
#define RCC_PLL_HSE		 200

//HSE of PLL
#define RCC_PLL_HSE_1		 210
#define RCC_PLL_HSE_12		 110

//Bus IDs
#define RCC_AHB				0
#define RCC_APB1			1
#define RCC_APB2			2

//Function to orgainise clock crystal
void RCC_voidAjustmentClockSys (void);


#endif
