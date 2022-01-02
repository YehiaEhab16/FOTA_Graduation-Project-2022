# importing defined Modules
import Comm
import Calender
import Music
import Radio
import Maps
import Phone
import Settings
import Weather
import Video
import ntpath

# importing required packages
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QTimer, Qt
from PyQt5 import QtGui
from PyQt5.uic import loadUiType
import sys
import datetime
import pathlib

# Get current directory's path
current_directory = str(pathlib.Path(__file__).parent.absolute())

# Sets image of software update notification in settings
settingsNotificationPath = current_directory + '/Images/settingsNotification.png'
settingsIcon = current_directory + '/Images/settingsLogo.png'

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/MainWindow.ui"))


# Exit button
def Handle_Exit():
    sys.exit()


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
        self.Maps = Maps.MainAPP_Map()
        self.Phone = Phone.MainAPP_Phone()
        self.Setting = Settings.MainAPP_Setting()
        self.Weather = Weather.MainAPP_Weather()
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
        self.setFixedSize(800, 480)

    # GUI buttons
    def Handle_Buttons(self):
        self.calendar.clicked.connect(self.Handle_Calendar)
        self.music.clicked.connect(self.Handle_Music)
        self.weather.clicked.connect(self.Handle_Weather)
        self.radio.clicked.connect(self.Handle_Radio)
        self.video.clicked.connect(self.Handle_Video)
        self.maps.clicked.connect(self.Handle_Maps)
        self.settings.clicked.connect(self.Handle_Setting)
        self.phone.clicked.connect(self.Handle_Phone)
        self.exit.clicked.connect(Handle_Exit)

    # Calling other UIs when on clicking their buttons
    def Handle_Radio(self):
        self.Radio.show()

    def Handle_Maps(self):
        self.Maps.show()

    def Handle_Phone(self):
        self.Phone.show()

    def Handle_Setting(self):
        self.Setting.show()

    def Handle_Video(self):
        self.Video.show()

    def Handle_Weather(self):
        self.Weather.show()

    def Handle_Calendar(self):
        self.Calender.show()

    def Handle_Music(self):
        self.Music.show()

    # Timer Function to update time label
    def showTime(self):
        # getting current time
        currentTime = datetime.datetime.now()
        day = currentTime.strftime("%a")
        hour = currentTime.strftime("%I:%M %p")
        # showing it to the label
        self.time_label.setText(day + " " + hour)
        self.time_label.setAlignment(Qt.AlignCenter)
        # Condition to change settings to have a software update notification
        if Comm.Get() == 1:
            # Sets the image of notification to replace the default settings image
            self.settings.setIcon(QtGui.QIcon(settingsNotificationPath))
        else:  # Condition must be added (If user views the software update)
            self.settings.setIcon(QtGui.QIcon(settingsIcon))


# Executing main window
def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
