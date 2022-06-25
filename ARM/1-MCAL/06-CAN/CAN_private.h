/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define		RELEASE_FIFO 		((u32)1<<5)


//Registers Definitions
							/******1-CAN control and status registers*******/

//1-1- CAN master control register (CAN_MCR) -- Address offset: 0x00
#define		CAN_MCR_INRQ 		((u32)0x00000001)	//Initialization request 	  		-- The software clears this bit to switch the hardware into normal mode
#define     CAN_MCR_SLEEP       ((u32)0x00000002)	//Sleep mode request 		  		-- Sleep mode will be entered as soon as the current CAN activity (transmission or reception of a CAN frame) has been completed
#define     CAN_MCR_TXFP        ((u32)0x00000004)	//Transmit FIFO priority 	  		-- 0: Priority driven by the identifier of the message // 1: Priority driven by the request order (chronologically)
#define     CAN_MCR_RFLM        ((u32)0x00000008)	//Receive FIFO locked mode    		-- 0: Receive FIFO not locked on overrun // 1: Receive FIFO locked against overrun
#define     CAN_MCR_NART        ((u32)0x00000010)	//No automatic retransmission 		-- 0: Automatically retransmit until success // 1: A message will be transmitted only once
#define     CAN_MCR_AWUM        ((u32)0x00000020)	//Automatic wakeup mode 			-- 0: Sleep mode is left on software request by clearing the SLEEP bit // 1: Sleep mode is left automatically by hardware
#define     CAN_MCR_ABOM        ((u32)0x00000040)	//Automatic bus-off management		-- 0: The Bus-Off state is left on software request // 1: The Bus-Off state is left automatically by hardware
#define     CAN_MCR_TTCM        ((u32)0x00000080)	//Time triggered communication mode -- 0: Disabled // : Enabled
#define     CAN_MCR_DBF			((u32)0x00000080)	//Debug freeze						-- 0: CAN working during debug / 1: CAN reception/transmission frozen during debug
/*------------------------------------*/
//1-2- CAN master status register (CAN_MSR) -- Address offset: 0x04
#define		CAN_MSR_INAK		((u16)0x0001)	//Initialization acknowledge -- This bit is set by hardware and indicates to the software that the CAN hardware is now in initialization mode
#define     CAN_MSR_SLAK        ((u16)0x0002)	//Sleep acknowledge          -- This bit is set by hardware and indicates to the software that the CAN hardware is now in Sleep mode
#define     CAN_MSR_ERRI        ((u16)0x0004)	//Error interrupt
#define     CAN_MSR_WKUI        ((u16)0x0008)	//Wakeup interrupt
#define     CAN_MSR_SLAKI       ((u16)0x0010)	//Sleep acknowledge interrupt

/*------------------------------------*/
//1-3- CAN transmit status register (CAN_TSR) -- Address offset: 0x08
#define		CAN_TSR_RQCP0		((u32)0x00000001)	//Request completed mailbox0	 -- Set by hardware when the last request (transmit or abort) has been performed
#define     CAN_TSR_TXOK0       ((u32)0x00000002)	//Transmission OK of mailbox0	 -- The hardware updates this bit after each transmission attempt // 0: Tran. failed / 1: Tran. successful
#define     CAN_TSR_ALST0       ((u32)0x00000004)	//Arbitration lost for mailbox0	 -- This bit is set when the previous TX failed due to an arbitration lost
#define     CAN_TSR_TERR0       ((u32)0x00000008)	//Transmission error of mailbox0 -- This bit is set when the previous TX failed due to an error
#define     CAN_TSR_ABRQ0       ((u32)0x00000080)	//Abort request for mailbox0	 -- Set by software to abort the transmission request for the corresponding mailbox

#define     CAN_TSR_RQCP1		((u32)0x00000100)	//Request completed mailbox1
#define     CAN_TSR_TXOK1       ((u32)0x00000200)   //Transmission OK of mailbox1
#define     CAN_TSR_ALST1       ((u32)0x00000400)   //Arbitration lost for mailbox1
#define     CAN_TSR_TERR1       ((u32)0x00000800)   //Transmission error of mailbox01
#define     CAN_TSR_ABRQ1       ((u32)0x00008000)   //Abort request for mailbox1

