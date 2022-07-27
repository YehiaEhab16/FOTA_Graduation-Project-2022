# System Architecture

The embedded is the hardware system in which the software resides in the system. The embedded system can be considered as the microprocessor that can be used to perform some specific task.
The embedded system has basically three types of components:
-	**MCAL** (Microcontroller Abstraction Layer)
-   **HAL** (Hardware Abstraction Layer)
-   **Service Layer**
-   **RTOS** (Real Time Operating System)
-   **Application Layer**

<p  align="center">
<img  width="650"  src="/assets/Diagrams/System Architecture.drawio.png ">
</p>

## MCAL
MCAL is a software module that has direct access to all the on-chip MCU peripheral modules , In this project there are: 

- **RCC** (Reset and Clock Control)  : Control the clock that enters into peripheral. 

- **GPIO** (General Purpose Input Output):  Configure the Pins in MCU.

-  **NVIC** (Nested Vector Interrupt Control) : Configure the interrupt that is outside the processor  in MCU.

- **EXTI** (External Interrupt/event Controller ) :  Configure the external interrupt pins in MCU.

- **USART** (Universal Synchronous/Asynchronous Receiver/Transmitter)  : Access the USART communication protocol peripheral. 

- **CAN** (Controller Area Network) : Access the CAN communication protocol peripheral. 

- **STK** (System Ticks) : Access the internal timer in processor. 
 
- **FPEC** (Flash memory program/erase controller): Access the flash memory to write and erase the page on it. 

- **ADC** (Analog to digital converter) : Access the Analog to digital converter peripheral to read the data from analog sensor.

- **DMA** (Direct Memory Access) : Access the DMA peripheral to send data between peripheral and memory without interfering the MCU.



## HAL
HAL is a layer of programming that allows a computer OS to interact with a hardware device at a general or abstract level rather than at a detailed hardware level, In this project there are: 
- **LED**  : ON and OFF control on specific LED.  
- **DCM** : ON, OFF and Change the speed on the DC motor. 
- **BZR** :  ON and OFF control on Buzzer.
- **TMP** : Read from the Temperature Sensor.
- **USN** : Read from the Ultrasonic Sensor.
- **SW** : Configure the switches on specific pins and read its value. 
- **FAN** : ON, OFF and Change the speed on the FAN.
- **COM** : 
	- Customize communication protocol Like as the parallel communication protocol. 
	-  It is based on external interrupt.
	- It communicates between the user ECU and Raspberry pi by using pins that responsible about the update and diagnostic. 



## Service Layer 

The system service layer is the service interface that the OS provides to the application, In this project there are: 
- **Sys**(System) : Initialize Applications, USER, Main ECU and Bootloader. 
- **PARSING** : Filter the Hex file to extract the information that will be used in uploading the file in Application ECU. 

## RTOS
- RTOS is an operating system that is used in scheduling tasks by using priority based, and using the **FCFS** (First Come First Serve).
- The Functionality: 
	- Create  task.
	- Delete task. 
	- Change state of task.
	- scheduling between tasks. 
## Application Layer 

### Main ECU
- It used to control and facilitate communication between ECUs. 
- When the updated file is uploaded to the server, it receives the notification and sends it to User ECUs. 
- It receives the Approve and reject flag from User ECUs. 
- It sends the permission of update to application ECUs.
- It receives the diagnostics request from user and sends it to application to scan for diagnostics. 
- It receives the diagnostics data from application ECUs. 
- It sends any faults in the system that is in the user and sends it to server. 
### APP ECU 1
- Application one has 3 tasks:
	- It reads the temperature by using temperature sensor.
	- System check that has two modes:
		- Periodic mode: checks the reading of temperature that is within range in this mode, if there is an error send the status of the check, otherwise it does not send anything to user. 
		- User request mode: checks the reading of temperature that is within range in this mode, either there is an error or not, it sends fault to the user.
	- Executes action on the Fan when there is high reading of temperature and the OEM send update.  
### APP ECU 2
- Application one has 6 tasks:

	-  Read the direction of vehicle.
	- If the direction is backward (Enable parking checking mode, this mode checks the ultrasonic module) then alert and read distance tasks are resumed. 
	- When the vehicle moves backward, check the distance between it and any obstacle, if the distance is less than the threshold distance, the buzzer is switched ON.
	- Upon the direction of vehicle, Move vehicle task make decision movement of vehicle.
	- System check that has two modes:
		- Periodic mode: checks the reading of Ultrasonic sensor that is within range and  checks the reading of encoder of DCM in this mode, if there is an error send the status of the check, otherwise it does not send anything to user. 
		- User request mode: checks the reading of Ultrasonic sensor that is within range and checks the reading of encoder of DCM in this mode, either there is an error or not, it sends fault to the user.	 
### User Interface
User interface contain two Component : 
- Raspberry pi: its the user interface that receives any notification and sends any decision about any application.
- User ECU: this is gateway that used to convert the customize communication between raspberry pi and User ECU to the CAN communication protocol to send any message to main ECU

### Bootloader
The bootloader is the first code to run after power up or reset, and runs before any other software starts on a processor, including an operating system (OS). 
#### Memory Hierarchy
Design the flash Memory into three Partition :
- Bootloader: it contain two partition 
	-  Preload 
	- Bootloader code 
- Application 1: it is first version of application, any update has been occurred, it upload in this partition 
- Application 2 : it is the second version from the application 
- Flag request: it is states of MCU within and after update :
	-  No update
	- Update 
	- Data corruption 
<p  align="center">
<img  width="650"  src="/assets/Diagrams/Bootloader Addresses.png ">
</p>

#### Scenarios during update

##### Update complete
<p  align="center">
<img  width="650"  src="/assets/Diagrams/Bootloader Flow_Case1.png ">
</p>
##### Data corruption 
<p  align="center">
<img  width="650"  src="/assets/Diagrams/Bootloader Flow_Case2.png ">
</p>
##### Shutdown during update
<p  align="center">
<img  width="650"  src="/assets/Diagrams/Bootloader Flow_Case3.png ">
</p>

``