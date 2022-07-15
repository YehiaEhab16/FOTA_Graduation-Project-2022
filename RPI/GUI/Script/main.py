# importing defined Modules
import time

import Calender
import Music
import Radio
import Guide
import Phone
import Settings
import Weather
import Video
import ntpath

import os

# importing required packages
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QTimer, Qt
from PyQt5 import QtGui, QtCore
from PyQt5.uic import loadUiType
import sys
import datetime
import pathlib

# Get current directory's path
current_directory = str(pathlib.Path(__file__).parent.absolute())

# Sets image of software update notification in settings
settingsNotificationPath = current_directory + \
    '/../Images/settingsNotification.png'
settingsIcon = current_directory + '/../Images/settingsLogo.png'

cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/MainWindow.ui'
Link1 = parent+'/UI/SplashScreen.ui'

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))
FormClass2, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link1))

VarGlobal = None

global counter
counter = 0

# Define splash screen window


class SplashScreen(QWidget, FormClass2):
    def __init__(self, parent=None):
        self.Window_Loop = MainAPP()

        global VarGlobal
        global thread1
        super(SplashScreen, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.counter = 0
        # creating a timer object
        self.timer2 = QTimer(self)
        # adding action to timer
        self.timer2.timeout.connect(self.loading)
        # update the timer every 15 ms
        self.timer2.start(15)
        self.Weather = Weather.MainAPP_Weather()
        VarGlobal = self.Weather

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Splash Screen")
        self.setFixedSize(800, 480)

    # Loading Screen Function
    def loading(self):
        self.counter = self.counter + 1
        if self.counter > 100:
            self.timer2.stop()
            time.sleep(1)
            # CLose load window and open main window
            self.close()
            # Comm_Init()
            self.Window_Loop.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
            self.Window_Loop.show()


def Handle_Weather():
    global VarGlobal
    VarGlobal.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
    VarGlobal.show()


# Define main window
class MainAPP(QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_Buttons()
        self.window()
        self.Calender = Calender.MainAPP_Calender()
        self.Music = Music.MainAPP_Music()
        self.Radio = Radio.MainAPP_Radio()
        self.Guide = Guide.MainAPP_Guide()
        self.Phone = Phone.MainAPP_Phone()
        self.Setting = Settings.MainAPP_Setting()
        self.Video = Video.MainAPP_Video()

        # creating a timer object
        timer = QTimer(self)
        # adding action to timer
        timer.timeout.connect(self.showTime)
        # update the timer every second
        timer.start()

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Main Window")
        #self.setFixedSize(800, 480)

    # GUI buttons
    def Handle_Buttons(self):
        self.calendar.clicked.connect(self.Handle_Calendar)
        self.music.clicked.connect(self.Handle_Music)
        self.weather.clicked.connect(Handle_Weather)
        self.radio.clicked.connect(self.Handle_Radio)
        self.video.clicked.connect(self.Handle_Video)
        self.guide.clicked.connect(self.Handle_Guide)
        self.settings.clicked.connect(self.Handle_Setting)
        self.phone.clicked.connect(self.Handle_Phone)

    # Calling other UIs when on clicking their buttons
    def Handle_Radio(self):
        self.Radio.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Radio.show()

    def Handle_Guide(self):
        self.Guide.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Guide.show()

    def Handle_Phone(self):
        self.Phone.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Phone.show()

    def Handle_Setting(self):
        self.settings.setIcon(QtGui.QIcon(settingsIcon))
        self.Setting.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        if Settings.settingsIconFlag == 1:
            self.Setting.setCurrentIndex(2)
        elif Settings.settingsIconFlagTwo == 1:
            self.Setting.setCurrentIndex(3)
        else:
            self.Setting.setCurrentIndex(0)
        self.Setting.show()

    def Handle_Video(self):
        self.Video.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Video.show()

    def Handle_Calendar(self):
        self.Calender.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Calender.show()

    def Handle_Music(self):
        self.Music.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
        self.Music.show()

    # Timer Function to update time label
    def showTime(self):
        global counter
        # getting current time
        currentTime = datetime.datetime.now()
        day = currentTime.strftime("%a")
        hour = currentTime.strftime("%I:%M %p")
        # showing it to the label
        self.time_label.setText(day + " " + hour)
        self.time_label.setAlignment(Qt.AlignCenter)
        counter = counter + 1
        # Condition to change settings to have a software update notification
        if (Settings.settingsIconFlag == 1 or Settings.settingsIconFlagTwo == 1):
            self.settings.setIcon(QtGui.QIcon(settingsNotificationPath))
        else:
            self.settings.setIcon(QtGui.QIcon(settingsIcon))


# Executing main window
def main():
    app = QApplication(sys.argv)
    splash = SplashScreen()
    splash.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
    splash.show()
    app.exec()


if __name__ == '__main__':
    main()


