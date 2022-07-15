
# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget, QTableWidgetItem, QMessageBox
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.uic import loadUiType
import time
import requests
import os
from bluetooth import *
import Phone
from PyQt5 import QtCore
from subprocess import check_output
import RPi.GPIO as GPIO

threadDelay = 0.1

inputDiagTempVar = 0
inputDiagDirectionsVar = 0
inputDiagUltraVar = 0
updateInProgress = 0

outputUpdate = 8
outputDiag = 10
outputResponseFlag = 12

inputUpdate = 16
inputDiagTemp = 18
inputDiagDirections = 32
inputDiagUltra = 36
inputDiagFlag = 37

settingsIconFlagTwo = 0
settingsIconFlag = 0
updateCompletedFlag = 0
requestDiagMode = 2

redirectToggle = True
wifiToggle = False
bluetoothToggle = False

updateReceived = False
diagReceived = False

cwd = os.getcwd()
parent = os.path.dirname(cwd)

wifiNameArray = []
wifiEncryptionArray = []
wifiFrequencyArray = []
bluetoothArray = []
     
Link = parent+'/UI/Settings.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))

class MyThread(QThread):
    change_value = pyqtSignal(int)  # value to periodically update gui labels
    def run(self):
        cnt = 0
        while True:
            cnt += 1
            time.sleep(threadDelay)
            self.change_value.emit(cnt)

