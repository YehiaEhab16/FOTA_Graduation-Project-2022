# importing required packages
import ntpath
from PyQt5.QtWidgets import QComboBox, QWidget
from PyQt5.QtCore import QUrl
from PyQt5.uic import loadUiType
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent
from PyQt5.QtGui import QPixmap
import sys
import os
import pathlib

#
current_directory = str(pathlib.Path(__file__).parent.absolute())
MusicFiles = os.listdir(current_directory + '\Music')

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/Music.ui"))


# Exit button
def Handle_Exit():
    sys.exit()


# Define main window
class MainAPP_Music (QWidget, FormClass):

    def __init__(self, parent=None):
        super(MainAPP_Music, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.player = QMediaPlayer()
        self.pixmap = QPixmap(current_directory + '\Images\Music.jpg')

        for f in MusicFiles:
            self.MusicList.addItem(f)

    # GUI buttons

    def Handle_Buttons(self):
        self.playButton.clicked.connect(self.Handle_Player)
        self.DecreaseSound.clicked.connect(self.DecreaseVolume)
        self.IncreaseSound.clicked.connect(self.IncreaseVolume)
        self.PreviousMusic.clicked.connect(self.Handle_Previous)
        self.NextMusic.clicked.connect(self.Handle_Next)
        self.back.clicked.connect(self.Handle_Exit)

    def IncreaseVolume(self):
        currentVolum = self.player.volume()
        self.player.setVolume(currentVolum+6)
        self.Sound.setValue(currentVolum+6)

    def DecreaseVolume(self):
        currentVolum = self.player.volume()
        self.player.setVolume(currentVolum-6)
        self.Sound.setValue(currentVolum-6)

    def window(self):
        self.setWindowTitle("Music")
        self.setFixedSize(800, 480)

    def Handle_Previous(self):
        try:
            if self.MusicList.currentIndex() >= 1:
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex - 1
                self.MusicList.setCurrentIndex(newIndex)
                self.MusicPhoto.setPixmap(self.pixmap)
                Full_Path = current_directory + "\Music\\" + self.MusicList.currentText()
                url = QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()

        except:
            pass

    def Handle_Next(self):
        try:
            if self.MusicList.currentIndex() < self.MusicList.count() - 1:
                oldIndex = self.MusicList.currentIndex()
                newIndex = oldIndex + 1
                self.MusicList.setCurrentIndex(newIndex)
                self.MusicPhoto.setPixmap(self.pixmap)
                Full_Path = current_directory + "\Music\\" + self.MusicList.currentText()
                url = QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()

        except:
            pass

    def Handle_Player(self):
        currentVolum = self.player.volume()
        self.Sound.setValue(currentVolum)
        self.MusicPhoto.setPixmap(self.pixmap)
        Full_Path = current_directory + "\Music\\" + self.MusicList.currentText()
        url = QUrl.fromLocalFile(Full_Path)
        content = QMediaContent(url)
        self.player.setMedia(content)
        self.player.play()

    def Handle_Exit(self):
        self.close()
        self.player.stop()
