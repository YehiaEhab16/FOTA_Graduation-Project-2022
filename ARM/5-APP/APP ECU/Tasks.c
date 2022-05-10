/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATA : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

#include "CAN_interface.h"
#include "BZR_interface.h"
#include "USN_interface.h"
#include "Tasks.h"


CAN_HandleTypeDef CAN_Handler;


u8 TempSensor (){
	
}


/*this function will 
					Operate the motors			
*/
u8 Motors (){
	
}

/*this function will 
					Operate the ultrasonic sensor
					Return a flag when the reading is over or below the normal values(no reading of garpage).
					Return a message if the value has suddenly changed by a large absolute differance (the current and the previous value).
					In the last case the fuction will operate a buzzer and flash.					
*/
u8 CollisionSystem (){
	u16 Distance=0;
	Distance = Ultrasonic_u32Calc();
	if (Distance < 10){
		/*Tack action*/
		/*EXAMPLE*/
		Buzzer_u8Signal();
	}
	

}

void send(){
	CAN_u8Transmit(&CAN_Handler);
}

void receive(){	
}


  


