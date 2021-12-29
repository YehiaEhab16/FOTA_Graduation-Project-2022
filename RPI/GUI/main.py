# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QTabWidget
from PyQt5.QtCore import QTimer, QTime, Qt
from PyQt5.uic import loadUiType
import sys

# importing defined modules
import Gui

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI\MainWindow.ui"))


# Exit button
# def Handle_Exit():
#    sys.exit()


# Define main window
class MainAPP (QTabWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QTabWidget.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
        self.Handle_Buttons()

        # creating a timer object
        # timer = QTimer(self)
        # adding action to timer
        # timer.timeout.connect(self.showTime)
        # update the timer every second
        # timer.start()

    # GUI buttons
    def Handle_Buttons(self):
        pass

    def Handle_UI(self):
        Gui.window(self)

    # def showTime(self):
        # getting current time
        #current_time = QTime.currentTime()
        # converting QTime object to string
        #label_time = current_time.toString('hh:mm')
        # showing it to the label
        # self.label_9.setText(label_time)
        # self.label_9.setAlignment(Qt.AlignCenter)

# Executing main window


def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
