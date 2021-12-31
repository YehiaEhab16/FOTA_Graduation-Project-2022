from PyQt5 import QtGui
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtCore import Qt, QUrl, QSize
from PyQt5.QtMultimedia import QMediaContent, QMediaPlayer
from PyQt5.QtMultimediaWidgets import QVideoWidget
from PyQt5.QtWidgets import (QApplication, QComboBox, QHBoxLayout,
                             QPushButton, QSlider, QStyle, QVBoxLayout, QWidget, QStatusBar)
import pathlib
import os


current_directory = str(pathlib.Path(__file__).parent.absolute())

videoFiles = os.listdir(current_directory + '\Videos')


class MainAPP_Video (QWidget):
    def __init__(self, parent=None):
        super(MainAPP_Video, self).__init__(parent)
        QWidget.__init__(self)
        self.setWindowIcon(QtGui.QIcon(current_directory + '\Images\icon.png'))
        self.window()

        # StyleSheet for UI
        self.setStyleSheet("""
            QComboBox{
                padding-left: 20px;
                padding-top: 10px;
                padding-bottom: 10px;
                font-size: 20px;
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

        self.mediaPlayer = QMediaPlayer(None, QMediaPlayer.VideoSurface)

        btnSize = QSize(16, 16)
        videoWidget = QVideoWidget()

        # Back Button attributes
        backButton = QPushButton("Back")
        backButton.clicked.connect(self.Handle_Exit)

        # Video List ComboBox initializations
        self.videoList = QComboBox()
        for f in videoFiles:
            self.videoList.addItem(f)

        # Open Video Button attributes
        openButton = QPushButton("Open Video")
        openButton.setIconSize(btnSize)
        openButton.setFont(QFont("Noto Sans", 8))
        openButton.setIcon(QIcon.fromTheme(
            "document-open", QIcon(current_directory + '\Images\openFolderIcon.png')))
        openButton.clicked.connect(self.playVideo)

        # Play Button attributes
        self.playButton = QPushButton()
        self.playButton.setEnabled(False)
        self.playButton.setIconSize(btnSize)
        self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))
        self.playButton.clicked.connect(self.play)

        # Time Slider attributes
        self.positionSlider = QSlider(Qt.Horizontal)
        self.positionSlider.setRange(0, 0)
        self.positionSlider.sliderMoved.connect(self.setPosition)

        # Ready/File Path attributes
        self.statusBar = QStatusBar()
        self.statusBar.setFont(QFont("Noto Sans", 7))
        self.statusBar.setFixedHeight(14)

        # connecting all layouts
        controlLayout2 = QHBoxLayout()
        controlLayout2.addWidget(self.videoList)
        controlLayout = QHBoxLayout()
        controlLayout.setContentsMargins(0, 0, 0, 0)
        controlLayout.addWidget(openButton)
        controlLayout.addWidget(self.playButton)
        controlLayout.addWidget(self.positionSlider)
        controlLayout.addWidget(backButton)

        # Layouts initializations
        layout = QVBoxLayout()
        layout.addLayout(controlLayout2)
        layout.addWidget(videoWidget)
        layout.addLayout(controlLayout)
        layout.addWidget(self.statusBar)

        # Setting layout
        self.setLayout(layout)

        # Media Player attributes
        self.mediaPlayer.setVideoOutput(videoWidget)
        self.mediaPlayer.stateChanged.connect(self.mediaStateChanged)
        self.mediaPlayer.positionChanged.connect(self.positionChanged)
        self.mediaPlayer.durationChanged.connect(self.durationChanged)
        self.mediaPlayer.error.connect(self.handleError)
        self.statusBar.showMessage("Ready")

    # Play selected video from QComboBox function
    def playVideo(self):
        videoURL = current_directory + '\Videos\\' + self.videoList.currentText()
        self.mediaPlayer.setMedia(
            QMediaContent(QUrl.fromLocalFile(videoURL)))
        self.playButton.setEnabled(True)
        self.statusBar.showMessage(videoURL)
        self.play()

    # Play/Pause function setters
    def play(self):
        if self.mediaPlayer.state() == QMediaPlayer.PlayingState:
            self.mediaPlayer.pause()
        else:
            self.mediaPlayer.play()

    #   Play/Pause button icon function setters
    def mediaStateChanged(self, state):
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

    # Error handle function, disables play button & shows the error on screen
    def handleError(self):
        self.playButton.setEnabled(False)
        self.statusBar.showMessage("Error: " + self.mediaPlayer.errorString())

    def Handle_Exit(self):
        self.close()

    def window(self):
        self.setWindowTitle("Video")
        self.setFixedSize(800, 480)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    player = MainAPP_Video()
    player.setWindowTitle("Video")
    player.setFixedSize(800, 480)
    player.show()
    sys.exit(app.exec_())
