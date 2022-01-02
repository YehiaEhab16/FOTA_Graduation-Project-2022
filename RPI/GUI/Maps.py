# importing required packages
import ntpath
from PyQt5 import QtGui
from PyQt5.QtWidgets import QWidget, QPushButton, QHBoxLayout, QVBoxLayout
import pathlib

current_directory = str(pathlib.Path(__file__).parent.absolute())


# Define main window
class MainAPP_Map (QWidget):

    def __init__(self, parent=None):
        super(MainAPP_Map, self).__init__(parent)
        QWidget.__init__(self)
        self.window()

        # StyleSheet for UI
        self.setStyleSheet("""
            QWidget{
                color: silver;
                background-color: #302F2F;
                selection-background-color:#3d8ec9;
                selection-color: black;
                background-clip: border;
                border-image: none;
                outline: 0;
            }

            QWidget:item:hover{
                background-color: #78879b;
                color: black;
            }

            QWidget:item:selected{
                background-color: #3d8ec9;
            }

            QPushButton{
                color: silver;
                background-color: #302F2F;
                border-width: 2px;
                border-color: #4A4949;
                border-style: solid;
                padding-top: 12px;
                padding-bottom: 12px;
                padding-left: 20px;
                padding-right: 20px;
                border-radius: 4px;
            }

            QPushButton:disabled{
                background-color: #302F2F;
                border-width: 2px;
                border-color: #3A3939;
                border-style: solid;
                padding-top: 12px;
                padding-bottom: 12px;
                padding-left: 20px;
                padding-right: 20px;
                border-radius: 4px;
                color: #808080;
            }

            QPushButton:focus{
                background-color: #3d8ec9;
                color: white;
            }

            QPushButton:checked{
                background-color: #4A4949;
                border-color: #6A6969;
            }

            QPushButton:hover{
                border: 2px solid #78879b;
                color: silver;
            }


            QPushButton:pressed{
                background-color: #484846;
            }
        """)

        backButton = QPushButton("Back")
        backButton.clicked.connect(self.Handle_Exit)

        # Connecting all layouts
        controlLayout = QHBoxLayout()
        controlLayout.setContentsMargins(0, 0, 0, 0)
        controlLayout.addWidget(backButton)

        # Layouts initializations
        layout = QVBoxLayout()
        layout.addLayout(controlLayout)

        # Setting layout
        self.setLayout(layout)

    # Window Size, Title and Icon
    def window(self):
        self.setWindowTitle("Maps")
        self.setFixedSize(800, 480)
        self.setWindowIcon(QtGui.QIcon(current_directory + '/Images/icon.png'))

    def Handle_Exit(self):
        self.close()
