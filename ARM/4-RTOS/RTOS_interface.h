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

//Scheduler Functions
void RTOS_voidInit(void);

//Tasks Handling Functions
RTOS_u8CreateTask(u8 Copy_u8RTOSpriority ,u16 Copy_u16RTOSPeriodicity ,u16 Copy_u16RTOSFirstDelay ,u8 Copy_u8RTOSTaskState ,void (*Copy_voidRTOSpvoid)(void))
void RTOS_voidResumeTask (u8 Copy_u8RTOSTaskNUM);
void RTOS_voidSuspendTask(u8 Copy_u8RTOSTaskNUM);
void RTOS_voidDeleteTask (u8 Copy_u8RTOSTaskNUM);

#endif
