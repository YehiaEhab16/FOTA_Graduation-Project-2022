/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 23-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Preprocessor file guard */
#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_


typedef struct
{
	u16 RTOS_u16Periodicity;
	u16 RTOS_u16FirstDelay;
	void (*RTOS_pvoid)(void);
	u8 RTOS_u8Priority;
	u8 RTOS_u8TaskState;
}RTOS_t;





//RTOS Task States
#define RTOS_READY			0
#define RTOS_SUSPENDED		1


#define RTOS_NUM_TASKS	100

#define RTOS_TICKTIME	1
		
static void Scheduler(void);


#endif
