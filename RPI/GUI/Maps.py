# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QTabWidget, QWidget
from PyQt5.QtCore import QTimer, QTime, Qt,QUrl
from PyQt5.uic import loadUiType
import sys
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent
import os
from PyQt5.QtGui import QPixmap
import sys
# importing defined modules

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI\Maps.ui"))


# Define main window
class MainAPP_Map (QWidget, FormClass):

    def __init__(self, parent=None):
        super(MainAPP_Map, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()

        # creating a timer object
        # timer = QTimer(self)
        # adding action to timer
        # timer.timeout.connect(self.showTime)
        # update the timer every second
        # timer.start()

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    def window(self):
        self.setWindowTitle("Map")
        self.setFixedSize(800, 480)

    def Handle_Exit(self):
        self.close()