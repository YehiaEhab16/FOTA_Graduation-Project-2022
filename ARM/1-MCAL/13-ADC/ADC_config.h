/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*You can choose frome 16 channel 0-15*/
#define SQ1				NOCHANNEL
#define SQ2				NOCHANNEL
#define SQ3				NOCHANNEL
#define SQ4				NOCHANNEL
#define SQ5				NOCHANNEL
#define SQ6				NOCHANNEL
#define SQ7				NOCHANNEL
#define SQ8				NOCHANNEL
#define SQ9				NOCHANNEL
#define SQ10			NOCHANNEL
#define SQ11			NOCHANNEL
#define SQ12			NOCHANNEL
#define SQ13			NOCHANNEL
#define SQ14			NOCHANNEL
#define SQ15			NOCHANNEL
#define SQ16			NOCHANNEL

/*Regular channel sequence length */
#define SQ_L               0




/*Conversion mode
-CONT
-Single
-DISCON
*/
#define ADC_CONV_MODE       CONT  


/*Alignment of data after conversion
-Left
-Right
*/
#define ADC_ALIG_STATE      Right
/*  JDR1;
	JDR2;
	JDR3;      
	jDR4;*/


#define ADC1_SQR1          ( (SQ13)|(SQ14<<5)|(SQ15<<10)|(SQ16<<15)|(SQ_L<<20))
#define ADC1_SQR2 		   ( (SQ7) |(SQ8<<5) |(SQ9<<10) |(SQ10<<15)|(SQ11<<20)|(SQ12<<25))     
#define ADC1_SQR3 		   ( (SQ1) |(SQ2<<5) |(SQ3<<10) |(SQ4<<15) |(SQ5<<20)|(SQ6<<25)  )
#define ADC1_SQR3 	       ( (SQ1) |(SQ2<<5) |(SQ3<<10) |(SQ4<<15) |(SQ5<<20)|(SQ6<<25)  )



#endif
