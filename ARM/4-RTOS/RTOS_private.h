/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :RTOS			         ***********************/
/***********************   DATE : 19-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Preprocessor file guard */
#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_


struct RTOS_sTasks
{
	u32 RTOS_u32Periodicity;
	u32 RTOS_u32FirstDelay;
	void *RTOS_pvoid(void)=NULL;
	u8 RTOS_u8Priority;
	u8 RTOS_u8TaskState;
};

//RTOS Task States
#define RTOS_READY			0
#define RTOS_SUSPENDED		0


#define RTOS_NUM_TASKS	100

#define RTOS_TICKTIME	5
		
static void Scheduler(void);


#endif
