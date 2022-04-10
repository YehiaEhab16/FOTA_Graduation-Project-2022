/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 23-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "STK_interface.h"

#include "RTOS_config.h"
#include "RTOS_interface.h"
#include "RTOS_private.h"

RTOS_t RTOS_sTasks[RTOS_NUM_TASKS] = {NULL};

/*Scheduler Functions*/
//Start Timer with specific tick time and Call Scheculer 
void RTOS_voidInit(void)
{
	STK_voidInit();
	STK_u8DelayAsyPeriodic(RTOS_TICKTIME, &Scheduler);
}
//Task Scheduling according to specific algorithm
static void Scheduler(void)
{
	u8 Local_u8Counter=0;
	for(Local_u8Counter=0;Local_u8Counter<RTOS_NUM_TASKS;Local_u8Counter++)
	{
		if(RTOS_sTasks[Local_u8Counter].RTOS_pvoid!=NULL && RTOS_sTasks[Local_u8Counter].RTOS_u8TaskState==RTOS_READY)
		{
			if(RTOS_sTasks[Local_u8Counter].RTOS_u16FirstDelay==0)
			{
				RTOS_sTasks[Local_u8Counter].RTOS_pvoid();
				RTOS_sTasks[Local_u8Counter].RTOS_u16FirstDelay = RTOS_sTasks[Local_u8Counter].RTOS_u16Periodicity - 1;
			}
			else
				RTOS_sTasks[Local_u8Counter].RTOS_u16FirstDelay--;
		}
	}
}

/*Tasks Handling Functions*/
//Crearte Task with specific parameters (ex:Priority, Periodicity, ...)
u8 RTOS_u8CreateTask(TASK_t* Copy_TASK_tInfo)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_TASK_tInfo->TASK_pvoid != NULL)
	{
		while(RTOS_sTasks[Copy_TASK_tInfo->TASK_u8Priority].RTOS_pvoid != NULL)
			Copy_TASK_tInfo->TASK_u8Priority++;
		
		RTOS_sTasks[Copy_TASK_tInfo->TASK_u8Priority].RTOS_u16Periodicity = Copy_TASK_tInfo->TASK_u16Periodicity;
		RTOS_sTasks[Copy_TASK_tInfo->TASK_u8Priority].RTOS_u16FirstDelay  = Copy_TASK_tInfo->TASK_u16FirstDelay;
		RTOS_sTasks[Copy_TASK_tInfo->TASK_u8Priority].RTOS_pvoid 		  = Copy_TASK_tInfo->TASK_pvoid;
		RTOS_sTasks[Copy_TASK_tInfo->TASK_u8Priority].RTOS_u8TaskState    = Copy_TASK_tInfo->TASK_u8TaskState;	
	}
	
	else
		Local_u8ErrorState=NOK;
	
	return Local_u8ErrorState;
}
//Set Task State as suspended
void RTOS_voidSuspendTask(u8 Copy_u8RTOSTaskNUM)
{
	RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_u8TaskState         = RTOS_SUSPENDED;
}
//Set Task State as resumed
void RTOS_voidResumeTask(u8 Copy_u8RTOSTaskNUM)
{
	RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_u8TaskState         = RTOS_READY;

}
//Completly delete task
void RTOS_voidDeleteTask(u8 Copy_u8RTOSTaskNUM)
{
		RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_u16Periodicity  = NULL;
		RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_u16FirstDelay	 = NULL;
		RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_pvoid 		     = NULL;
		RTOS_sTasks[Copy_u8RTOSTaskNUM].RTOS_u8TaskState     = NULL;
}
