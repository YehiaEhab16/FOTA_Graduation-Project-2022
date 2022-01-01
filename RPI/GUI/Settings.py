# importing required packages
import ntpath
from PyQt5.QtWidgets import QTabWidget
from PyQt5.uic import loadUiType
from PyQt5.QtGui import QPixmap
# importing defined modules


# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI\Settings.ui"))


# Exit button
# def Handle_Exit():
#    sys.exit()

# GUI Functions
# Setting window title and size

# Define main window
class MainAPP_Setting (QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Setting, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()

    # GUI buttons

    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    def window(self):
        self.setWindowTitle("Settings")
        self.setFixedSize(800, 480)

    def Handle_Exit(self):
        self.close()
