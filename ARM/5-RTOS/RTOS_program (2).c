/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 23-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../7-Library/STD_TYPES.h"

#include "../1-MCAL/07-STK/STK_interface.h"

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
u8 RTOS_u8CreateTask(u8 Copy_u8RTOSpriority ,u16 Copy_u16RTOSPeriodicity ,u16 Copy_u16RTOSFirstDelay ,u8 Copy_u8RTOSTaskState ,void (*Copy_voidRTOSpvoid)(void))
{
	u8 Local_u8ErrorState = OK;
	if(Copy_voidRTOSpvoid != NULL)
	{
		while(RTOS_sTasks[Copy_u8RTOSpriority].RTOS_pvoid != NULL)
			Copy_u8RTOSpriority++;
		
		RTOS_sTasks[Copy_u8RTOSpriority].RTOS_u16Periodicity = Copy_u16RTOSPeriodicity;
		RTOS_sTasks[Copy_u8RTOSpriority].RTOS_u16FirstDelay	 = Copy_u16RTOSFirstDelay;
		RTOS_sTasks[Copy_u8RTOSpriority].RTOS_pvoid 		 = Copy_voidRTOSpvoid;
		RTOS_sTasks[Copy_u8RTOSpriority].RTOS_u8TaskState    = Copy_u8RTOSTaskState;
		
		if ((RTOS_sTasks[Copy_u8RTOSpriority].RTOS_u8TaskState) == RTOS_SUSPENDED)
			 RTOS_voidSuspendTask(Copy_u8RTOSpriority);
		
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
