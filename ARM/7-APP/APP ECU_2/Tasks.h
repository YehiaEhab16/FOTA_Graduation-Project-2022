/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef TASKS_H_
#define TASKS_H_


#define DIST_THRESHOLD					10
#define TEMP_THRESHOLD					30
		
#define READ_DISTANCE_ID				2
#define ALERT_ID						3
		
#define FORWARD							0
#define BACKWARD						1
#define STOP							2

#define TASK_REF_PRIORITY				0
#define TASK_REF_FIRST_DELAY			0
#define TASK_REF_PERIODICITY			5

typedef enum
{
	  Distance = 0 ,
	  Temperature  ,
	  RightMotorFB ,
	  LeftMotorFB  ,
	  Direction
}Tasks_Data;


typedef enum
{
	NonError =0 ,
	TempErrorMode1,
	TempErrorMode2

}Task_Error_Code;

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

