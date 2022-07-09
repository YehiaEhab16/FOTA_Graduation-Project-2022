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
 * @def Activate buzzer and LED for collision avoidance
 * 		State : Ready --> Direction of Vehicle : BackWard
 */
void Task_voidAlert(void);

/**
 * @def read direction from 2 switches to indicate forward or backward motion
 * 		State : Ready --> Direction of Vehicle : BackWard
 */ 
void Task_voidReadDirection(void);

/**
 * @def read distance from Ultrasonic sensor
 */
void Task_voidReadDistance(void);

/**
 * @def check for malfunctions in system
 */
void Task_voidSystemCheck(void);

/**
 * @def move vehicle forward or backward
 */ 
void Task_voidMoveVehicle(void);

/**
 * @def send diagnostics data to Main ECU
 */ 
void Task_voidSendDiagnostics(void);

/**
 * @def Get feedback from encoder
 */
void Task_voidMotorFeedback(void);


#endif

