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

#include "Tasks.h"

//Task Definition
TaskHandle_t Task1_Handler = NULL ;
TaskHandle_t Task2_Handler = NULL ;
TaskHandle_t Task3_Handler = NULL ;
TaskHandle_t Task4_Handler = NULL ;
TaskHandle_t Task5_Handler = NULL ;
TaskHandle_t Task6_Handler = NULL ;
TaskHandle_t Task7_Handler = NULL ;
TaskHandle_t Task8_Handler = NULL ;

int main(void)
{
	//Initialization
	SYS_voidInit();
	
	//Task Creation
	xTaskCreate((TaskFunction_t)Task_voidAlert, 	      "Task1", configMINIMAL_STACK_SIZE, NULL, 0, &Task1_Handler);
	xTaskCreate((TaskFunction_t)Task_u8ReadDirection, 	  "Task2", configMINIMAL_STACK_SIZE, NULL, 0, &Task2_Handler);
	xTaskCreate((TaskFunction_t)Task_u8ReadTemperature,   "Task3", configMINIMAL_STACK_SIZE, NULL, 0, &Task3_Handler);
	xTaskCreate((TaskFunction_t)Task_u8ReadDistance,      "Task4", configMINIMAL_STACK_SIZE, NULL, 0, &Task4_Handler);
	xTaskCreate((TaskFunction_t)Task_u8SystemCheck,       "Task5", configMINIMAL_STACK_SIZE, NULL, 0, &Task5_Handler);
	xTaskCreate((TaskFunction_t)Task_u8MoveVehicle,       "Task6", configMINIMAL_STACK_SIZE, NULL, 0, &Task6_Handler);
	xTaskCreate((TaskFunction_t)Task_u8RecieveRequest,    "Task7", configMINIMAL_STACK_SIZE, NULL, 0, &Task7_Handler);
	xTaskCreate((TaskFunction_t)Task_voidSendDiagnostics, "Task8", configMINIMAL_STACK_SIZE, NULL, 0, &Task8_Handler);
	
	//Start Scheduler
	vTaskStartScheduler();
	while(1)
	{
		
	}
}