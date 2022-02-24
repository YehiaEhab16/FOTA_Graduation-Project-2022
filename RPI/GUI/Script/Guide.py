# importing required packages
import ntpath
from PyQt5.QtWidgets import QWidget
from PyQt5.uic import loadUiType
import os

cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Guide.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))


# Define main window
class MainAPP_Guide (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Guide, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_Buttons()
        self.window()

    def window(self):
        self.setWindowTitle("Guide")
        self.setFixedSize(800, 480)

    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    def Handle_Exit(self):
        self.close()
