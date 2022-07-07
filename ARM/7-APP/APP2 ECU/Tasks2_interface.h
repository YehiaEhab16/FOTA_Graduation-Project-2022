/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef TASKS_H_
#define TASKS_H_


#define TASK_REF_PRIORITY				0
#define TASK_REF_FIRST_DELAY			0
#define TASK_REF_PERIODICITY			5

/**
 * @def read temperature from sensor
 * State : Ready
 */
void Task_voidReadTemperature(void );



/**
 * @def check for malfunctions in system
 */
void Task_voidSystemCheck(void);


/**
 * @def send diagnostics data to Main ECU
 */ 
void Task_voidSendDiagnostics(void);

/**
 * @def rotate fan in case of temperature rise
 * State : suspended
 */
void Task_voidFanRotate(void );



#endif

