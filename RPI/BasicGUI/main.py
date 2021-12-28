# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog, QMessageBox
# from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.uic import loadUiType
import sys
# import time

# importing defined modules
import Gui

# Load UI
FormClass, _ = loadUiType(ntpath.join(ntpath.dirname(__file__), "BasicUI.ui"))


# Exit button
# def Handle_Exit():
#    sys.exit()


# Define main window
class MainAPP (QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QMainWindow.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
        self.Handle_Buttons()

    # GUI buttons
    def Handle_Buttons(self):
        pass

    def Handle_UI(self):
        Gui.window(self)


# Executing main window
def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