#define     CAN_TSR_RQCP2		((u32)0x00010000)	//Request completed mailbox2
#define     CAN_TSR_TXOK2       ((u32)0x00020000)   //Transmission OK of mailbox2
#define     CAN_TSR_ALST2       ((u32)0x00040000)   //Arbitration lost for mailbox2
#define     CAN_TSR_TERR2       ((u32)0x00080000)   //Transmission error of mailbox2
#define     CAN_TSR_ABRQ2       ((u32)0x00800000)   //Abort request for mailbox2

#define     CAN_TSR_TME0		((u32)0x04000000)	//Transmit mailbox 0 empty	    -- This bit is set by hardware when no transmit request is pending for mailbox 0
#define     CAN_TSR_TME1        ((u32)0x08000000)	//Transmit mailbox 1 empty
#define     CAN_TSR_TME2        ((u32)0x10000000)	//Transmit mailbox 2 empty

/*------------------------------------*/
//1-4- CAN receive FIFO register (CAN_RF0R/CAN_RF1R)
#define		CAN_FIFO_FMP		((u32)0x03)			//FIFO 0 message pending		-- These bits indicate how many messages are pending in the receive FIFO.
#define     CAN_FIFO_FULL		((u8)0x08)			//FIFO 0 full					-- Set by hardware when three messages are stored in the FIFO.
#define     CAN_FIFO_FOVR		((u8)0x10)			//FIFO 0 overrun				-- This bit is set by hardware when a new message has been received and passed the filter while the FIFO was full.
#define     CAN_FIFO_RFOM		((u8)0x20)			//Release FIFO 0 output mailbox -- Set by software to release the output mailbox of the FIFO.


/*------------------------------------*/
//1-5- CAN interrupt enable register (CAN_IER) -- Address offset: 0x14
#define		CAN_IER_TMEIE		((u32)0x00000001)	//Transmit mailbox empty interrupt enable -- 0: No interrupt when RQCPx bit is set // 1: Interrupt generated when RQCPx bit is set
#define		CAN_IER_FMPIE0		((u32)0x00000002)	//FIFO message pending interrupt enable	  -- 0: No interrupt generated when state of FMP[1:0] bits are not 00b // 1: Interrupt generated when state of FMP[1:0] bits are not 00b.
#define     CAN_IER_FFIE0		((u32)0x00000004)	//FIFO full interrupt enable			  -- 0: No interrupt when FULL bit is set // 1: Interrupt generated when FULL bit is set
#define     CAN_IER_FOVIE0		((u32)0x00000008)	//FIFO overrun interrupt enable	  		  -- 0: No interrupt when FOVR bit is set // 1: Interrupt generated when FOVR bit is set.
#define		CAN_IER_FMPIE1		((u32)0x00000010)	//FIFO message pending interrupt enable
#define     CAN_IER_FFIE1		((u32)0x00000020)	//FIFO full interrupt enable
#define     CAN_IER_FOVIE1		((u32)0x00000040)	//FIFO overrun interrupt enable
#define     CAN_IER_LECIE		((u32)0x00000800)	//Last error code interrupt enable		  -- 0: ERRI bit will not be set when the error code in LEC[2:0] is set by hardware on error detection // 1: ERRI bit will be set
#define		CAN_IER_ERRIE		((u32)0x00008000)	//Error interrupt enable			   	  -- 0: No interrupt will be generated when an error condition is pending in the CAN_ESR // 1: An interrupt will be generated
#define     CAN_IER_WKUIE		((u32)0x00010000)	//Wakeup interrupt enable			      -- 0: No interrupt when WKUI is set // 1: Interrupt generated when WKUI bit is set
#define     CAN_IER_SLKIE		((u32)0x00020000)	//Sleep interrupt enable				  -- 0: No interrupt when SLAKI bit is set // 1: Interrupt generated when SLAKI bit is set

/*------------------------------------*/
//1-6- CAN error status register (CAN_ESR) -- Address offset: 0x18
#define		CAN_ESR_LEC		    ((u32)0x00000070)	//Last error code 000: No Error // 001: Stuff Error // 010: Form Error // 011: Acknowledgment Error // 100: Bit recessive Error // 101: Bit dominant Error // 110: CRC Error // 111: Set by software
#define     CAN_ESR_TEC		    ((u32)0x00FF0000)	//Least significant byte of the 9-bit transmit error counter -- The implementing part of the fault confinement mechanism of the CAN protocol.
#define     CAN_ESR_REC		    ((u32)0xFF000000)	//Receive error counter

