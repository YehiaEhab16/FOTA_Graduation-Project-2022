# importing required packages
import ntpath
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QTabWidget, QMessageBox
from PyQt5.uic import loadUiType
import pathlib
import datetime
import os
import Settings

# Get current directory's path
current_directory = str(pathlib.Path(__file__).parent.absolute())
cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Phone.ui'

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))

# Initialing list for names and numbers
names = []
nums = []
Contents = []
NumberOfContents = 0

ValueLcd = ""


# Define main window
class MainAPP_Phone(QTabWidget, FormClass):

    def __init__(self, parent=None):
        global names
        global nums
        global NumberOfContents
        super(MainAPP_Phone, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        with open(current_directory + '/../Data/Contacts.txt', 'r') as f:
            global Contents
            global ValueLcd
            if Settings.redirectToggle == True:
                for line in f:
                    f_contents = line.split(' - ')
                    Contents.append(f_contents)
                    names.append(f_contents[0])
                    nums.append(f_contents[1][:-1])
                    NumberOfContents = NumberOfContents + 1
                    self.loadData()
            else:
                ValueLcd = "911"
                self.number.setText(ValueLcd)
                self.loadData()

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.back_2.clicked.connect(self.Handle_Exit)
        self.back_3.clicked.connect(self.Handle_Exit)
        self.Contacts_table.cellClicked.connect(self.Contacts_Call)
        self.Recents_table.cellClicked.connect(self.Recent_Call)
        self.Num_1.clicked.connect(self.Button_1)
        self.Num_2.clicked.connect(self.Button_2)
        self.Num_3.clicked.connect(self.Button_3)
        self.Num_4.clicked.connect(self.Button_4)
        self.Num_5.clicked.connect(self.Button_5)
        self.Num_6.clicked.connect(self.Button_6)
        self.Num_7.clicked.connect(self.Button_7)
        self.Num_8.clicked.connect(self.Button_8)
        self.Num_9.clicked.connect(self.Button_9)
        self.Num_0.clicked.connect(self.Button_0)
        self.Num_s.clicked.connect(self.Button_A)
        self.Num_h.clicked.connect(self.Button_H)
        self.erase.clicked.connect(self.Handle_Erase)
        self.dial.clicked.connect(self.Handle_Call)

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Phone")

    # Function to load data in contacts tab
    def loadData(self):
        global names
        global nums
        self.Contacts_table.setRowCount(len(names))
        row = 0
        for i in range(0, len(names)):
            self.Contacts_table.setItem(
                 row, 0, QtWidgets.QTableWidgetItem(names[i]))
            self.Contacts_table.setItem(
                row, 1, QtWidgets.QTableWidgetItem(nums[i]))
            row = row + 1

    # Keypad Buttons
    def Button_0(self):
        global ValueLcd
        ValueLcd = ValueLcd + "0"
        self.number.setText(ValueLcd)

    def Button_1(self):
        global ValueLcd
        ValueLcd = ValueLcd + "1"
        self.number.setText(ValueLcd)

    def Button_2(self):
        global ValueLcd
        ValueLcd = ValueLcd + "2"
        self.number.setText(ValueLcd)

    def Button_3(self):
        global ValueLcd
        ValueLcd = ValueLcd + "3"
        self.number.setText(ValueLcd)

    def Button_4(self):
        global ValueLcd
        ValueLcd = ValueLcd + "4"
        self.number.setText(ValueLcd)

    def Button_5(self):
        global ValueLcd
        ValueLcd = ValueLcd + "5"
        self.number.setText(ValueLcd)

    def Button_6(self):
        global ValueLcd
        ValueLcd = ValueLcd + "6"
        self.number.setText(ValueLcd)

    def Button_7(self):
        global ValueLcd
        ValueLcd = ValueLcd + "7"
        self.number.setText(ValueLcd)

    def Button_8(self):
        global ValueLcd
        ValueLcd = ValueLcd + "8"
        self.number.setText(ValueLcd)

    def Button_9(self):
        global ValueLcd
        ValueLcd = ValueLcd + "9"
        self.number.setText(ValueLcd)

    def Button_A(self):
        global ValueLcd
        ValueLcd = ValueLcd + "*"
        self.number.setText(ValueLcd)

    def Button_H(self):
        global ValueLcd
        ValueLcd = ValueLcd + "#"
        self.number.setText(ValueLcd)

    def Handle_Erase(self):
        global ValueLcd
        AccVal = ""
        for counter in range(0, len(ValueLcd) - 1):
            AccVal = AccVal + ValueLcd[counter]

        ValueLcd = AccVal
        self.number.setText(ValueLcd)

    # Dial Function
    def Handle_Call(self):
        global NumberOfContents
        global Contents
        global ValueLcd
        # Check for invalid inputs
        if ((len(ValueLcd) == 11) and (ValueLcd[:3] == "012" or ValueLcd[:3] == "011"
                                       or ValueLcd[:3] == "015" or ValueLcd[:3] == "010")) \
                or ((len(ValueLcd) == 9) and (ValueLcd[:2] == "03")):
            PersonName = ""
            for counter in range(0, NumberOfContents):
                if ValueLcd == Contents[counter][1][:-1]:
                    PersonName = Contents[counter][0]

            if PersonName == "":
                self.name.setText("Unknown")
            else:
                self.name.setText(PersonName)
            self.OP.setText('Calling')
            # Add number in recent tab
            self.Recents_table.insertRow(0)
            if PersonName == "":
                self.Recents_table.setItem(
                    0, 0, QtWidgets.QTableWidgetItem('Unknown'))
            else:
                self.Recents_table.setItem(
                    0, 0, QtWidgets.QTableWidgetItem(PersonName))
            self.Recents_table.setItem(
                0, 1, QtWidgets.QTableWidgetItem(ValueLcd))
            # Get Current Day
            t_day = str(datetime.date.today()).split('-')
            t_day = t_day[2] + '/' + t_day[1]
            self.Recents_table.setItem(
                0, 2, QtWidgets.QTableWidgetItem(t_day))
            # Error message (mobile not connected)
            ret = QMessageBox.warning(self, 'Call Failed',
                                      'Please Connect Your Mobile Phone',
                                      QMessageBox.Retry | QMessageBox.Ok)
            if ret == QMessageBox.Retry:
                self.Handle_Call()
            elif ret == QMessageBox.Ok:
                ValueLcd = ""
                self.number.setText("")
                self.name.setText("")
                self.OP.setText("")
        else:
            ret = QMessageBox.warning(self, 'Call Failed',
                                      'Please make sure you dial a valid phone number',
                                      QMessageBox.Retry | QMessageBox.Ok)
            if ret == QMessageBox.Retry:
                self.Handle_Call()

    # Function to call when contact is pressed
    def Contacts_Call(self, row):
        QTabWidget.setCurrentIndex(self, 0)
        self.OP.setText("Calling")
        self.name.setText(names[row])
        # Add number in recent tab
        self.Recents_table.insertRow(0)
        self.Recents_table.setItem(
            0, 0, QtWidgets.QTableWidgetItem(names[row]))
        self.Recents_table.setItem(
            0, 1, QtWidgets.QTableWidgetItem(nums[row]))
        # Get Current Day
        t_day = str(datetime.date.today()).split('-')
        t_day = t_day[2] + '/' + t_day[1]
        self.Recents_table.setItem(
            0, 2, QtWidgets.QTableWidgetItem(t_day))
        ret = QMessageBox.warning(self, 'Call Failed',
                                  'Please Connect Your Mobile Phone',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            self.Contacts_Call(row)
        elif ret == QMessageBox.Ok:
            self.number.setText("")
            self.name.setText("")
            self.OP.setText("")

    # Function to call when recent number is pressed
    def Recent_Call(self, row):
        QTabWidget.setCurrentIndex(self, 0)
        self.OP.setText("Calling")
        self.name.setText(self.Recents_table.item(row, 0).text())
        # Add number in recent tab
        self.Recents_table.insertRow(0)
        self.Recents_table.setItem(
            0, 0, QtWidgets.QTableWidgetItem(self.Recents_table.item(row+1, 0).text()))
        self.Recents_table.setItem(
            0, 1, QtWidgets.QTableWidgetItem(self.Recents_table.item(row+1, 1).text()))
        # Get Current Day
        t_day = str(datetime.date.today()).split('-')
        t_day = t_day[2] + '/' + t_day[1]
        self.Recents_table.setItem(
            0, 2, QtWidgets.QTableWidgetItem(t_day))
        ret = QMessageBox.warning(self, 'Call Failed',
                                  'Please Connect Your Mobile Phone',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            self.Recent_Call(row)
        elif ret == QMessageBox.Ok:
            self.number.setText("")
            self.name.setText("")
            self.OP.setText("")

    # Exit Button
    def Handle_Exit(self):
        self.close()
