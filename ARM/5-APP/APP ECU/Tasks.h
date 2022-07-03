/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TASKS_H_
#define TASKS_H_


#define FORWARD					0
#define BACKWARD				1
#define STOP					2

#define DIST_THRESHOLD			10
#define TEMP_THRESHOLD			30

#define QUEUE_SIZE				1
#define QUEUE_ITEM_SIZE			1
#define QUEUE_WRITE_TIME		10
#define QUEUE_READ_TIME			10

/**
 * @def Activate buzzer and LED for collision avoidance
 */

void Task_voidCreateQueue (void);

void Task_voidAlert(void * parms);

/**
 * @def read direction from 2 switches to indicate forward or backward motion
 */ 
void Task_voidReadDirection(void * parms);

/**
 * @def read temperature from sensor
 */ 
void Task_voidReadTemperature(void * parms);

/**
 * @def read distance from Ultrasonic sensor
 */
void Task_voidReadDistance(void * parms);

/**
 * @def check for malfunctions in system
 */
void Task_voidSystemCheck(void * parms);

/**
 * @def move vehicle forward or backward
 */ 
void Task_voidMoveVehicle(void * parms);

/**
 * @def rotate fan in case of temperature rise
 */ 
void Task_voidFanRotate(void * parms);

/**
 * @def send diagnostics data to Main ECU
 */ 
void Task_voidSendDiagnostics(void * parms);

/**
 * @def Get feedback from encoder
 */
void Task_voidMotorFeedback(void * parms);

#endif

