/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):TIMER			 ***********************/
/***********************   DATA : 11-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

//CallBack Functions
void (*TIM2_CallBack)(void);
void (*TIM3_CallBack)(void);
void (*TIM4_CallBack)(void);

//Getting Timer Id
static TIMER_t * Get_timer( u8 timer)
{
	switch (timer)
	{
	case TIM1: return((TIMER_t *)TIM1_BASE);
	case TIM2: return((TIMER_t *)TIM2_BASE);
	case TIM3: return((TIMER_t *)TIM3_BASE);
	case TIM4: return((TIMER_t *)TIM4_BASE);
	default : return((TIMER_t *)TIM2_BASE);
	}
}

//Timer Configuration
void TIMER_voidTimerConfig(u8 Copy_u8Timer, GPT_Config *GPT_ConfigPtr)
{
	TIMER_t* timer = Get_timer(Copy_u8Timer);
	timer->PSC = GPT_ConfigPtr->Prescaler - 1;
	timer->ARR = GPT_ConfigPtr->Period;

	switch(GPT_ConfigPtr->Update_State)
	{
		case DISABLE: CLR_BIT(timer->CR[0],1);break;
		case ENABLE: SET_BIT(timer->CR[0],1);break;
	}

	switch(GPT_ConfigPtr->Period_Mode)
	{
		case ONE_PULSE_MODE:CLR_BIT(timer->CR[0],3); break;
		case PERIODIC_MODE:	SET_BIT(timer->CR[0],3); break;
	}

	switch(GPT_ConfigPtr->Direction)
	{
		case UP_COUNT:	 CLR_BIT(timer->CR[0],4); break;
		case DOWN_COUNT: SET_BIT(timer->CR[0],4); break;
		default:		 CLR_BIT(timer->CR[0],4); break;
	}

	switch(GPT_ConfigPtr->Center_Aligned_Mode)
	{
		case EDGE_ALIGNED_MODE: timer->CR[0] &= ~(0x0060);	break;
		case CENTER_ALIGNED_MODE_1:	SET_BIT(timer->CR[0],5);
									CLR_BIT(timer->CR[0],6);
									break;
		case CENTER_ALIGNED_MODE_2:	CLR_BIT(timer->CR[0],5);
									SET_BIT(timer->CR[0],6);
									break;
		case CENTER_ALIGNED_MODE_3: timer->CR[0] |= (0x0060); break;
	}

	switch(GPT_ConfigPtr->AutoReloadBuffer)
	{
		case DISABLE: CLR_BIT(timer->CR[0],7);break;
		case ENABLE:  SET_BIT(timer->CR[0],7);	break;
	}

	switch(GPT_ConfigPtr->Clock_Div)
	{
		case DIV_1:	CLR_BIT(timer->CR[0],8);
					CLR_BIT(timer->CR[0],9);
					break;
		case DIV_2:	SET_BIT(timer->CR[0],8);
					CLR_BIT(timer->CR[0],9);
					break;
		case DIV_4:	CLR_BIT(timer->CR[0],8);
					SET_BIT(timer->CR[0],9);
					break;
	}

	switch(GPT_ConfigPtr->UDI_State)
	{
		case DISABLE:CLR_BIT(timer->DIER,0);break;
		case ENABLE: SET_BIT(timer->DIER,0); break;
	}
}

//Start Timer Function
void TIMER_voidStartTimer(u8 Copy_u8Timer)
{
	TIMER_t* timer = Get_timer(Copy_u8Timer);
	SET_BIT(timer->CR[1],0);		/* set counter enable bit to start the timer */
}

//Stop Timer Function
void TIMER_voidStopTimer(u8 Copy_u8Timer)
{
	TIMER_t* timer = Get_timer(Copy_u8Timer);
	CLR_BIT(timer->CR[1],0); /* clear counter enable bit to stop the timer */
}

//Delay Function
void TIMER_voidDelay(u8 Copy_u8Timer, u32 Copy_u32Delay, u32 Copy_u16Unit)
{
	TIMER_t* timer = Get_timer(Copy_u8Timer);
	u16 Local_u16Prescaler = 8-1;
	u32 Local_u32Counter;

	timer->PSC = Local_u16Prescaler;
	timer->ARR = Copy_u32Delay -1;

	for (Local_u32Counter=0; Local_u32Counter<Copy_u16Unit; Local_u32Counter++)
	{
		timer->CNT = 0;			//Clear the counter
		//Enable counter and One-pulse mode
		timer->CR[0] |= 0x9;
		//Wait until CEN bit is cleared
		while(timer->CR[0] & 1);
	}

	//Clear ARR register
	timer->ARR = 0;
	//Clear interrupt flag
	CLR_BIT(timer->SR,0);
}

