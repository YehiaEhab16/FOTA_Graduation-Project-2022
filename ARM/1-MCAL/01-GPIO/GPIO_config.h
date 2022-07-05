/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):GPIO 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_


/*
Options for Pins:
	-PORT_INPUT_ANALOG_MODE        
	-PORT_INPUT_FLOATING           
	-PORT_INPUT_PULL_UP_DOWN       
	-PORT_OUPUT_10MHZ_PUSH_PULL    
	-PORT_OUPUT_10MHZ_OPEN_DRAIN   
	-PORT_OUPUT_10MHZ_AF_PUSH_PULL 
	-PORT_OUPUT_10MHZ_AF_OPEN_DRAIN
	-PORT_OUPUT_2MMHZ_PUSH_PULL    
	-PORT_OUPUT_2MMHZ_OPEN_DRAIN   
	-PORT_OUPUT_2MMHZ_AF_PUSH_PULL 
	-PORT_OUPUT_2MMHZ_AF_OPEN_DRAIN
	-PORT_OUPUT_50MHZ_PUSH_PULL    
	-PORT_OUPUT_50MHZ_OPEN_DRAIN   
	-PORT_OUPUT_50MHZ_AF_PUSH_PULL 
	-PORT_OUPUT_50MHZ_AF_OPEN_DRAIN
*/

#define PORTA_PIN0_DIR  		           PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN1_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN2_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN3_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN4_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN5_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN6_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN7_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN8_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN9_DIR                     PORT_OUPUT_50MHZ_AF_PUSH_PULL
#define PORTA_PIN10_DIR                    PORT_INPUT_FLOATING
#define PORTA_PIN11_DIR                    PORT_INPUT_FLOATING
#define PORTA_PIN12_DIR                    PORT_OUPUT_50MHZ_AF_PUSH_PULL
#define PORTA_PIN13_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN14_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN15_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL

#define PORTB_PIN0_DIR  		           PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN1_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN2_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN3_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN4_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN5_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN6_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN7_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN8_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN9_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN10_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN11_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN12_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN13_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN14_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN15_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL

#define PORTC_PIN13_DIR  		           PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTC_PIN14_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTC_PIN15_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL

/*
*********************************option*********************************************
Option Select : 1- (1) 				: HIGH Level
				2- (0)  			: LOW  Level
*/
#define PORTA_PIN0_INITIAL					0
#define PORTA_PIN1_INITIAL                  0
#define PORTA_PIN2_INITIAL                  0
#define PORTA_PIN3_INITIAL                  0
#define PORTA_PIN4_INITIAL                  0
#define PORTA_PIN5_INITIAL                  0
#define PORTA_PIN6_INITIAL                  0
#define PORTA_PIN7_INITIAL                  0
#define PORTA_PIN8_INITIAL                  0
#define PORTA_PIN9_INITIAL                  0
#define PORTA_PIN10_INITIAL                 0
#define PORTA_PIN11_INITIAL                 0
#define PORTA_PIN12_INITIAL                 0
#define PORTA_PIN13_INITIAL                 0
#define PORTA_PIN14_INITIAL                 0
#define PORTA_PIN15_INITIAL                 0

#define PORTB_PIN0_INITIAL                  0
#define PORTB_PIN1_INITIAL                  0
#define PORTB_PIN2_INITIAL                  0
#define PORTB_PIN3_INITIAL                  0
#define PORTB_PIN4_INITIAL                  0
#define PORTB_PIN5_INITIAL                  0
#define PORTB_PIN6_INITIAL                  0
#define PORTB_PIN7_INITIAL                  0
#define PORTB_PIN8_INITIAL                  0
#define PORTB_PIN9_INITIAL                  0
#define PORTB_PIN10_INITIAL                 0
#define PORTB_PIN11_INITIAL                 0
#define PORTB_PIN12_INITIAL                 0
#define PORTB_PIN13_INITIAL                 0
#define PORTB_PIN14_INITIAL                 0
#define PORTB_PIN15_INITIAL                 0

#define PORTC_PIN13_INITIAL                 0
#define PORTC_PIN14_INITIAL                 0
#define PORTC_PIN15_INITIAL                 0


#endif
