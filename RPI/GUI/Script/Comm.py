# Functions for communication protocol
<<<<<<< HEAD
#import serial 
import threading
import time
# Receive Function
global data 
data = '1' 
class Read_thread (threading.Thread):
	def _init__(self):
		threading.Thread.__init__(self)


	def run (self):
		pass
			



def Stop_Read (Read_thread):
	return 0

def Start_Read (Read_thread):
	return 0

def Read_Data():
	return 0
	
def Send(data):
	return 0
=======
import serial
import threading
import time

global Serial_Port
Serial_Port = None


def Comm_Init():
    global Serial_Port
    Serial_Port = serial.Serial("/dev/ttyS0", 9600)


def Comm_Read(size):
    data = 0
    global Serial_Port
    Input_Buff = 0
    if Input_Buff != 0:
        data = Serial_Port.read(size)
    else:
        data = 0
    return data


def Comm_Write(data):
    global Serial_Port
    Serial_Port.write(data)


def Comm_Kill_Port():
    global Serial_Port
    Serial_Port.close()
>>>>>>> ff62ba942b992b58f0baf1c8c82d19b289974242
