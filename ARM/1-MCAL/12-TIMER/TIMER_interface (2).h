/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):Dec 22, 2021	 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define TIMER_RISING 	0
#define TIMER_FALLING	1


#define 	TIM1		    0
#define 	TIM2		    1
#define 	TIM3		    2
#define 	TIM4		    3

#define 	TIM_CHANNEL1		                1
#define 	TIM_CHANNEL2		                2
#define 	TIM_CHANNEL3		                3
#define 	TIM_CHANNEL4		                4

#define 	TIM_DISABLE		                0
#define 	TIM_ENABLE		                1

#define 	UP_COUNT		                0
#define 	DOWN_COUNT  	                1

#define 	DIV_1			                0
#define 	DIV_2			                1
#define 	DIV_4			                2

#define     ONE_PULSE_MODE                  0
#define     PERIODIC_MODE                   1

#define 	CENTER_ALIGNED_MODE_1			0
#define 	CENTER_ALIGNED_MODE_2			1
#define 	CENTER_ALIGNED_MODE_3			2
#define 	EDGE_ALIGNED_MODE				3

#define 	mSEC			                1000
#define 	uSEC			                1


#define PORTA_PIN0		TIM2_CH1
#define PORTA_PIN1		TIM2_CH2
#define PORTA_PIN2		TIM2_CH3
#define PORTA_PIN3		TIM2_CH4
#define PORTA_PIN6		TIM3_CH1
#define PORTA_PIN7		TIM3_CH2
#define PORTA_PIN8		TIM1_CH1
#define PORTA_PIN9		TIM1_CH2
#define PORTA_PIN10		TIM1_CH3
#define PORTA_PIN11		TIM1_CH4
#define PORTB_PIN0		TIM3_CH3
#define PORTB_PIN1		TIM3_CH4


typedef struct
{
	u16 Prescaler;
	u16 Period;
	u8 Period_Mode;					/* PERIODIC_MODE or ONE_PULSE_MODE */
	u8 Direction;					/* UP_COUNT or DOWN_COUNT */
	u8 Clock_Div;					/* DIV_1, DIV_2 or DIV_3 */
	u8 Center_Aligned_Mode;			/* EDGE_ALIGNED_MODE, CENTER_ALIGNED_MODE_(1,2 OR 3)*/
	u8 Update_State;	            /* ENABLE or DISABLE */
	u8 AutoReloadBuffer;            /* ENABLE or DISABLE */
	u8 Counter_State;               /* ENABLE or DISABLE */
	u8 UDI_State;                   /* ENABLE or DISABLE */
}GPT_Config;

/*Function Prototypes*/



void TIMER_voidCapture (u8 Copy_u8Timer , u8 Copy_u8Edge , u32 Copy_u8AutoReload , u8 Copy_u8Channel );

void TIMER_u8StopChannel (u8 Copy_u8Timer , u8 Copy_u8Channel );

u32 TIMER_u8GetCaptureValue (u8 Copy_u8Timer , u8 Copy_u8Channel);

void TIMER_voidSelectEdge (u8 Copy_u8Timer,u8 Copy_u8Edge , u8 Copy_u8Channel );

/**
 * @def   Configures timer properties (doesn't start timer)
 * @param Copy_u8Timer: TIM1, TIM2, TIM3 or TIM4
 * 		  GPT_ConfigPtr: pointer to timer configuration struct
 * @return
 */
void TIMER_voidTimerConfig(u8 Copy_u8Timer, GPT_Config *GPT_ConfigPtr);
/**
 * @def   Start timer
 * @param Copy_u8Timer: TIM1, TIM2, TIM3 or TIM4
 * @return
 */
void TIMER_StartTimer(u8 Copy_u8Timer);
/**
 * @def   Stop timer
 * @param Copy_u8Timer: TIM1, TIM2, TIM3 or TIM4
 * @return
 */
void TIMER_StopTimer(u8 Copy_u8Timer);
/**
 * @def   Busy waiting
 * @param Copy_u8Timer: TIM1, TIM2, TIM3 or TIM4
 * 		  Copy_u32Delay: delay time
 * 		  Copy_u16Unit: unit of delay time (mSEC or uSEC)
 * @return
 */
void TIMER_Delay(u8 Copy_u8Timer, u32 Copy_u32Delay, u32 Copy_u16Unit);
/**
 * @def   Read current value of counter register
 * @param Copy_u8Timer: TIM1, TIM2, TIM3 or TIM4
 * @return
 */
u16 TIMER_u16GetCount(u8 Copy_u8Timer);
/**
 * @def   Output Compare (toggle mode) for desired channel
 * @param PORTx_PINx: port and pin for the desired timer channel
 * 		  Copy_u16Period: toggling period
 * 		  Copy_u16CompareValue: time at which output event (toggle) is generated
 * 		  Copy_u16Unit: unit of toggling period and compare value (mSEC or uSEC)
 * @return
 */
void TIMER_OutputCompare(u8 Copy_u8PORT_PIN, u16 Copy_u16Period, u16 Copy_u16CompareValue, u16 Copy_u16Unit);
/**
 * @def   Generates PWM signal
 * @param PORTx_PINx: port and pin for the desired timer channel
 * 		  Copy_u16Period: pwm signal period
 * 		  Copy_u16DutyCycle: Duty cycle of the pwm signal [(x)%]
 * 		  Copy_u16Unit: unit of toggling period and compare value (mSEC or uSEC)
 * @return
 */
void TIMER_PWM(u8 Copy_u8PORT_PIN, u16 Copy_u16Period, u16 Copy_u16DutyCycle, u16 Copy_u16Unit);



#endif