/*------------------------------------*/
//1-7- CAN bit timing register (CAN_BTR) -- Address offset: 0x1C
#define		CAN_BTR_BRP		   ((u32)0x000003FF)	//Baud rate prescaler				   	  -- define the length of a time quanta.
#define     CAN_BTR_TS1		   ((u32)0x000F0000)	//Least significant 				   	  -- define the number of time quanta in Time Segment 1.
#define     CAN_BTR_TS2		   ((u32)0x00700000)	//Receive error count				   	  -- define the number of time quanta in Time Segment 2.
#define     CAN_BTR_SJW		   ((u32)0x03000000)	//Resynchronization jump width		   	  -- define the maximum number of time quanta the CAN hardware is allowed to lengthen or shorten
#define  	CAN_BTR_LBKM       ((u32)0x40000000)	//Loop back mode (debug)			   	  -- 0: Loop Back Mode disabled / 1: Loop Back Mode enabled
#define  	CAN_BTR_SILM       ((u32)0x80000000)	//Silent mode (debug)				   	  -- 0: Normal operation / 1: Silent Mode


							/******2-CAN mailbox registers*******/

//2-1- CAN TX mailbox identifier register (CAN_TIxR) -- Address offset: 0x180, 0x190, 0x1A0
#define  	CAN_TI0R_TXRQ      ((u32)0x00000001)   // Transmit Mailbox Request 					  -- Set by software to request the transmission for the corresponding mailbox / Cleared by hardware when the mailbox becomes empty.
#define  	CAN_TI0R_RTR       ((u32)0x00000002)   // Remote Transmission Request 				  -- Remote transmission request /0: Data frame / 1: Remote frame
#define  	CAN_TI0R_IDE       ((u32)0x00000004)   // Identifier Extension 						  -- defines the identifier type of message in the mailbox. /0: Standard identifier. / 1: Extended identifier.
#define  	CAN_TI0R_EXID      ((u32)0x001FFFF8)   // Extended Identifier 						  -- The LSBs of the extended identifier.
#define  	CAN_TI0R_STID      ((u32)0xFFE00000)   // Standard Identifier or Extended Identifier  -- The standard identifier or the MSBs of the extended identifier (depending on the IDE bit value)

/*------------------------------------*/
//2-2- CAN mailbox data length control and time stamp register (CAN_TDTxR) -- Address offset: 0x184, 0x194, 0x1A4
#define     TDT0R_DLC      ((u32)0x0000000F)   // Data Length Code 						-- defines the number of data bytes a data frame contains or a remote frame request.
#define     TDT0R_TGT      ((u32)0x00000100)   // Transmit Global Time					-- 0: Time stamp TIME[15:0] is not sent. / 1: Time stamp TIME[15:0] value is sent in the last two data bytes
#define     TDT0R_TIME     ((u32)0xFFFF0000)   // Message Time Stamp 					-- contains the 16-bit timer value captured at the SOF transmission.

/*------------------------------------*/
//2-3- CAN mailbox data low register (CAN_TDLxR) -- Address offset: 0x188, 0x198, 0x1A8
#define     TDL0R_DATA0    ((u32)0x000000FF)        // Data byte 0
#define     TDL0R_DATA1    ((u32)0x0000FF00)        // Data byte 1
#define     TDL0R_DATA2    ((u32)0x00FF0000)        // Data byte 2
#define     TDL0R_DATA3    ((u32)0xFF000000)        // Data byte 3

/*------------------------------------*/
//2-4- CAN mailbox data high register (CAN_TDHxR) -- Address offset: 0x18C, 0x19C, 0x1AC
#define     TDH0R_DATA4    ((u32)0x000000FF)        // Data byte 4
#define     TDH0R_DATA5    ((u32)0x0000FF00)        // Data byte 5
#define     TDH0R_DATA6    ((u32)0x00FF0000)        // Data byte 6
#define     TDH0R_DATA7    ((u32)0xFF000000)        // Data byte 7

/*------------------------------------*/
//2-5- CAN receive FIFO mailbox identifier register (CAN_RIxR) -- Address offset: 0x18C, 0x19C, 0x1AC
#define  	RIR_RTR       ((u32)0x00000002)        // Remote Transmission Request					-- 0: Data frame / 1: Remote frame
#define  	RIR_IDE       ((u32)0x00000004)        // Identifier Extension 						-- This bit defines the identifier type of message in the mailbox. / 0: Standard identifier. / 1: Extended identifier.
#define  	RIR_EXID      ((u32)0x001FFFF8)        // Extended identifier 							-- The LSBs of the extended identifier.
#define  	RIR_STID      ((u32)0xFFE00000)        // Standard Identifier or Extended Identifier	-- The standard identifier or the MSBs of the extended identifier

