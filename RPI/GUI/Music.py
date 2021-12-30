# importing required packages
import ntpath
from PyQt5.QtWidgets import QApplication, QTabWidget ,QWidget
from PyQt5.QtCore import QTimer, QTime, Qt,QUrl
from PyQt5.uic import loadUiType
import sys
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent
import os
from PyQt5.QtGui import QPixmap
import sys
# importing defined modules


# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/Music.ui"))


# Exit button
def Handle_Exit():
      sys.exit()

# GUI Functions
# Setting window title and size



# Define main window
class MainAPP_Music (QWidget, FormClass):
    global Counter
    Counter = 0
    def __init__(self, parent=None):
        super(MainAPP_Music, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.player = QMediaPlayer()
        self.pixmap = QPixmap('Images\Music.jpg')

        # creating a timer object
        # timer = QTimer(self)
        # adding action to timer
        # timer.timeout.connect(self.showTime)
        # update the timer every second
        # timer.start()

    # GUI buttons
    def Handle_Buttons(self):
        self.playButton.clicked.connect(self.Handle_Player)
        self.DecreaseSound.clicked.connect (self.DecreaseVolume)
        self.IncreaseSound.clicked.connect (self.IncreaseVolume)
        self.PreviousMusic.clicked.connect (self.Handle_Previous)
        self.NextMusic.clicked.connect (self.Handle_Next)
        self.back.clicked.connect (self.Handle_Exit)

    def IncreaseVolume(self):
        currentVolum = self.player.volume()
        self.player.setVolume (currentVolum+6)
        self.Sound.setValue(currentVolum+6)

    def DecreaseVolume(self):
        currentVolum = self.player.volume()
        self.player.setVolume (currentVolum-6)
        self.Sound.setValue(currentVolum-6)

    def window(self):
        self.setWindowTitle("Calendar")
        self.setFixedSize(800, 480)

    def Handle_Previous (self):
        global Counter
        try:
            if Counter<self.MusicList.count() and Counter>0:
                CurrentIndex = self.MusicList.currentIndex() + Counter
                #self.MusicList.currentIndex=CurrentIndex
                CurrentMusic = self.MusicList.itemText(CurrentIndex - 1)
                self.CurrentMusic.setText(CurrentMusic)
                self.MusicPhoto.setPixmap(self.pixmap)
                Full_Path = os.path.join(os.getcwd()+"\Music",CurrentMusic)
                url=QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()
                Counter=Counter-1

        except:
            pass

    def Handle_Next (self):
        global Counter
        try :
            if Counter<self.MusicList.count()-1:
                CurrentIndex = self.MusicList.currentIndex() + Counter
                CurrentMusic = self.MusicList.itemText(CurrentIndex + 1)
                self.CurrentMusic.setText(CurrentMusic)
                self.MusicPhoto.setPixmap(self.pixmap)
                Full_Path = os.path.join(os.getcwd()+"\Music",CurrentMusic)
                url=QUrl.fromLocalFile(Full_Path)
                content = QMediaContent(url)
                self.player.setMedia(content)
                self.player.play()
                Counter=Counter+1

        except:
            pass

    def Handle_Player (self) :
        global Counter
        Counter = 0
        currentVolum = self.player.volume()
        self.Sound.setValue(currentVolum)
        CurrentIndex = self.MusicList.currentIndex()
        CurrentMusic = self.MusicList.itemText(CurrentIndex)
        self.CurrentMusic.setText(CurrentMusic)
        self.MusicPhoto.setPixmap(self.pixmap)
        Full_Path = os.path.join(os.getcwd()+"\Music",CurrentMusic)
        url=QUrl.fromLocalFile(Full_Path)
        content = QMediaContent(url)

        self.player.setMedia(content)
        self.player.play()

    def Handle_Exit(self):
        self.close()
        self.player.stop()
    # def showTime(self):
        # getting current time
        #current_time = QTime.currentTime()
        # converting QTime object to string
        #label_time = current_time.toString('hh:mm')
        # showing it to the label
        # self.label_9.setText(label_time)
        # self.label_9.setAlignment(Qt.AlignCenter)

# Executing main window

