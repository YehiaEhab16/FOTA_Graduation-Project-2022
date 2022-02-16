# importing required packages
import ntpath
from PyQt5.QtWidgets import QWidget
from PyQt5.uic import loadUiType

import os
cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Calendar.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))


# Exit button
# def Handle_Exit():
#    sys.exit()


# GUI Functions
# Setting window title and size


# Define main window
class MainAPP_Calender (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Calender, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_Buttons()
        self.window()

    def window(self):
        self.setWindowTitle("Calendar")
        self.setFixedSize(800, 480)
    # GUI buttons

    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    def Handle_Exit(self):
        self.close()
