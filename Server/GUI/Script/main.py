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

# Initializing Firebase Server
storage, db = Server.init()

# Load UI
FormClass, _ = loadUiType(ntpath.join(ntpath.dirname(__file__), "../UI/App.ui"))

version = "1"
error = "0"


# Thread for reading from server
class MyThread(QThread):
    change_value = pyqtSignal(int)  # value to periodically udpate gui labels

    def run(self):
        global version, error
        cnt = 0
        while True:
            cnt += 1
            time.sleep(1)   # Accessing server every 1 sec
            version = str(db.child("aW0PKEndkpi4Wp4qksi3HA==").child(
                "App_ECU").get().val())
            error = str(db.child("zPPO6sJUEU5WrqeEnB2N9g==").child("Uid").get().val())
            self.change_value.emit(cnt)


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
        global version, error
        self.browse.clicked.connect(self.Handle_Browse)
        self.upload.clicked.connect(self.Handle_Upload)
        self.exit.clicked.connect(Handle_Exit)
        self.thread = MyThread()
        self.thread.change_value.connect(self.Handle_Update)
        self.thread.start()

    # Window specs
    def Handle_UI(self):
        Gui.window(self)

    # Browse button
    def Handle_Browse(self):
        Gui.browse(self,QFileDialog)

    # Upload Button
    def Handle_Upload(self):
        Gui.upload(self, db, storage, QMessageBox)

    # Function to update GUI Labels (Version and Error)
    def Handle_Update(self):
        global version, error
        Gui.update(self, version, error, db, QMessageBox)


# Executing main window
def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
