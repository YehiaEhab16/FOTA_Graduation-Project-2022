/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/

#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H


				/*INITIAL TYPE DEFINITIONS*/

#define PRESCALER	//Specifies the length of a time quantum.
/* Options:			must be a number between Min_Data = 1 and Max_Data = 1024*/

#define MODE		//Specifies the CAN operating mode.
/* Options:			MODE_NORMAL
					MODE_LOOPBACK
					MODE_SILENT
					MODE_SILENT_LOOPBACK*/
					
#define SJW			//Specifies the maximum number of time quanta 
/* Options:			SJW_1TQ
					SJW_2TQ
					SJW_3TQ
					SJW_4TQ*/
					
#define BS1			//pecifies the number of time quanta in Bit Segment 1
/* Options:			BS1_1TQ
					BS1_2TQ
					BS1_3TQ
					BS1_4TQ
					BS1_5TQ
					BS1_6TQ
					BS1_7TQ
					BS1_8TQ
					BS1_9TQ
					BS1_10TQ
					BS1_11TQ
					BS1_12TQ
					BS1_13TQ
					BS1_14TQ
					BS1_15TQ
					BS1_16TQ*/
					
#define BS2			//Specifies the number of time quanta in Bit Segment 2
/* Options:			BS2_1TQ
					BS2_2TQ
					BS2_3TQ
					BS2_4TQ
					BS2_5TQ
					BS2_6TQ
					BS2_7TQ
					BS2_8TQ*/
					
#define TTCM		//Enable or disable the time triggered communication mode
/* Options:			ENABLED
					DISABLED*/
					
#define ABOM		//Enable or disable the automatic bus-off management
/* Options:			ENABLED
					DISABLED*/
					
#define AWUM		//Enable or disable the automatic wake-up mode
/* Options:			ENABLED
					DISABLED*/
					
#define NART		//Enable or disable the non-automatic retransmission mode
/* Options:			ENABLED
					DISABLED*/
					
#define RFLM		//Enable or disable the Receive FIFO Locked mode
/* Options:			ENABLED
					DISABLED*/
					
#define TXFP		//Enable or disable the transmit FIFO priority.
/* Options:			ENABLED
					DISABLED*/

/***************************************************************************/





#endif