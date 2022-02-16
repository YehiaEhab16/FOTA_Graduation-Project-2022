# Functions for communication protocol
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
