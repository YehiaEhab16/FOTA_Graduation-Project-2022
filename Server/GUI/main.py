import ntpath
import PyQt5.QtCore
import PyQt5.QtWidgets
import PyQt5.QtGui
from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox, QFileDialog
from PyQt5.uic import loadUiType
import sys
import os
import urllib.request
import pyrebase
import json

###########################Firebase Configs############################

firebaseConfig = {
    'apiKey': "AIzaSyDR_u8I3FcZD3tA5fLZUzAoWWxwFHR9PsM",
    'authDomain': "fota-graduation-project-3c764.firebaseapp.com",
    'databaseURL': "https://fota-graduation-project-3c764-default-rtdb.firebaseio.com",
    'projectId': "fota-graduation-project-3c764",
    'storageBucket': "fota-graduation-project-3c764.appspot.com",
    'messagingSenderId': "491013029871",
    'appId': "1:491013029871:web:fde1e60c30874be47b001a",
    'measurementId': "G-9G7CPD1N1S"
}
firebase = pyrebase.initialize_app(firebaseConfig)
storage = firebase.storage()
db = firebase.database()

###########################Define the QT design ###############################

FormClass, _ = loadUiType(ntpath.join(ntpath.dirname(__file__), "App.ui"))

###########################Define the main Window by class####################


class MainAPP (QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.Handle_UI()
        self.Handle_Buttons()

    def Handle_UI(self):
        self.setWindowTitle("Server Manager")
        self.setFixedSize(452, 341)

    def Handle_Buttons(self):
        self.browse.clicked.connect(self.Handle_Browse)
        self.upload.clicked.connect(self.Handle_Upload)

    def Handle_Browse(self):
        save_place = QFileDialog.getSaveFileName(
            self, caption="Save As", directory=".", filter="All Files (*.*)")
        save_place = str(save_place)
        text = save_place.split('\'')[1]
        self.lineEdit.setText(text)

    def Handle_Upload(self):
        filePath = self.lineEdit.text()
        fileName = filePath.split('/')[-1]
        fileNameWithoutExtension = filePath.split('/')[-1][:-2]
        versionCheck = db.child("Software").child(
            fileNameWithoutExtension).get()
        if versionCheck.val() == None:
            db.child("Software").update(
                {fileNameWithoutExtension: "1"})
            storage.child(fileName).put(filePath)
        else:
            versionNumber = versionCheck.val()
            versionNumber = int(versionNumber)+1
            versionnumberTest = str(versionNumber)
            db.child("Software").update(
                {fileNameWithoutExtension: versionnumberTest})
            storage.child(fileName).put(filePath)


def main():
    app = QApplication(sys.argv)
    Window_Loop = MainAPP()
    Window_Loop.show()
    app.exec()


if __name__ == '__main__':
    main()