/*------------------------------------*/
//2-6- CAN receive FIFO mailbox data length control and time stamp register(CAN_RDTxR) -- Address offset: 0x1B4, 0x1C4
#define  	RDT1R_DLC      ((u32)0x0000000F)        // Data Length Code 							-- defines the number of data bytes a data frame contains (0 to 8).
#define  	RDT1R_FMI      ((u32)0x0000FF00)        // Filter Match Index 							-- contains the index of the filter the message stored in the mailbox passed through.
#define  	RDT1R_TIME     ((u32)0xFFFF0000)        // Message Time Stamp 							-- This field contains the 16-bit timer value captured at the SOF detection

/*------------------------------------*/
//2-7- CAN receive FIFO mailbox data low register (CAN_RDLxR) -- Address offset: 0x1B8, 0x1C8
#define  	RDL1R_DATA0    ((u32)0x000000FF)        // Data byte 0
#define  	RDL1R_DATA1    ((u32)0x0000FF00)        // Data byte 1
#define  	RDL1R_DATA2    ((u32)0x00FF0000)        // Data byte 2
#define  	RDL1R_DATA3    ((u32)0xFF000000)        // Data byte 3

/*------------------------------------*/
//2-8- CAN receive FIFO mailbox data high register (CAN_RDHxR) -- Address offset: 0x1BC, 0x1CC
#define  	RDH1R_DATA4    ((u32)0x000000FF)        // Data byte 4
#define  	RDH1R_DATA5    ((u32)0x0000FF00)        // Data byte 5
#define  	RDH1R_DATA6    ((u32)0x00FF0000)        // Data byte 6
#define  	RDH1R_DATA7    ((u32)0xFF000000)        // Data byte 7




							/******3-CAN filter registers*******/
//3-1- CAN filter master register (CAN_FMR) -- Address offset: 0x200
#define     FMR_CAN2SB	   ((u32)0x00003F00)		//CAN2 start bank        -- These bits are set and cleared by software. They define the start bank for the CAN2 interface (Slave) in the range 0 to 27.
#define     FMR_FINIT      ((u32)0x00000001)        //Filter init mode       -- Initialization mode for filter banks  / 0: Active filters mode. / 1: Initialization mode for the filters.

/*------------------------------------*/
//CAN filter mode register (CAN_FM1R) -- Address offset: 0x204
#define		FM1R_FBMx	   ((u32)0x0FFFFFFF)		//Filter mode            -- 0: Two 32-bit registers of filter bank x are in Identifier Mask mode. / 1: Two 32-bit registers of filter bank x are in Identifier List mode.

/*------------------------------------*/
//CAN filter scale register (CAN_FS1R) -- Address offset: 0x20C
#define		FS1R_FSCx  	   ((u32)0x00FFFFFFF)	   //Filter scale configuration     -- These bits define the scale configuration of Filters 13-0. /0: Dual 16-bit scale configuration / 1: Single 32-bit scale configuration

/*------------------------------------*/
//CAN filter FIFO assignment register (CAN_FFA1R) -- Address offset: 0x214
#define		FFA1R_FFAx	   ((u32)0x00FFFFFFF)  	   //Filter FIFO assignment for filter x  -- The message passing through this filter will be stored in the specified FIFO. /0: Filter assigned to FIFO 0 / 1: Filter assigned to FIFO 1

/*------------------------------------*/
//CAN filter activation register (CAN_FA1R) -- Address offset: 0x21C
#define		FA1R_FACTx	   ((u32)0x00FFFFFFF)	  //Filter active		-- The software sets this bit to activate Filter x. To modify the Filter x registers (CAN_FxR[0:7]), the FACTx bit must be cleared or the FINIT bit of the CAN_FMR register must be set. /0: Filter x is not active - 1: Filter x is active

/*------------------------------------*/
//Filter bank i register x (CAN_FiRx) -- Address offset: 0x240..0x31C
#define		FiRx_FB 	   ((u32)0xFFFFFFFFF)	  //Filter bits    -- identifier -0: Dominant bit is expected / 1: Recessive bit is expected / Mask - 0: Don�t care, the bit is not used for the comparison 1: Must match,

/*!< CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/
#define  CAN_FMR_FINIT                       ((u8)0x01)               /*!< Filter Init Mode */


#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))


#endif
