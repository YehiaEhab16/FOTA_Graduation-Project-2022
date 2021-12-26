# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog, QMessageBox
from PyQt5.uic import loadUiType
import sys

# importing defined modules
import Server
import Gui

# Initializing Firebase Server
storage, db = Server.init()

# Load UI
FormClass, _ = loadUiType(ntpath.join(ntpath.dirname(__file__), "App.ui"))


# Exit button
def Handle_Exit():
    sys.exit()


# Define main window
class MainAPP (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
        self.Handle_Buttons()

    # GUI buttons
    def Handle_Buttons(self):
        self.browse.clicked.connect(self.Handle_Browse)
        self.upload.clicked.connect(self.Handle_Upload)
        self.exit.clicked.connect(Handle_Exit)

    # Window specs
    def Handle_UI(self):
        Gui.window(self)

    # Browse button
    def Handle_Browse(self):
        Gui.browse(self,QFileDialog)

    # Upload Button
    def Handle_Upload(self):
        Gui.upload(self, db, storage, QMessageBox)


# Executing main window
def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
