# importing required packages
import ntpath
from PyQt5.QtWidgets import QWidget, QStyle
from PyQt5.uic import loadUiType
from PyQt5.QtMultimedia import QMediaPlayer
import os

# Channel list
Channel_List = [87.8, 88.2, 88.7, 89.5, 90.9, 91.5, 92.1, 92.1, 92.7,
                93.7, 95, 95.4, 98.2, 98.8, 100.6, 102.2, 104.2, 105.3, 105.8, 106.3, 107.4, 108]
# Frequencies
Freq = 0
MinFreq = 87
MaxFreq = 110
# Indication to the play or pause
Counter = 1

cwd = os.getcwd()
parent = os.path.dirname(cwd)

Link = parent+'/UI/Radio.ui'
# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), Link))


# Define main window
class MainAPP_Radio(QWidget, FormClass):
    def __init__(self, parent=None):
        global Freq
        super(MainAPP_Radio, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.player = QMediaPlayer()
        Freq = float(self.freq.text())
        self.play_pause.setIcon(
            self.style().standardIcon(QStyle.SP_MediaPause))
        self.sound.setValue(100)
        self.player.setVolume(100)

    # GUI buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)
        self.previous.clicked.connect(self.PrevChannel)
        self.next.clicked.connect(self.NextChannel)
        self.increment.clicked.connect(self.Handle_Inc)
        self.decrement.clicked.connect(self.Handle_Dec)
        self.inc_sound.clicked.connect(self.IncreaseVolume)
        self.dec_sound.clicked.connect(self.DecreaseVolume)
        self.play_pause.clicked.connect(self.Play_Pause)

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Radio")
        self.setFixedSize(800, 480)

    # Function to increase volume
    def IncreaseVolume(self):
        currentVolume = self.player.volume() + 5
        self.player.setVolume(currentVolume)
        self.sound.setValue(currentVolume)
    # Function to decrease volume

    def DecreaseVolume(self):
        currentVolume = self.player.volume() - 5
        self.player.setVolume(currentVolume)
        self.sound.setValue(currentVolume)

    # Function for next channel
    def NextChannel(self):
        global Channel_List
        global Freq
        CheckFreq = 87.8
        # if self.player.state() == QMediaPlayer.PlayingState:
        if Counter == 1:
            if Freq != MaxFreq:
                while True:
                    Freq = round(Freq + 0.1, 1)
                    self.freq.setText(str(Freq))
                    # Searching for frequency in channel list
                    for i in Channel_List:
                        if Freq == i:
                            CheckFreq = i
                            break
                    # Break when finding frequency or reaching maximum frequency
                    if Freq == CheckFreq or Freq == MaxFreq:
                        break

    # Function for previous channel
    def PrevChannel(self):
        global Channel_List
        global Freq
        CheckFreq = 87.8
        # if self.player.state() == QMediaPlayer.PlayingState:
        if Counter == 1:
            if Freq != MinFreq:
                while True:
                    Freq = round(Freq - 0.1, 1)
                    self.freq.setText(str(Freq))
                    # Searching for frequency in channel list
                    for i in Channel_List:
                        if Freq == i:
                            CheckFreq = i
                            break
                    # Break when finding frequency or reaching minimum frequency
                    if Freq == CheckFreq or Freq == MinFreq:
                        break

    # Function for small step increment
    def Handle_Inc(self):
        # if self.player.state() == QMediaPlayer.PlayingState:
        if Counter == 1:
            global Freq
            if Freq < MaxFreq:
                Freq = round(Freq + 0.1, 1)
                self.freq.setText(str(Freq))

    # Function for small step decrement
    def Handle_Dec(self):
        # if self.player.state() == QMediaPlayer.PlayingState:
        if Counter == 1:
            global Freq
            if Freq > MinFreq:
                Freq = round(Freq - 0.1, 1)
                self.freq.setText(str(Freq))

    # Function to play/pause channels
    def Play_Pause(self):
        global Counter

        # if self.player.state() == QMediaPlayer.PlayingState:
        if Counter == 1:
            self.play_pause.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPlay))
            self.player.pause()
            Counter = 0
        # elif self.player.state() == QMediaPlayer.PausedState:
        elif Counter == 0:
            self.player.play()
            self.play_pause.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPause))
            Counter = 1

    # Function to exit music GUI
    def Handle_Exit(self):
        self.close()
