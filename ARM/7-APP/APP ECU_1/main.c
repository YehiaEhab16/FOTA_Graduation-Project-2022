/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/04-EXTI/EXTI_interface.h"
#include "../../3-SERVICE/02-SYS/SYS_interface.h"

#include "../../5-RTOS/RTOS_interface.h"

#include "ISR.h"
#include "Tasks.h"

int main(void)
{
	//Initialization
	SYS_voidApp1Init(EXTI_LINE3,&ISR_voidCANRecieve,&ISR_voidDCM);

/**
 * Task_voidReadDirection -- > Priority =0 , First Delay = 0 , State = Ready
 * Task_voidMoveVehicle   -- > Priority =1 , First Delay = 0 , State = Ready
 * Task_voidReadDistance  -- > Priority =2 , First Delay = 0 , State = Suspend
 * Task_voidAlert         -- > Priority =3 , First Delay = 0 , State = Suspend
 * Task_voidMotorFeedback -- > Priority =4 , First Delay = 0 , State = Ready
 * Task_voidSystemCheck   -- > Priority =5 , First Delay = 0 , State = Ready
 */
	//RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+1,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidMoveVehicle);

	//RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+2,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidReadDistance);

	//RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+3,TASK_REF_FIRST_DELAY,RTOS_SUSPENDED,&Task_voidAlert);

	//RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+3,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidMotorFeedback);

	//RTOS_u8CreateTask (TASK_REF_PRIORITY,TASK_REF_PERIODICITY+5,TASK_REF_FIRST_DELAY,RTOS_READY,&Task_voidSystemCheck);

while(1);



}
