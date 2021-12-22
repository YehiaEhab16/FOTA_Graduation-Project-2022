import ntpath
import PyQt5.QtCore
import PyQt5.QtWidgets
import PyQt5.QtGui
from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox, QFileDialog
from PyQt5.uic import loadUiType
import sys
import os
import urllib.request
###########################Define the QT design ###############################

FormClass,_ = loadUiType (ntpath.join(ntpath.dirname(__file__),"App.ui"))

###########################Define the main Window by class####################

class MainAPP (QWidget,FormClass):
    def __init__(self,parent = None):
        super(MainAPP,self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
        

    def Handle_UI (self):
        self.setWindowTitle("Serevr Manager")
        self.setFixedSize(452,341)


def main ():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()

if __name__ == '__main__':
    main()

