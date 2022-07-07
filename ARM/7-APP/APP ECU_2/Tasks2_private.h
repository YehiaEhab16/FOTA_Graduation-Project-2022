/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATE : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TASKSPRIVATE_H_
#define TASKS_PRIVATE_H_


#define DIST_THRESHOLD			10
#define TEMP_THRESHOLD			30


typedef enum
{
	  Distance = 0 ,
	  Temperature  ,
	  RightMotorFB ,
	  LeftMotorFB  ,
	  Direction



}Tasks_Data;

#define READ_DISTANCE_ID		2
#define ALERT_ID				3


#define FORWARD					0
#define BACKWARD				1
#define STOP					2


#endif

