/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

/*
Configuration for Bin
*/
#define PORT_INPUT_ANALOG_MODE         		0000
#define PORT_INPUT_FLOATING            		0100
#define PORT_INPUT_PULL_UP_DOWN        		1000
#define PORT_OUPUT_10MHZ_PUSH_PULL     		0001
#define PORT_OUPUT_10MHZ_OPEN_DRAIN    		0101
#define PORT_OUPUT_10MHZ_AF_PUSH_PULL  		1001
#define PORT_OUPUT_10MHZ_AF_OPEN_DRAIN 		1101
#define PORT_OUPUT_2MMHZ_PUSH_PULL     		0010
#define PORT_OUPUT_2MMHZ_OPEN_DRAIN    		0110
#define PORT_OUPUT_2MMHZ_AF_PUSH_PULL  		1010
#define PORT_OUPUT_2MMHZ_AF_OPEN_DRAIN 		1110
#define PORT_OUPUT_50MHZ_PUSH_PULL     		0011
#define PORT_OUPUT_50MHZ_OPEN_DRAIN    		0111
#define PORT_OUPUT_50MHZ_AF_PUSH_PULL  		1011
#define PORT_OUPUT_50MHZ_AF_OPEN_DRAIN 		1111



/*
*************************(Option1)*****************************************
Option1 Select : 1- PORT_INPUT_ANALOG_MODE
				 2- PORT_INPUT_FLOATING
				 3- PORT_INPUT_PULL_UP_DOWN

				 5- PORT_OUPUT_10MHZ_PUSH_PULL
				 6- PORT_OUPUT_10MHZ_OPEN_DRAIN
				 7- PORT_OUPUT_10MHZ_AF_PUSH_PULL
				 8- PORT_OUPUT_10MHZ_AF_OPEN_DRAIN

				 9- PORT_OUPUT_2MMHZ_PUSH_PULL
				 10-PORT_OUPUT_2MMHZ_OPEN_DRAIN
				 11-PORT_OUPUT_2MMHZ_AF_PUSH_PULL
				 12-PORT_OUPUT_2MMHZ_AF_OPEN_DRAIN

				 13-PORT_OUPUT_50MHZ_PUSH_PULL
				 14-PORT_OUPUT_50MHZ_OPEN_DRAIN
				 15-PORT_OUPUT_50MHZ_AF_PUSH_PULL
				 16-PORT_OUPUT_50MHZ_AF_OPEN_DRAIN


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
#define PORTA_PIN9_DIR                     PORT_OUPUT_10MHZ_AF_PUSH_PULL
#define PORTA_PIN10_DIR                    PORT_INPUT_PULL_UP_DOWN
#define PORTA_PIN11_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN12_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN13_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN14_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTA_PIN15_DIR                    PORT_OUPUT_2MMHZ_PUSH_PULL


#define PORTB_PIN0_DIR  		           PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN1_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN2_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN3_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN4_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN5_DIR                     PORT_OUPUT_2MMHZ_PUSH_PULL
#define PORTB_PIN6_DIR                     PORT_OUPUT_2MMHZ_AF_PUSH_PULL
#define PORTB_PIN7_DIR                     PORT_OUPUT_2MMHZ_AF_PUSH_PULL
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



#define PORTA_PIN0_INITIAL					1
#define PORTA_PIN1_INITIAL                  1
#define PORTA_PIN2_INITIAL                  1
#define PORTA_PIN3_INITIAL                  1
#define PORTA_PIN4_INITIAL                  1
#define PORTA_PIN5_INITIAL                  1
#define PORTA_PIN6_INITIAL                  1
#define PORTA_PIN7_INITIAL                  1
#define PORTA_PIN8_INITIAL                  1
#define PORTA_PIN9_INITIAL                  0
#define PORTA_PIN10_INITIAL                 1
#define PORTA_PIN11_INITIAL                 1
#define PORTA_PIN12_INITIAL                 1
#define PORTA_PIN13_INITIAL                 1
#define PORTA_PIN14_INITIAL                 1
#define PORTA_PIN15_INITIAL                 1
											
											
#define PORTB_PIN0_INITIAL                  1
#define PORTB_PIN1_INITIAL                  1
#define PORTB_PIN2_INITIAL                  1
#define PORTB_PIN3_INITIAL                  1
#define PORTB_PIN4_INITIAL                  1
#define PORTB_PIN5_INITIAL                  1
#define PORTB_PIN6_INITIAL                  1
#define PORTB_PIN7_INITIAL                  1
#define PORTB_PIN8_INITIAL                  1
#define PORTB_PIN9_INITIAL                  1
#define PORTB_PIN10_INITIAL                 1
#define PORTB_PIN11_INITIAL                 1
#define PORTB_PIN12_INITIAL                 1
#define PORTB_PIN13_INITIAL                 1
#define PORTB_PIN14_INITIAL                 1
#define PORTB_PIN15_INITIAL                 1
											
#define PORTC_PIN13_INITIAL                 1
#define PORTC_PIN14_INITIAL                 1
#define PORTC_PIN15_INITIAL                 1




















#endif
