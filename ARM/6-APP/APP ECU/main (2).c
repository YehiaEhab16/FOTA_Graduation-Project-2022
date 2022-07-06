/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../7-Library/STD_TYPES.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../3-SERVICE/02-SYS/SYS_interface.h"

#include "../../4-FreeRTOS/OS/org/Source/include/FreeRTOS.h"
#include "../../4-FreeRTOS/OS/org/Source/include/task.h"

#include "ISR.h"
#include "Tasks.h"

int main(void)
{
	//Initialization
	SYS_voidAppInit(&Task_voidCANRecieveISR);
	//Task_voidCreateQueue();

	extern TaskHandle_t Global_TaskHandle_tAlert, Global_TaskHandle_tDist;
	//, Global_TaskHandle_tSend;

	//Task Creation
	xTaskCreate((TaskFunction_t)Task_voidAlert, 	      "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &Global_TaskHandle_tAlert);
	xTaskCreate((TaskFunction_t)Task_voidReadDirection,   "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidReadTemperature, "Task3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidReadDistance,    "Task4", configMINIMAL_STACK_SIZE, NULL, 1, &Global_TaskHandle_tDist);
	xTaskCreate((TaskFunction_t)Task_voidMoveVehicle,     "Task5", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate((TaskFunction_t)Task_voidMotorFeedback,   "Task6", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidFanRotate, 	  "Task7", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidSystemCheck,     "Task8", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	//xTaskCreate((TaskFunction_t)Task_voidSendDiagnostics, "Task9", configMINIMAL_STACK_SIZE, NULL, 1, &Global_TaskHandle_tSend);

	//Task Suspending
	vTaskSuspend(Global_TaskHandle_tAlert);
	vTaskSuspend(Global_TaskHandle_tDist);
//	vTaskSuspend(Global_TaskHandle_tSend);

	//Start Scheduler
	vTaskStartScheduler();

	while(1);
}
