/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../3-SERVICE/02-SYS/SYS_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../5-RTOS/RTOS_interface.h"

#include "ISR.h"
#include "Tasks.h"

LED_t LED1 = {LED_PORTB,LED_PIN0,LED_ACTIVE_HIGH};

int main(void)
{
	//Initialization
	SYS_voidApp1Init(&Task_voidCANRecieveISR);

/**
 * Task_voidReadTemperature -- > Priority =0 , First Delay = 0 , State = Ready
 * Task_voidMoveVehicle   -- > Priority =1 , First Delay = 0 , State = Ready
 * Task_voidSystemCheck  -- > Priority =2 , First Delay = 0 , State = Suspend
**/
	RTOS_u8CreateTask (TASK_REF_PRIORITY+1,TASK_REF_PERIODICITY+1,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidReadTemperature);
	RTOS_u8CreateTask (TASK_REF_PRIORITY+2,TASK_REF_PERIODICITY+5,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidSystemCheck);
	RTOS_u8CreateTask (TASK_REF_PRIORITY+3,TASK_REF_PERIODICITY,TASK_REF_FIRST_DELAY,RTOS_SUSPENDED,&Task_voidFanRotate);


	LED_voidLedOn(&LED1);
	
	while(1);

}
