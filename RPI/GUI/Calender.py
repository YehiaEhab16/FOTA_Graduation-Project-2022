# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QTabWidget ,QWidget
from PyQt5.QtCore import QTimer, Qt
from PyQt5.uic import loadUiType
import sys
import datetime


# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI\Calendar.ui"))


# Exit button
# def Handle_Exit():
#    sys.exit()


# GUI Functions
# Setting window title and size



# Define main window
class MainAPP_Calender (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Calender, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_Buttons()
        self.window()


        # creating a timer object
        #timer = QTimer(self)
        # adding action to timer
        # timer.timeout.connect(self.showTime)
        # update the timer every second
        # timer.start()

    def window(self):
        self.setWindowTitle("Calendar")
        self.setFixedSize(800, 480)
    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect (self.Handle_Exit)
    def Handle_Exit(self):
        self.close()


    # def showTime(self):
        # getting current time
        #currentTime = datetime.datetime.now()
        #day = currentTime.strftime("%a")
        #hour = currentTime.strftime("%I:%M %p")
        # showing it to the label
        #self.label_9.setText(day + " " + hour)
        # self.label_9.setAlignment(Qt.AlignCenter)

# Executing main window


# def main():
#     app = QApplication(sys.argv)
#     Window_Loop = MainAPP()
#     Window_Loop.show()
#     app.exec()


if __name__ == '__main__':
    main()