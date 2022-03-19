/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 19-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Preprocessor file guard */
#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

//Scheduler Functions
void RTOS_voidStart(void);

//Tasks Handling Functions
void RTOS_voidCreateTask(void);
void RTOS_voidResumeTask(void);
void RTOS_voidSuspendTask(void);
void RTOS_voidDeleteTask(void);

#endif
