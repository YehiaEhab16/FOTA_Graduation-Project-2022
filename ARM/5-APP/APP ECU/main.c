/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATA : 10/5/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "SYS_interface"

#include "../OS/org/Source/include/FreeRTOS.h"
#include "../OS/org/Source/include/task.h"
#include "../OS/org/Source/include/queue.h"

#include "Tasks.h"

//Create Queues
xQueueHandle Global_xQueueHandleDistance=0;
xQueueHandle Global_xQueueHandleDirection=0;
xQueueHandle Global_xQueueHandleTemperature=0;
xQueueHandle Global_xQueueMainRequest=0;

int main(void)
{
	//Initialization
	SYSAPP_voidInit();
	
	//Create Queues
	Global_xQueueHandleDistance =    xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueHandleDirection =   xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueHandleTemperature = xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	Global_xQueueMainRequest =		 xQueueCreate(QUEUE_SIZE, QUEUE_ITEM_SIZE);
	
	//Task Creation
	xTaskCreate(Task_voidAlert, 	      "Task1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(Task_voidReadDirection,   "Task2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Task_voidReadTemperature, "Task3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(Task_voidReadDistance,    "Task4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(Task_voidSystemCheck,     "Task5", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(Task_voidMoveVehicle,     "Task6", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Task_voidRecieveRequest,  "Task7", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(Task_voidSendDiagnostics, "Task8", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	
	//Start Scheduler
	vTaskStartScheduler();
	while(1)
	{
		
	}
}