# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog, QMessageBox
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.uic import loadUiType
import sys
import time

# importing defined modules
import Server
import Gui


class MainAPP (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
    
    
    def Handle_UI(self):
        Gui.window(self)    