# Define main window
class MainAPP_Setting(QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Setting, self).__init__(parent)
        QTabWidget.__init__(self)
        global redirectToggle
        self.setupUi(self)
        self.window()
        redirectToggle = self.isActiveWindow()
        self.PhoneRedirect = Phone.MainAPP_Phone()
        self.Handle_Buttons()
        self.GPIO_Init()
        self.accessAPI()
        self.thread = MyThread()
        self.thread.change_value.connect(self.HandleCheck)
        self.thread.start()
        self.OP_2.hide()
        self.progressBar.hide()
        
    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.back_2.clicked.connect(self.Handle_Exit)
        self.back_3.clicked.connect(self.Handle_Exit)
        self.back_4.clicked.connect(self.Handle_Exit)
        self.UpdateCheck.clicked.connect(self.Handle_Update)
        self.CheckUp.clicked.connect(self.Handle_Diagnostics)
        self.Contact.clicked.connect(self.Handle_Send)
        self.Contact.clicked.connect(self.Handle_Phone)
        self.checkBox.clicked.connect(self.Handle_Toggle_Wifi)
        self.checkBox_2.clicked.connect(self.Handle_Toggle_Bluetooth)

    def GPIO_Init(self):
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BOARD)

        GPIO.setup(outputUpdate, GPIO.OUT, initial=GPIO.LOW)
        GPIO.setup(outputDiag, GPIO.OUT, initial=GPIO.LOW)
        GPIO.setup(outputResponseFlag, GPIO.OUT, initial=GPIO.LOW)

        GPIO.setup(inputUpdate, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        GPIO.setup(inputDiagTemp, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        GPIO.setup(inputDiagDirections, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        GPIO.setup(inputDiagUltra, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        GPIO.setup(inputDiagFlag, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        
        GPIO.add_event_detect(inputUpdate, GPIO.RISING, callback=self.Handle_Update_ISR, bouncetime = 300)
        GPIO.add_event_detect(inputDiagFlag, GPIO.RISING, callback=self.Handle_Diag_ISR, bouncetime = 300)


    def window(self):
        self.setWindowTitle("Settings")
        self.setFixedSize(800, 480)

    def accessAPI(self):
        versions = []
        versionsProperties = ["App_ECU","Updated_At", "File_Size"]
        versions = requests.get("https://fota-project-new-default-rtdb.firebaseio.com/factorySoftware/versions.json").json()
        versionsNumber = len(versions)
        self.UpdateHistory.setRowCount(versionsNumber)
        for row in range(versionsNumber):
            for column in range(3):
                self.UpdateHistory.setItem(row,column, QTableWidgetItem(str(versions[row].get(versionsProperties[column]))))
                if versionsProperties[column] == "App_ECU":
                    self.UpdateHistory.setItem(row,column, QTableWidgetItem("App_ECU_V_" +str(versions[row].get(versionsProperties[column]))))

    def Handle_Update(self):
            currentVersion = 2
            factoryVersion = requests.get("https://fota-project-new-default-rtdb.firebaseio.com/factorySoftware/latestVersion/App_ECU.json").json()
            if factoryVersion != currentVersion:
                ret = QMessageBox.information(self, 'New Update',
                                        'Please select whether you want to download the new update',
                                            QMessageBox.Ok | QMessageBox.Cancel)
                if ret == QMessageBox.Ok:
                    QMessageBox.information(self, "New update will be downloaded")

    def Handle_Send(self):
        pass
        
    def Handle_Toggle_Wifi(self):
        global wifiToggle
        global wifiNameArray
        global wifiEncryptionArray
        global wifiFrequencyArray
        wifiToggle = not wifiToggle
        if (wifiToggle == True):
            try:
                scanoutput = check_output(["sudo","iwlist", "wlan0", "scan"])
            except:
                try:
                    time.sleep(1)
                    scanoutput = check_output(["sudo","iwlist", "wlan0", "scan"])
                except:
                    time.sleep(3)
                    scanoutput = check_output(["sudo","iwlist", "wlan0", "scan"])
            # Getting and filtering the names of WiFi-s
            for line in scanoutput.split():
                line = line.decode('utf-8')
                if line.startswith("ESSID"):
                  filterLine =line.split(':')[1].replace('"','')
                  wifiNameArray.append(filterLine) 
            while ("" in wifiNameArray):
                wifiNameArray.remove("")
                
            # Getting and filtering the encryption types of WiFi-s	
            for line in scanoutput.split():
                line = line.decode('utf-8')
                if line.startswith("key"):
                    filterLine =line.split(':')[1].replace('"','')
                    if filterLine == 'on':
                        filterLine = 'Encrypted (WPS)'
                    else:
                        filterLine = 'None'
                    wifiEncryptionArray.append(filterLine)
            while ("" in wifiEncryptionArray):
                wifiEncryptionArray.remove("")
                
            #Getting and filtering the frequencies of WiFi-s
            for line in scanoutput.split():
                line = line.decode('utf-8')
                if line.startswith("Frequency"):
                  filterLine =line.split(':')[1].replace('"','')
                  wifiFrequencyArray.append(filterLine)    
            while ("" in wifiFrequencyArray):
                wifiFrequencyArray.remove("")
            wifiNameArrayLength = len(wifiNameArray)
            self.WiFi.setRowCount(wifiNameArrayLength)
            for row in range(wifiNameArrayLength):
                self.WiFi.setItem(row,0,QTableWidgetItem(str(wifiNameArray[row])))
                self.WiFi.setItem(row,1,QTableWidgetItem(str(wifiFrequencyArray[row]) + ' GHz'))
                self.WiFi.setItem(row,2,QTableWidgetItem(str(wifiEncryptionArray[row])))
        else:
            wifiNameArray = []
            wifiFrequencyArray = []
            wifiEncryptionArray = []
            self.WiFi.setRowCount(0)
                
    def Handle_Toggle_Bluetooth(self):
        global bluetoothArray
        global bluetoothToggle
        bluetoothToggle = not bluetoothToggle
        if bluetoothToggle == True:
            # Getting bluetooth available devices list
            nearbyDevices = discover_devices(lookup_names = True)
            for name, addr in nearbyDevices:
                bluetoothArray.append(addr)
            bluetoothArrayLength = len(bluetoothArray)
            self.Bluetooth.setRowCount(bluetoothArrayLength)
            for row in range(bluetoothArrayLength):
                self.Bluetooth.setItem(row,0,QTableWidgetItem(str(bluetoothArray[row])))
        else:
            bluetoothArray = []
            self.Bluetooth.setRowCount(0)

    def Handle_Phone(self):
        self.PhoneRedirect.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.PhoneRedirect.show()

    def Handle_Diagnostics(self):
        global requestDiagMode
        requestDiagMode = 1
        GPIO.output(outputDiag, GPIO.LOW)
        #time.sleep(0.1)
        GPIO.output(outputDiag, GPIO.HIGH) 

    def HandleCheck(self):
        global updateReceived
        global diagReceived
        global settingsIconFlag     
        global settingsIconFlagTwo 
        global inputDiagTempVar
        global inputDiagDirectionsVar
        global inputDiagUltraVar 
        global updateInProgress
        print(updateInProgress)
        self.progressBar.setValue(updateInProgress)
        localErrorFlag=0
        if(updateReceived == True):
            updateReceived = False
            global requestDiagMode
            settingsIconFlag = 1
            localErrorFlag=0
        if self.isActiveWindow() and settingsIconFlag:
            settingsIconFlag = 0
            self.setCurrentIndex(2)
            qMsgBoxUpdate = QMessageBox.information(self, 'New Update',
                        'Please select whether you want to download the new update',
                        QMessageBox.Ok | QMessageBox.Cancel)
            if qMsgBoxUpdate == QMessageBox.Ok:  
                self.OP_2.show()
                self.progressBar.show()
                GPIO.output(outputUpdate,GPIO.HIGH)
                self.Radiator.setText("alo")
                self.Engine.setText("No Errors Found hoba")
                self.Sensor.setText("No Errors Found")
                GPIO.output(outputResponseFlag, GPIO.LOW)
                GPIO.output(outputResponseFlag, GPIO.HIGH)                
            else:
                GPIO.output(outputUpdate, GPIO.LOW)
                GPIO.output(outputResponseFlag, GPIO.LOW)
                GPIO.output(outputResponseFlag, GPIO.HIGH)
        if updateInProgress == 100:
            updateInProgress = 0
            qMsgBoxUpdate = QMessageBox.information(self, 'New Update',
                'Update Complete',
                    QMessageBox.Ok)
            self.OP_2.hide()
            self.progressBar.setValue(0)
            self.progressBar.hide()

            


                   
        elif(diagReceived == True):
            diagReceived = False
            self.setCurrentIndex(3)
            inputDiagTempVar = GPIO.input(inputDiagTemp)
            inputDiagDirectionsVar = GPIO.input(inputDiagDirections)
            inputDiagUltraVar = GPIO.input(inputDiagUltra)
            if requestDiagMode == 1:
                if(inputDiagTempVar == 1):
                    self.Radiator.setText("Error occured")
                    localErrorFlag=1
                if(inputDiagDirectionsVar == 1):
                    self.Engine.setText("Error occured")
                    localErrorFlag=1
                if(inputDiagUltraVar == 1):
                    self.Sensor.setText("Error occured")
                    localErrorFlag=1
                if(localErrorFlag):
                    qMsgBoxSystemCheck = QMessageBox.information(self,"System Check",
                                    "System Check Returned with 1 or more error",
                                    QMessageBox.Ok)
                else:
                    qMsgBoxSystemCheck = QMessageBox.information(self,"System Check",
                                    "Performed System Check, No Errors Found",
                                    QMessageBox.Ok)
                localErrorFlag=0

                requestDiagMode = 2
                inputDiagTempVar = 0
                inputDiagDirectionsVar = 0
                inputDiagUltraVar = 0
            elif requestDiagMode == 2:
                settingsIconFlagTwo = 1
                print("alooooooo")
        if(self.isActiveWindow() and settingsIconFlagTwo):
            print("ana d5lt gowa el window")
            settingsIconFlagTwo = 0
            qMsgBoxSystemCheck = QMessageBox.information(self, 'System Check',
                        'System check is required',
                        QMessageBox.Ok)
            if qMsgBoxSystemCheck == QMessageBox.Ok:
                if(inputDiagTempVar == 1):
                    self.Radiator.setText("Error mn mode 2")
                if(inputDiagDirectionsVar == 1):
                    self.Engine.setText("Error mn mode 2")
                if(inputDiagUltraVar == 1):
                    self.Sensor.setText("Error mn mode 2")
                inputDiagTempVar = 0
                inputDiagDirectionsVar = 0
                inputDiagUltraVar = 0

    def Handle_Exit(self):
        self.close()
    @staticmethod
    def Handle_Update_ISR(channel):
        global updateReceived
        global updateInProgress
        inputUpdateState = GPIO.input(inputDiagTemp)
        inputUpdateFinish = GPIO.input(inputDiagDirections)
        if inputUpdateState == 0 and inputUpdateFinish == 0:
            updateReceived = True
        elif inputUpdateState == 1:
            updateInProgress += 10
        elif inputUpdateFinish == 1 and updateInProgress != 100: 
            updateInProgress = 100

    @staticmethod
    def Handle_Diag_ISR(channel):
        global diagReceived
        diagReceived = True
            


