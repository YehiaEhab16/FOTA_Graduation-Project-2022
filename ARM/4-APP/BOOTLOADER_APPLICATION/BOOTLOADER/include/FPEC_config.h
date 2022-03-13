/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef FPEC_CONFIG_H_
#define FPEC_CONFIG_H_

/**
 * FPEC_START_PAGE_BOOT : First Page of the boot Loader Page address
 * FPEC_END_PAGE_BOOT   : Second Page of boot Loader  Page address
 */
#define FPEC_START_PAGE_BOOT		0x08000001
#define FPEC_END_PAGE_BOOT			0x08000000


/**
 *
 */
#define FPEC_START_NUM_PAGE_FLASH			4
#define FPEC_END_NUM_PAGE_FLASH				64


/**
 * maxium Page
 */
#define FPEC_MAX_NUM_PAGE			128


/**
 * FPEC_LATENCY : 1- FPEC_ZERO_STATE
 * 				  2- FPEC_ONE_STATE
 * 				  3- FPEC_TWO_STATE
 *
 *
 */
#define FPEC_LATENCY 		FPEC_ZERO_STATE







#endif
