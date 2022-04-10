/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 23-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Preprocessor file guard */
#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

typedef struct
{
	u16 TASK_u16Periodicity;
	u16 TASK_u16FirstDelay;
	void (*TASK_pvoid)(void);
	u8 TASK_u8Priority;
	u8 TASK_u8TaskState;
}TASK_t;

//Scheduler Functions
/**
 * @def   Initialize RTOS
 */
void RTOS_voidInit(void);

//Tasks Handling Functions
/**
 * @def   Create Task
 * @param Copy_TASK_tInfo: Task Info
 */
RTOS_u8CreateTask(TASK_t* Copy_TASK_tInfo);

/**
 * @def   Resume Task
 * @param Copy_u8RTOSTaskNUM: Task Id
 */
void RTOS_voidResumeTask (u8 Copy_u8RTOSTaskNUM);

/**
 * @def   Suspend Task
 * @param Copy_u8RTOSTaskNUM: Task Id
 */
void RTOS_voidSuspendTask(u8 Copy_u8RTOSTaskNUM);

/**
 * @def   Delete Task
 * @param Copy_u8RTOSTaskNUM: Task Id
 */
void RTOS_voidDeleteTask (u8 Copy_u8RTOSTaskNUM);


#endif
