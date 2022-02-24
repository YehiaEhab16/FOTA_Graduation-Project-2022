# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget
from PyQt5.uic import loadUiType
import Comm
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


    def Handle_Update(self):
        pass

    def Handle_Send(self):
        pass

    def Handle_Diagnostics(self):
        pass

    def Handle_Exit(self):
        self.close()
