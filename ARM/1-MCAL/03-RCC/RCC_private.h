/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define RCC_NUM_REGISTER 		32

/*the speed of high speed internal */
#define RCC_HSI_SPEED 			8000000


#define ENABLE 			1
#define DISABLE			0


#define AHB_START		10
#define AHB_END			20

#define APB1_START		51
#define APB1_END		30

#define APB2_START		70
#define APB2_END		99


/*
 * the offset of all busses
 * 												*/
#define RCC_AHB_OFFSET			10
#define RCC_APB2_OFFSET			30
#define RCC_APB1_OFFSET			70

/*
 * CLOCK CONTROL REGISTER
 * */
#define RCC_PLL_READY 			25
#define RCC_HSE_READY			17
#define RCC_HSI_READY			1

#define RCC_PLL_ON 				24
#define RCC_HSE_ON				16
#define RCC_HSI_ON 				0

/*
 * The Clock Selection
 *
 */

#define RCC_HSE_SELECTION		0b01
#define RCC_PLL_SELECTION		0b10
#define RCC_HSI_SELECTION		0b00

/*
 * prescaler of APB1
 * */
#define RCC_APB1_DIV1		0b000
#define RCC_APB1_DIV2		0b100
#define RCC_APB1_DIV4		0b101
#define RCC_APB1_DIV6      0b110
#define RCC_APB1_DIV8      0b111


/*
 * prescaler of APB2
 * */

#define RCC_APB2_DIV1		0b000
#define RCC_APB2_DIV2		0b100
#define RCC_APB2_DIV4		0b101
#define RCC_APB2_DIV6       0b110
#define RCC_APB2_DIV8       0b111

/*
 * prescaler of AHB
 *
 */
#define RCC_AHB_DIV1		0b0000
#define RCC_AHB_DIV2		0b1000
#define RCC_AHB_DIV4		0b1001
#define RCC_AHB_DIV8        0b1010
#define RCC_AHB_DIV16		0b1011
#define RCC_AHB_DIV64		0b1100
#define RCC_AHB_DIV128		0b1101
#define RCC_AHB_DIV256      0b1110

/*
 * Multiplication of pll
 * */
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



/*Select the Pll entry
 *
 * Select :
 * 			1- HSI
 * 			2- HSE
 *
 * */

#define RCC_PLL_HSI 	 100
#define RCC_PLL_HSE		 200


/*
 * Select the HSE of PLL
 * select =
 * */
#define RCC_PLL_HSE_1		 210
#define RCC_PLL_HSE_12		 110



/**
 * @def this Function That organize the Clock of Crystal
 */
void RCC_voidAjustmentClockSys (void);


/**
 *
 * @param Copy_u8Bus
 * @param Copy_u8StateBus
 * @return Error Flag
 */
u8 RCC_u8ChangeModeBuses (u8 Copy_u8Bus , u8 Copy_u8StateBus);
















#endif
