# Functions for communication protocol
import serial
import threading
import time

global Serial_Port
Serial_Port = None


def Comm_Init():
    global Serial_Port
    Serial_Port = serial.Serial("/dev/ttyS0", 9600)


def Comm_Read(lenght):
    global Serial_Port
    #Serial_Port = serial.Serial("/dev/ttyS0", 9600)
    data = Serial_Port.read(lenght)
    return data


def Comm_Write(data):
    global Serial_Port
    Serial_Port.write(data)
    

def Comm_Kill_Port():
    global Serial_Port
    Serial_Port.close()
