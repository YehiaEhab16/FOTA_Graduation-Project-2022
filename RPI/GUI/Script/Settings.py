# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget
from PyQt5.uic import loadUiType
<<<<<<< HEAD
import Comm

=======
import os
import Comm
>>>>>>> ff62ba942b992b58f0baf1c8c82d19b289974242
# importing defined modules
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
<<<<<<< HEAD
        self.UpdateCheck.clicked.connect(self.Handle_Update)
        self.CheckUp.clicked.connect(self.Handle_Diagnostics)
        self.Contact.clicked.connect(self.Handle_Send)
=======
        self.back_5.clicked.connect(self.Handle_Exit)
        self.UpdateCheck.clicked.connect(self.Handle_Receive)
        self.Diagnos.clicked.connect(self.Handle_Send)
>>>>>>> ff62ba942b992b58f0baf1c8c82d19b289974242

    def window(self):
        self.setWindowTitle("Settings")
        self.setFixedSize(800, 480)

<<<<<<< HEAD
    def Handle_Update(self):
        pass

    def Handle_Send(self):
        pass

    def Handle_Diagnostics(self):
        pass
=======
    def Handle_Receive(self):
        print(Comm.Read_Data())

    def Handle_Send(self):
        print(Comm.Send())
>>>>>>> ff62ba942b992b58f0baf1c8c82d19b289974242

    def Handle_Exit(self):
        self.close()
