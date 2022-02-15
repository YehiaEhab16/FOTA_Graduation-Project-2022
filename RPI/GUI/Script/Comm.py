# Functions for communication protocol
import serial 
import threading
import time
# Receive Function
global data 
data = '1' 
global Serial_Port
class Read_thread (threading.Thread):
	def _init__(self):
		threading.Thread.__init__(self)


	def run (self):
		global Serial_Port
		Serial_Port = serial.Serial ("/dev/ttyS0") 
		Serial_Port.baudrate = 9600
		global data 
		while True :
			data = Serial_Port.read(1)
			#print (data)
			time.sleep(4)
			

def Stop_Read (Read_thread):
	global Serial_Port
	Serial_Port.close()
	Read_thread.kill()

def Start_Read (Read_thread):
	Read_thread.start()

def Read_Data():
	global data 
	return data
	
def Send(data):
	Serial_Port = serial.Serial ("/dev/ttyS0",9600)   
	Serial_Port.baudrate = 9600  
	Serial_Port.write(data)
	Serial_Port.close()

