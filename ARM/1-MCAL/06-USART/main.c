#include





void ahmed (void)
{
	/*Pin A2 High			*/
	GPIO_voidSetPinValue(GPIOA , PIN2 , HIGH );
	/*Delay for 1 Sec		*/ 
	STK_voidSetBusyWait( 1000000 );
	
	/*Pin A2 Low			*/
	GPIO_voidSetPinValue(GPIOA , PIN2 , LOW );
	/*Delay for 1 Sec		*/ 
	STK_voidSetBusyWait( 1000000 );
	
}
void atia (void)
{
	/*Pin A2 High			*/
	GPIO_voidSetPinValue(GPIOA , PIN3 , HIGH );
	/*Delay for 1 Sec		*/ 
	STK_voidSetBusyWait( 1000000 );
	
	/*Pin A2 Low			*/
	GPIO_voidSetPinValue(GPIOA , PIN3 , LOW );
	/*Delay for 1 Sec		*/ 
	STK_voidSetBusyWait( 1000000 );
	
}

int main(void)
{
	/*RCC								*/
	RCC_voidInitSysClock(void);
	/*RCC AFIO							*/
	RCC_voidEnablePeripheralClock(APB2 , 0);
	
	RCC_voidEnablePeripheralClock(APB2 , GPIOA);
	EXTI_voidSetCallBack(ahmed);
	EXTI_voidSetCallBack(atia);
	
	/**		GPIO Direction	**/
	/*		A0 = input =====> PULL UP Resistor	*/
	GPIO_voidSetPinDirection(GPIOA , PIN0 , INPUT_PULLUP_DOWN);
	GPIO_voidSetPinValue(GPIOA , PIN0 ,HIGH );

	GPIO_voidSetPinDirection(GPIOA , PIN1 , INPUT_PULLUP_DOWN);
	GPIO_voidSetPinValue(GPIOA , PIN1 ,HIGH );
	/**	A2 ======> OUTPUT  SPEED 2MHZ PUSH PULL 	*/
	GPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_SPEED_2MHZ_PP);	
	GPIO_voidSetPinDirection(GPIOA , PIN3 , OUTPUT_SPEED_2MHZ_PP);	
		
	EXTI_voidInit();
	EXTI_voidSetSignalLatch(EXTI_LINE0 , FALLING_EDGE);
	EXTI_voidSetSignalLatch(EXTI_LINE1 , FALLING_EDGE);
		
	NVIC_voidSetPriority(6 , 2);
	NVIC_voidSetPriority(7 , 1);
	NVIC_voidEnableInterrupt(6);
	NVIC_voidEnableInterrupt(7);
	//NVIC_voidSetPendingFlag(6);
	
	while(1);
	
	return 0;
}












