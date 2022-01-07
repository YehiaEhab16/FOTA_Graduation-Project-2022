# importing required packages
from PyQt5 import QtGui, QtCore
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtCore import Qt, QUrl, QSize
from PyQt5.QtMultimedia import QMediaContent, QMediaPlayer
from PyQt5.QtMultimediaWidgets import QVideoWidget
from PyQt5.QtWidgets import (QApplication, QComboBox, QHBoxLayout,
                             QPushButton, QSlider, QStyle, QVBoxLayout, QWidget, QLabel)
import pathlib
import os
import sys
import cv2

# Getting Current Directory
current_directory = str(pathlib.Path(__file__).parent.absolute())

# Listing available videos from specific directory
videoFiles = os.listdir(current_directory + '/Videos')


# Main Window
class MainAPP_Video (QWidget):
    def __init__(self, parent=None):
        super(MainAPP_Video, self).__init__(parent)
        QWidget.__init__(self)
        self.window()

        # StyleSheet for UI
        self.setStyleSheet("""
        QLabel {
            font-size:20px;
        }
            QComboBox{
                selection-background-color: #3d8ec9;
                background-color: #201F1F;
                border-style: solid;
                border: 1px solid #3A3939;
                border-radius: 2px;
                padding: 2px;
                min-width: 75px;
                font-size: 15px;
            }
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
                font-size:20px;
                background-color: #302F2F;
                border-width: 2px;
                border-color: #4A4949;
                border-style: solid;
                padding-top: 6px;
                padding-bottom: 6px;
                padding-left: 10px;
                padding-right: 10px;
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


            QSlider::groove:horizontal{
                border: 1px solid #3A3939;
                height: 8px;
                background: #201F1F;
                margin: 2px 0;
                border-radius: 2px;
            }

            QSlider::handle:horizontal{
                background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0.0 silver, stop: 0.2 #a8a8a8, stop: 1 #727272);
                border: 1px solid #3A3939;
                width: 14px;
                height: 14px;
                margin: -4px 0;
                border-radius: 2px;
            }
        """)

        # Initializing Media Player
        self.mediaPlayer = QMediaPlayer(None, QMediaPlayer.VideoSurface)

        btnSize = QSize(20, 20)
        iconSize = QSize(20, 20)
        self.videoWidget = QVideoWidget()
        self.videoWidget.setMaximumSize(800,320)

        # Back Button attributes
        backButton = QPushButton("Back")
        backButton.clicked.connect(self.Handle_Exit)

        # Video List ComboBox initializations
        self.videoList = QComboBox()
        for f in videoFiles:
            chars = ['.mp4', '.mov', '.wmv', '.avi', '.avchd', '.mkv', '.flv', '.f4v', '.swf', '.webm', '.html5']
            for char in chars:
                f = f.replace(char, "").replace(char.upper(), "")
            self.videoList.addItem(f)

        # Open Video Button attributes
        openButton = QPushButton("Start Video")
        openButton.setIconSize(iconSize)
        openButton.setFont(QFont("Noto Sans", 8))
        openButton.setIcon(QIcon.fromTheme(
            "document-open", QIcon(current_directory + '/Images/openFolderIcon.png')))
        openButton.clicked.connect(self.playVideo)

        # Play Button attributes
        self.playButton = QPushButton()
        self.playButton.setIconSize(btnSize)
        self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))
        self.playButton.clicked.connect(self.play)

        # Time Slider attributes
        self.positionSlider = QSlider(Qt.Horizontal)
        self.positionSlider.setRange(0, 0)
        self.positionSlider.sliderMoved.connect(self.setPosition)

        self.soundLabel = QLabel("Sound", self)
        self.soundLevel = QLabel("100%", self)

        self.volumeSlider = QSlider(Qt.Horizontal)
        self.volumeSlider.setRange(0, 100)
        self.volumeSlider.setValue(100)
        self.volumeSlider.setTickPosition(QSlider.NoTicks)
        self.volumeSlider.setTickInterval(0)
        self.volumeSlider.valueChanged.connect(self.setPositionVolume)
        self.volumeSlider.setMaximumWidth(200)

        # connecting all layouts
        controlLayout2 = QHBoxLayout()
        controlLayout2.addWidget(self.videoList)
        controlLayout = QHBoxLayout()
        controlLayout.setContentsMargins(0, 0, 0, 0)
        controlLayout.addWidget(openButton)
        controlLayout.addWidget(self.playButton)
        controlLayout.addWidget(self.positionSlider)
        controlLayout.addWidget(backButton)
        controlLayout3 = QHBoxLayout()
        controlLayout3.setContentsMargins(0, 0, 425, 0)
        controlLayout3.addWidget(self.soundLabel)
        controlLayout3.addWidget(self.soundLevel)
        controlLayout3.addWidget(self.volumeSlider)

        # Layouts initializations
        layout = QVBoxLayout()
        layout.addLayout(controlLayout2)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.videoWidget)

        layout.addLayout(layout2)
        layout.addLayout(controlLayout)
        layout.addLayout(controlLayout3)

        # Setting layout
        self.setLayout(layout)

        # Media Player attributes
        self.mediaPlayer.setVideoOutput(self.videoWidget)
        self.mediaPlayer.stateChanged.connect(self.mediaStateChanged)
        self.mediaPlayer.positionChanged.connect(self.positionChanged)

        self.mediaPlayer.durationChanged.connect(self.durationChanged)
        self.mediaPlayer.error.connect(self.handleError)

    # Window Size, Title and Icon
    def window(self):
        self.setWindowIcon(QtGui.QIcon(current_directory + '/Images/icon.png'))
        self.setWindowTitle("Video")
        self.setFixedSize(800, 480)

    # Play selected video from QComboBox function
    def playVideo(self):
        videoURL = current_directory + '/Videos/' + self.videoList.currentText() + '.mp4'
        vid = cv2.VideoCapture(videoURL)
        height = vid.get(cv2.CAP_PROP_FRAME_HEIGHT)
        width = vid.get(cv2.CAP_PROP_FRAME_WIDTH)
        width = int(width * 320.2 / height)
        self.videoWidget.setMaximumSize(width, 320)

        self.mediaPlayer.setMedia(
            QMediaContent(QUrl.fromLocalFile(videoURL)))
        self.play()

    # Play/Pause function setters
    def play(self):
        if self.mediaPlayer.state() == QMediaPlayer.PlayingState:
            self.mediaPlayer.pause()
        else:
            self.mediaPlayer.play()

    #   Play/Pause button icon function setters
    def mediaStateChanged(self):
        if self.mediaPlayer.state() == QMediaPlayer.PlayingState:
            self.playButton.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPause))
        else:
            self.playButton.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPlay))

    # Slider seconds function setter
    def positionChanged(self, position):
        self.positionSlider.setValue(position)

    # Slider position reset
    def durationChanged(self, duration):
        self.positionSlider.setRange(0, duration)

    # Slider position changed function
    def setPosition(self, position):
        self.mediaPlayer.setPosition(position)

    # Function to adjust volume
    def setPositionVolume(self, position):
        self.mediaPlayer.setVolume(position)
        self.soundLevel.setText(str(position) + "%")

    # Error handle function, disables play button & shows the error on screen
    def handleError(self):
        self.playButton.setEnabled(False)

    # Function to exit music gui and stop player
    def Handle_Exit(self):
        self.close()
        self.mediaPlayer.pause()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    player = MainAPP_Video()
    player.show()
    sys.exit(app.exec_())
