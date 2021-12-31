# importing required packages
import ntpath
from PyQt5.QtWidgets import QWidget
from PyQt5.uic import loadUiType

# importing defined modules

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI\Weather.ui"))


# Exit button
# def Handle_Exit():
#    sys.exit()

# GUI Functions
# Setting window title and size

# Define main window
class MainAPP_Weather (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Weather, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()

    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    def window(self):
        self.setWindowTitle("Weather")
        self.setFixedSize(800, 480)

    def Handle_Exit(self):
        self.close()
