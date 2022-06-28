/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
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
	Task_voidCreateQueue();

	//Task Creation
	xTaskCreate((TaskFunction_t)Task_voidAlert, 	      "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate((TaskFunction_t)Task_voidReadDirection,   "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidReadTemperature, "Task3", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate((TaskFunction_t)Task_voidReadDistance,    "Task4", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)Task_voidMoveVehicle,     "Task6", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate((TaskFunction_t)Task_voidSystemCheck,     "Task5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate((TaskFunction_t)Task_voidSendDiagnostics, "Task8", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

	//Start Scheduler
	vTaskStartScheduler();

	while(1);
}
