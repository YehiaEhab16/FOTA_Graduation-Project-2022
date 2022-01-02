# importing required packages
import ntpath
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QTabWidget, QMessageBox
from PyQt5.uic import loadUiType
import time

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/Phone.ui"))

# Initialing list for names and numbers
names = []
nums = []


# Define main window
class MainAPP_Phone(QTabWidget, FormClass):
    def __init__(self, parent=None):
        global names
        global nums
        super(MainAPP_Phone, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        with open('Contacts.txt', 'r') as f:
            for line in f:
                f_contents = line.split(' - ')
                names.append(f_contents[0])
                nums.append(f_contents[1][:-1])
        self.loadData()

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.back_2.clicked.connect(self.Handle_Exit)
        self.back_3.clicked.connect(self.Handle_Exit)
        self.Contacts_table.cellClicked.connect(self.Contacts_Call)
        self.Recents_table.cellClicked.connect(self.Recent_Call)

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Phone")
        self.setFixedSize(800, 480)

    # Function to load data in contacts tab
    def loadData(self):
        global names
        global nums
        self.Contacts_table.setRowCount(len(names))
        row = 0
        for i in range(0, len(names)):
            self.Contacts_table.setItem(row, 0, QtWidgets.QTableWidgetItem(names[i]))
            self.Contacts_table.setItem(row, 1, QtWidgets.QTableWidgetItem(nums[i]))
            row = row + 1

    # Function to call when contact is pressed
    def Contacts_Call(self, row):
        QTabWidget.setCurrentIndex(self, 0)
        self.OP.setText("Calling")
        self.name.setText(names[row])
        ret = QMessageBox.warning(self, 'Call Failed',
                                  'Please Connect Your Mobile Phone',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            self.Contacts_Call(row)
        elif ret == QMessageBox.Ok:
            self.OP.setText("")
            self.name.setText("")

    # Function to call when contact is pressed
    def Recent_Call(self):
        pass

    # Exit Button
    def Handle_Exit(self):
        self.close()
