/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/

/***********************   Layer :App ECU Application   ***********************/
/***********************   DATA : 25/4/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Apps.h"


/*parameters for task creation where The formate will be like:
			TASK_t Copy_TaskName_tInfo{Periodicity, FirstDelay ,&FunctionWillBeExecuted ,Priority1 ,TaskState}
			The following is the information of the tasks where their types is defined in TASK_t

  



*/



TASK_t Copy_CollisionTASK_tInfo  	 = {1000, 1000 , &CollisionSystem ,1 ,RTOS_READY};
TASK_t Copy_TempSensorTASK_tInfo 	 = {1000, 1000 , &TempSensor      ,2 ,RTOS_READY};
TASK_t Copy_MotorsTASK_tInfo     	 = {1000, 1000 , &Motors          ,3 ,RTOS_READY};
TASK_t Copy_DiagTASK_tInfo       	 = {1000, 1000 , &Diagnostics     ,4 ,RTOS_READY};
TASK_t Copy_RecCanTASK_tInfo 		 = {1000, 1000 , &CAN_voidReceive ,5 ,RTOS_READY};
TASK_t Copy_TransmitCanTASK_tInfo 	 = {1000, 1000 , &CAN_u8Transmit  ,6 ,RTOS_READY};
TASK_t Copy_UpdateTASK_tInfo       	 = {1000, 1000 , &updateSystem    ,7 ,RTOS_READY};




int main(void)
{


	RTOS_u8CreateTask(& Copy_CollisionTASK_tInfo);
	RTOS_u8CreateTask(& Copy_TempSensorTASK_tInfo);
	RTOS_u8CreateTask(& Copy_MotorsTASK_tInfo);
	RTOS_u8CreateTask(& Copy_DiagTASK_tInfo);
	RTOS_u8CreateTask(& Copy_RecCanTASK_tInfo);
	RTOS_u8CreateTask(& Copy_TransmitCanTASK_tInfo);
	
	
	
	while(1){
	
	
	}


	return 0;
}