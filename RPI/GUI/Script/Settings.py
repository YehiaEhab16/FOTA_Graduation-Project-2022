# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget, QTableWidgetItem, QMessageBox
from PyQt5.uic import loadUiType
import Comm
import requests
import os

cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Settings.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))


# Define main window
class MainAPP_Setting(QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Setting, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.accessAPI()

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.back_2.clicked.connect(self.Handle_Exit)
        self.back_3.clicked.connect(self.Handle_Exit)
        self.back_4.clicked.connect(self.Handle_Exit)
        self.UpdateCheck.clicked.connect(self.Handle_Update)
        self.CheckUp.clicked.connect(self.Handle_Diagnostics)
        self.Contact.clicked.connect(self.Handle_Send)

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
        pass

    def Handle_Exit(self):
        self.close()
