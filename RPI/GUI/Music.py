# importing required packages
import ntpath
from PyQt5.QtWidgets import QStyle, QWidget
from PyQt5.QtCore import QUrl
from PyQt5.uic import loadUiType
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent
import sys
import os
import pathlib

# Listing available music files from specific directory (Currently -> Music directory inside GUI)
current_directory = str(pathlib.Path(__file__).parent.absolute())
MusicFiles = os.listdir(current_directory + '/Music')

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/Music.ui"))

# Initializing global variables
currentIndicator = ""
nextIndicator = ""
Counter = 0


# Define main window
class MainAPP_Music (QWidget, FormClass):
    # Global Variables
    global currentIndicator
    global nextIndicator
    global Counter

    def __init__(self, parent=None):
        super(MainAPP_Music, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.player = QMediaPlayer()
        self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))

        for f in MusicFiles:
            self.MusicList.addItem(f)

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Music")
        self.setFixedSize(800, 480)

    # GUI buttons
    def Handle_Buttons(self):
        self.playButton.clicked.connect(self.Handle_Player)
        self.DecreaseSound.clicked.connect(self.DecreaseVolume)
        self.IncreaseSound.clicked.connect(self.IncreaseVolume)
        self.PreviousMusic.clicked.connect(self.Handle_Previous)
        self.NextMusic.clicked.connect(self.Handle_Next)
        self.back.clicked.connect(self.Handle_Exit)

    # Function to increase volume
    def IncreaseVolume(self):
        self.player.setVolume(self.player.volume()+5)
        self.Sound.setValue(self.player.volume()+5)

    # Function to decrease volume
    def DecreaseVolume(self):
        self.player.setVolume(self.player.volume()-5)
        self.Sound.setValue(self.player.volume()-5)

    # Function to select previous song from list
    def Handle_Previous(self):
        global currentIndicator
        global nextIndicator
        try:
            if self.MusicList.currentIndex() >= 1:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex - 1
                self.MusicList.setCurrentIndex(newIndex)
                Full_Path = current_directory + "/Music/" + self.MusicList.currentText()
                url = QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()
                currentIndicator = self.MusicList.currentText()
                nextIndicator = currentIndicator

        except Exception:
            pass

    # Function to select next song from list
    def Handle_Next(self):
        global currentIndicator
        global nextIndicator
        try:
            if self.MusicList.currentIndex() < self.MusicList.count() - 1:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex + 1
                self.MusicList.setCurrentIndex(newIndex)
                Full_Path = current_directory + "/Music/" + self.MusicList.currentText()
                url = QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()
                currentIndicator = self.MusicList.currentText()
                nextIndicator = currentIndicator

        except Exception:
            pass

    # Function to play/pause song
    def Handle_Player(self):
        global currentIndicator
        global nextIndicator
        global Counter
        nextIndicator = self.MusicList.currentText()
        if nextIndicator != currentIndicator:
            Counter = 0
        if Counter == 0:
            self.playButton.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPause))
            currentVolume = self.player.volume()
            self.Sound.setValue(currentVolume)
            currentIndicator = self.MusicList.currentText()
            Full_Path = current_directory + "/Music/" + self.MusicList.currentText()
            url = QUrl.fromLocalFile(Full_Path)
            content = QMediaContent(url)
            self.player.setMedia(content)
            self.player.play()
            Counter = Counter + 1

        else:
            if self.player.state() == QMediaPlayer.PlayingState:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPlay))
                self.player.pause()
            elif self.player.state() == QMediaPlayer.PausedState:
                self.player.play()
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))
            elif self.player.state() == QMediaPlayer.StoppedState:
                Counter = 0
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))

    # Function to exit music gui and stop player
    def Handle_Exit(self):
        self.close()
        self.player.stop()
        sys.exit()
