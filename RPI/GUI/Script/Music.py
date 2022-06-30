# importing required packages
import ntpath
from PyQt5.QtWidgets import QStyle, QWidget
from PyQt5.QtCore import QUrl
from PyQt5.uic import loadUiType
#import PyQt5.QtMultimedia
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent
from PyQt5.QtCore import QThread, pyqtSignal
import os
import pathlib
import time


# Listing available music files from specific directory (Currently -> Music directory inside GUI)
current_directory = str(pathlib.Path(__file__).parent.absolute())
MusicFiles = os.listdir(current_directory + '/../Music')
cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Music.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))

# Initializing global variables
currentIndicator = ""
nextIndicator = ""
Counter = 0


# Thread for detecting song state
class MyThread(QThread):
    change_value = pyqtSignal(int)  # value to periodically update gui labels

    def run(self):
        cnt = 0
        while True:
            cnt += 1
            time.sleep(1)  # Processing thread every 1 sec
            self.change_value.emit(cnt)


# Define main window
class MainAPP_Music(QWidget, FormClass):
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
        # Adding files inside music list
        for f in MusicFiles:
            filesWithoutExtension = os.path.splitext(f)[0]
            self.MusicList.addItem(filesWithoutExtension)
        self.Sound.setValue(self.player.volume())

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
        self.Sound.setValue(self.player.volume() + 5)
        self.player.setVolume(self.player.volume() + 5)

    # Function to decrease volume
    def DecreaseVolume(self):
        self.Sound.setValue(self.player.volume() - 5)
        self.player.setVolume(self.player.volume() - 5)

    # Function to select previous song from list
    def Handle_Previous(self):
        global currentIndicator
        global nextIndicator
        try:
            # Checking if index is valid and updating current index
            if self.MusicList.currentIndex() >= 1:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))  # Changing icon to pause icon
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex - 1
                self.MusicList.setCurrentIndex(newIndex)
                Full_Path = current_directory + '/../Music/' + \
                    MusicFiles[self.MusicList.currentIndex()]
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
            # Getting next index if available
            if self.MusicList.currentIndex() < self.MusicList.count() - 1:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))  # Changing icon to pause icon
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex + 1
                self.MusicList.setCurrentIndex(newIndex)
                Full_Path = current_directory + '/../Music/' + \
                    MusicFiles[self.MusicList.currentIndex()]
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
            # Start thread to check for the song completion
            self.thread = MyThread()
            self.thread.change_value.connect(self.Handle_SongState)
            self.thread.start()
            # Check for song chosen from combo box
            self.MusicList.currentIndexChanged.connect(self.Handle_ChangeSong)
            self.playButton.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPause))  # Changing icon to pause icon
            currentVolume = self.player.volume()
            self.Sound.setValue(currentVolume)
            currentIndicator = self.MusicList.currentText()
            Full_Path = current_directory + '/../Music/' + \
                MusicFiles[self.MusicList.currentIndex()]
            url = QUrl.fromLocalFile(Full_Path)
            content = QMediaContent(url)
            self.player.setMedia(content)
            self.player.play()
            Counter = Counter + 1

        else:
            # Changing icon to play or pause according to song state
            if self.player.state() == QMediaPlayer.PlayingState:
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPlay))
                self.player.pause()
            elif self.player.state() == QMediaPlayer.PausedState:
                self.player.play()
                self.playButton.setIcon(
                    self.style().standardIcon(QStyle.SP_MediaPause))

    # Function for thread to play the next song when the current is finished
    def Handle_SongState(self):
        global Counter
        if self.player.state() == QMediaPlayer.StoppedState:
            self.Handle_Next()

    # Function to change song when changed from list
    def Handle_ChangeSong(self):
        global currentIndicator
        self.playButton.setIcon(
            self.style().standardIcon(QStyle.SP_MediaPause))
        Full_Path = current_directory + '/../Music/' + \
            MusicFiles[self.MusicList.currentIndex()]
        url = QUrl.fromLocalFile(Full_Path)
        content = QMediaContent(url)
        self.player.setMedia(content)
        self.player.play()
        currentIndicator = self.MusicList.currentText()

    # Function to exit music gui and stop player
    def Handle_Exit(self):
        self.playButton.setIcon(
            self.style().standardIcon(QStyle.SP_MediaPlay))  # Changing icon to play icon
        self.close()
        self.player.pause()
        try:
            self.thread.terminate()
        except AttributeError:
            pass
