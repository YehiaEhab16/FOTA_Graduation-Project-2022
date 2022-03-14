/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):LED 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */

void LED_voidLedOn(LED_t* Copy_pLED_tStructLed)
{
	if(Copy_pLED_tStructLed->LED_u8Connection == LED_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_HIGH);
	else
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_LOW);
}
void LED_voidLedOff(LED_t* Copy_pLED_tStructLed)
{
	if(Copy_pLED_tStructLed->LED_u8Connection == LED_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_LOW);
	else
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_HIGH);
}

void LED_voidLedToggle(LED_t* Copy_pLED_tStructLed)
{
	GPIO_u8TogglePinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin);
}