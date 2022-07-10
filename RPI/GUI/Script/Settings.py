# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget, QTableWidgetItem, QMessageBox
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.uic import loadUiType
import time
import requests
import os
import RPi.GPIO as GPIO

outputUpdate = 8
outputDiag = 10
outputResponseFlag = 12

inputUpdate = 16
inputDiagTemp = 18
inputDiagDirections = 32
inputDiagUltra = 36
inputDiagFlag = 37

settingsIconFlag = 0
requestDiagMode = 2

cwd = os.getcwd()
parent = os.path.dirname(cwd)

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
            time.sleep(0.2)
            self.change_value.emit(cnt)

# Define main window
class MainAPP_Setting(QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Setting, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.GPIO_Init()
        self.accessAPI()
        self.thread = MyThread()
        self.thread.change_value.connect(self.HandleCheck)
        self.thread.start()

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.back_2.clicked.connect(self.Handle_Exit)
        self.back_3.clicked.connect(self.Handle_Exit)
        self.back_4.clicked.connect(self.Handle_Exit)
        self.UpdateCheck.clicked.connect(self.Handle_Update)
        self.CheckUp.clicked.connect(self.Handle_Diagnostics)
        self.Contact.clicked.connect(self.Handle_Send)

    def GPIO_Init(self):
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BOARD)

        GPIO.setup(outputUpdate, GPIO.OUT, initial=GPIO.HIGH)
        GPIO.setup(outputDiag, GPIO.OUT, initial=GPIO.HIGH)
        GPIO.setup(outputResponseFlag, GPIO.OUT, initial=GPIO.HIGH)

        GPIO.setup(inputUpdate, GPIO.IN)
        GPIO.setup(inputDiagTemp, GPIO.IN)
        GPIO.setup(inputDiagDirections, GPIO.IN)
        GPIO.setup(inputDiagUltra, GPIO.IN)
        GPIO.setup(inputDiagFlag, GPIO.IN)


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

    def Handle_Diagnostics(self):
        global requestDiagMode
        requestDiagMode = 1
        GPIO.output(outputDiag, GPIO.LOW)
        time.sleep(0.1)
        GPIO.output(outputDiag, GPIO.HIGH)
        

    def HandleCheck(self):
        inputUpdateVar = GPIO.input(inputUpdate)
        inputDiagTempVar = GPIO.input(inputDiagTemp)
        inputDiagDirectionsVar = GPIO.input(inputDiagDirections)
        inputDiagUltraVar = GPIO.input(inputDiagUltra)
        inputDiagFlagVar = GPIO.input(inputDiagFlag)
        
        if(inputUpdateVar == 0 or inputUpdateVar == False):
            global settingsIconFlag
            global requestDiagMode
            settingsIconFlag = 1
        if self.isActiveWindow() and settingsIconFlag:
            settingsIconFlag = 0
            qMsgBoxUpdate = QMessageBox.information(self, 'New Update',
                        'Please select whether you want to download the new update',
                        QMessageBox.Ok | QMessageBox.Cancel)
            if qMsgBoxUpdate == QMessageBox.Ok:
                GPIO.output(outputUpdate,GPIO.LOW)
                self.Radiator.setText("alo")
                self.Engine.setText("No Errors Found hoba")
                self.Sensor.setText("No Errors Found")
                

            else:
                GPIO.output(outputUpdate,GPIO.HIGH)
            GPIO.output(outputResponseFlag, GPIO.LOW)
                   
        elif(inputDiagFlagVar == 0 or inputDiagFlagVar == False):
            if requestDiagMode == 1:
                #fadl f flag = 1 ene a3ml el msgbox
                if(inputDiagTempVar == 0 or inputDiagTempVar == False):
                    self.Radiator.setText("Error occured")
                if(inputDiagDirectionsVar == 0 or inputDiagDirectionsVar == False):
                    self.Engine.setText("Error occured")
                if(inputDiagUltraVar == 0 or inputDiagUltraVar == False):
                    self.Sensor.setText("Error occured")

                requestDiagMode = 2
                inputDiagFlagVar = 1 or True
                inputDiagTempVar = 1 or True
                inputDiagDirectionsVar = 1 or True
                inputDiagUltraVar = 1 or True
            elif requestDiagMode == 2:
                if inputDiagFlagVar == 0 or inputDiagFlagVar == False:
                    qMsgBoxSystemCheck = QMessageBox.information(self, 'System Check',
                                'System check is required',
                                QMessageBox.Ok)
                    if qMsgBoxSystemCheck == QMessageBox.Ok:
                        if(inputDiagTempVar == 0 or inputDiagTempVar == False):
                            self.Radiator.setText("Error occured")
                        if(inputDiagDirectionsVar == 0 or inputDiagDirectionsVar == False):
                            self.Engine.setText("Error occured")
                        if(inputDiagUltraVar == 0 or inputDiagUltraVar == False):
                            self.Sensor.setText("Error occured")
                            inputDiagFlagVar = 1 or True
                            inputDiagTempVar = 1 or True
                            inputDiagDirectionsVar = 1 or True
                            inputDiagUltraVar = 1 or True
                        
                        else:
                            qMsgBoxSystemCheck = QMessageBox.information(self,"System Check",
                                "There are no errors in the system",
                                QMessageBox.Ok)

    def Handle_Exit(self):
        self.close()
