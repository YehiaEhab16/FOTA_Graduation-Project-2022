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
        self.Handle_Buttons()



    def Handle_UI (self):
        self.setWindowTitle("Serevr Manager")
        self.setFixedSize(452,341)

    def Handle_Buttons (self):
        self.browse.clicked.connect(self.Handle_Brows)

    def Handle_Brows (self):
        save_place = QFileDialog.getSaveFileName(self,caption="Save As",directory=".",filter="All Files (*.*)")
        save_place =str(save_place)
        text = save_place.split('\'')[1]
        self.lineEdit.setText(text)


def main ():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()

if __name__ == '__main__':
    main()