//Get Count Function
u16 TIMER_u16GetCount(u8 Copy_u8Timer)
{
	TIMER_t* timer = Get_timer(Copy_u8Timer);
	return timer->CNT;
}

//Output Compare Function
void TIMER_voidOutputCompare(TIM_CH_t* PORT_PIN, u16 Copy_u16Period, u16 Copy_u16CompareValue, u16 Copy_u16Unit)
{
	TIMER_t* timer = Get_timer(PORT_PIN->timer);
	u8 Local_u8Channel = PORT_PIN->channel;

	/* Check whether channel is enabled */
	if ((timer->CCER & (1 << ((Local_u8Channel-1)*4)) ) == 0)
	{
		timer->PSC = (8*Copy_u16Unit-1);
		switch(Local_u8Channel)
		{	/* Set output to toggle on match */
			case CHANNEL1: timer->CCMR[0] |= 0x30;	break;
			case CHANNEL2: timer->CCMR[0] |= 0x3000;break;
			case CHANNEL3: timer->CCMR[1] |= 0x30;	break;
			case CHANNEL4: timer->CCMR[1] |= 0x3000;break;
		}

		/* Enable channel compare mode */
		timer->CCER |= (1 << ((Local_u8Channel-1)*4));
		if (PORT_PIN->timer == TIM1) timer->BDTR |= 0x8000;
	}

	timer->ARR = (Copy_u16Period-1);
	timer->CCR[Local_u8Channel-1] = Copy_u16CompareValue;
	timer->CNT = 0; 			//Clear counter
	timer->CR[0] = 1;			//Enable timer
}

//PWM Function
void TIMER_voidPWM(TIM_CH_t* PORT_PIN, u16 Copy_u16Period, u16 Copy_u16DutyCycle, u16 Copy_u16Unit)
{
	TIMER_t* tim = Get_timer(PORT_PIN->timer);
	u8 Local_u8Channel = PORT_PIN->channel;

	if ((tim->CCER & (1 << ((Local_u8Channel-1)*4)) ) == 0)
	{
		tim->PSC = (8*Copy_u16Unit-1);
		switch(Local_u8Channel)
		{
			case CHANNEL1: tim->CCMR[0] |= 0x60;  break;
			case CHANNEL2: tim->CCMR[0] |= 0x6000;break;
			case CHANNEL3: tim->CCMR[1] |= 0x60;  break;
			case CHANNEL4: tim->CCMR[1] |= 0x6000;break;
		}
		tim->CCER |= (1 << ((Local_u8Channel-1)*4));
		if (PORT_PIN->timer == TIM1) tim->BDTR |= 0x8000;
		tim->CR[0] |=1;
	}
	tim->ARR = (Copy_u16Period-1);
	tim->CCR[Local_u8Channel-1] = Copy_u16Period * Copy_u16DutyCycle;

}

//Getting Timer Channel
static TIM_CH_t* GET_TIM_CH(u8 Copy_u8PortPin)
{
	TIM_CH_t *TIM_CH;
	if(Port_Pin<4)
	{
		TIM_CH->timer = 1;
		TIM_CH->channel = Port_Pin+1;
	}
	else if(Port_Pin<8)
	{
		TIM_CH->timer = 2;
		TIM_CH->channel = Port_Pin-3;
	}
	else if(Port_Pin<12)
	{
		TIM_CH->timer = 3;
		TIM_CH->channel = Port_Pin-7;
	}

	return TIM_CH;
}

//Timer2 ISR
void TIM2_IRQHandler(void)
{
	TIMER_t* timer = Get_timer(TIM2);
	TIM2_CallBack();
	timer->SR = 0U; 		//Reset interrupt
}

//Timer3 ISR
void TIM3_IRQHandler(void) {
	TIMER_t *tim3 = Get_timer(TIM3);
	TIM3_CallBack();
    tim3->SR = 0U;
}

//Timer4 ISR
void TIM4_IRQHandler(void) {
	TIMER_t *tim4 = Get_timer(TIM4);
	TIM4_CallBack();
	tim4->SR = 0U;
}
