/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):STK 			 ***********************/
/***********************   DATA : 3-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_


/**
 *
 * @def Init System ticks : 1- Disable System Tick
 * 							2- Disable Interrupt
 * 							3- Select the prescaler CLK
 *
 */
void STK_voidInit(void);

/**
 * @def Enable the timer
 */
void STK_voidEnableTimer (void);

/**
 * @def	Disable Timer
 *
 */
void STK_voidDisableTimer (void);

/**
 * @def Delay Function by Mille Second
 * @param Copy_u8TimeMilleSecond :Time by Mille Second
 */
void STK_voidDelay(u32 Copy_u8TimeMilleSecond);

/**
 * @def Delay Function by Mille Second Asynchronous Single iteration
 * @param Copy_u8TimeMilleSecond  Time with Mille Second
 * @param Copy_pvNotifi the pointer to function (Call Back Function )
 * @return Error Flag
 */
u8 STK_u8DelayAsySingle (u32 Copy_u8TimeMilleSecond , void(*Copy_pvNotifi)(void));

/**
 * @def Delay Function by Mille Second Asynchronous Multi iteration
 * @param Copy_u8TimeMilleSecond  Time with Mille Second
 * @param Copy_pvNotifi the pointer to function (Call Back Function )
 * @return Error Flag
 */
u8 STK_u8DelayAsyPeriodic (u32 Copy_u8TimeMilleSecond , void(*Copy_pvNotifi)(void));

/**
 * @def Get the Time
 * @return time in Mille Second
 */
u8 STK_u8GetTime (void);

/**
 * @def Get the Remaining Time
 * @return remainning time
 */
u8 STK_u8GetRemainigTime(void);


#endif

