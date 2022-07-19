/****************************************************************/
/****************************************************************/
/***********************   YEHIA SHAHIN   ***********************/
/***********************   Layer :HAL    ************************/
/***********************   SWC (DRIVER):CLCD ********************/
/***********************   DATA : 5-1-2022 **********************/
/***********************   VERSION : 1.00   *********************/
/****************************************************************/
/****************************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

//choose the ports

#define CLCD_DATA_PORT 		GPIO_PORTA

#define CLCD_CTRL_PORT		GPIO_PORTB
#define CLCD_RS_PIN			GPIO_PIN_0
#define CLCD_RW_PIN			GPIO_PIN_1
#define CLCD_E_PIN			GPIO_PIN_5

/*Selectable the mode of the Lcd
 * OptionS :
 * 			1- 8_BIT  MODE:			MODE_8_BIT
 * 			2- 4_BIT  MODE:		    MODE_4_BIT*/

#define CLCD_MODE		MODE_4_BIT
// function set





#endif
