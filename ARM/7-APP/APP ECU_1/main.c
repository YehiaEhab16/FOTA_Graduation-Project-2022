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

#include "../../4-RTOS/RTOS_interface.h"



#include "../APP_ECU1/ISR.h"
#include "../APP_ECU1/Tasks_interface.h"
#include "../APP_ECU1/Tasks_private.h"

int main(void)
{
	//Initialization
 	SYS_voidAppInit(&Task_voidCANRecieveISR);

/**
 * Task_voidReadDirection -- > Priority =0 , First Delay = 0 , State = Ready
 * Task_voidMoveVehicle   -- > Priority =1 , First Delay = 0 , State = Ready
 * Task_voidReadDistance  -- > Priority =2 , First Delay = 0 , State = Suspend
 * Task_voidAlert         -- > Priority =3 , First Delay = 0 , State = Suspend
 * Task_voidMotorFeedback -- > Priority =4 , First Delay = 0 , State = Ready
 * Task_voidSystemCheck   -- > Priority =5 , First Delay = 0 , State = Ready
 */
	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidReadDirection);

	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+1,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidMoveVehicle);

	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+2,TASK_REF_FIRST_DELAY,RTOS_SUSPENDED,&Task_voidReadDistance);

	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+3,TASK_REF_FIRST_DELAY,RTOS_SUSPENDED,&Task_voidAlert);

	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+3,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidMotorFeedback);

	RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+5,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidSystemCheck);

while(1);



}
