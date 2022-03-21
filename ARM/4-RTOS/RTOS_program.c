/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 19-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "STK_interface.h"

#include "RTOS_config.h"
#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_register.h"

struct RTOS_sTasks[RTOS_NUM_TASKS] = {NULL};

/*Scheduler Functions*/
//Start Timer with specific tick time and Call Scheculer 
void RTOS_voidStart(void)
{
	STK_voidInit();
	STK_u8DelayAsyPeriodic(RTOS_TICKTIME, &Scheduler);
}
//Task Scheduling according to specific algorithm
static void Scheduler(void)
{
	u8 Local_u8Counter=0;
	for(Local_u8Counter=0;Local_u8Counter<=RTOS_NUM_TASKS;Local_u8Counter++)
	{
		if(RTOS_sTasks[Local_u8Counter].RTOS_pvoid!=NULL && RTOS_sTasks[Local_u8Counter].RTOS_u8TaskState==RTOS_READY)
			RTOS_sTasks.RTOS_pvoid();
	}
}

/*Tasks Handling Functions*/
//Crearte Task with specific parameters (ex:Priority, Periodicity, ...)
void RTOS_voidCreateTask(void)
{
	
}
//Set Task State as suspended
void RTOS_voidSuspendTask(void)
{
	
}
//Set Task State as resumed
void RTOS_voidResumeTask(void)
{
	
}
//Completly delete task
void RTOS_voidDeleteTask(void)
{
	
}