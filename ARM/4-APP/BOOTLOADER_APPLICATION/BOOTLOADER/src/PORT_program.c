/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "PORT_config.h"
#include "PORT_private.h"

#include "PORT_register.h"


void PORT_voidInit()
{
	DDRA_CRL  = PORTA_DIR1;
	DDRA_CRH  = PORTA_DIR;
			  
	DDRB_CRL  = PORTB_DIR1;
	DDRB_CRH  = PORTB_DIR;
			   
	DDRC_CRH  = PORTC_DIR;
	
	PORTA	  = PORTA_VAlUE;
	PORTB	  = PORTB_VALUE;
	PORTC	  = PORTC_VALUE;

	
}
