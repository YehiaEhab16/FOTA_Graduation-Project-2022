# Gui Functions

# Setting window title and size
import os
from base64 import b64encode
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

cwd = os.getcwd()
encryptedFilePath = r'%s' % cwd + '\Server\GUI\Script\\fileToBeEncrypted.hex'

def encryptFile (filePath):
     firstWrite = True
     secretKey = b'abcdefghijklmnop'
     cipher = AES.new(secretKey, AES.MODE_ECB)
     with open(filePath) as beforeEncryptionFile:
      lines = beforeEncryptionFile.readlines()
      for row in lines:
       data = bytes(str(row), 'utf-8')
       ct_bytes = cipher.encrypt(pad(data, AES.block_size))
       ct = b64encode(ct_bytes).decode('utf-8')
       if firstWrite == True:
        afterEncryptionFile = open(encryptedFilePath, "w")
        afterEncryptionFile.write(ct + '\n')
        firstWrite = False
       elif firstWrite == False:
        afterEncryptionFile = open(encryptedFilePath, "a")
        afterEncryptionFile.write(ct + '\n')
     return encryptedFilePath


def window(self):
    self.setWindowTitle("Server Manager")
    self.setFixedSize(452, 346)


# Browse button
def browse(self, QFileDialog):
    # getting path of required file
    save_place = str(QFileDialog.getOpenFileName(
        self, caption="Choose file to  upload", directory=".", filter="Object Files (*.hex *.c))"))
    # displaying path in gui (splitting is done to only extract the path)
    self.lineEdit.setText(save_place.split('\'')[1])


# Update GUI Labels
def update(self, version, error, db, QMessageBox):
    # Displaying Version
    if version is not None:
        self.version.setText("App_ECU_v" + version + ".0")
    # Error Detection
    if error is not None:
        if error != '0':
            db.child("zPPO6sJUEU5WrqeEnB2N9g==").update({"Uid": "0"})
            self.error.setText("Error Code 0xff")
            QMessageBox.warning(self, 'Error Detected',
                                'Check the error code for more details')
            self.error.setText("No Errors Detected")


# Upload button
def upload(self, db, storage, QMessageBox):
    # Extracting filename and path
    filePath = self.lineEdit.text()
    if '/' in filePath:
        fileName = filePath.split('/')[-1]
        fileNameWithoutExtension = filePath.split('/')[-1][:-4]
    else:
        fileName = filePath.split("\\")[-1]
        fileNameWithoutExtension = filePath.split('\\')[-1][:-4]

    try:
        versionCheck = db.child("aW0PKEndkpi4Wp4qksi3HA==").child(
            fileNameWithoutExtension).get()  # checking if the file is already on the server
        if versionCheck.val() is None:
            # if file doesn't exist -> add path in database and update the storage
            storage.child(fileName).put(encryptFile(filePath))
            db.child("aW0PKEndkpi4Wp4qksi3HA==").update(
                {fileNameWithoutExtension: 1})
        else:
            # if file is existing -> update version in database and update storage
            storage.child(fileName).put(encryptFile(filePath))
            versionNumber = int(versionCheck.val()) + 1
            db.child("aW0PKEndkpi4Wp4qksi3HA==").update(
                {fileNameWithoutExtension: versionNumber})
        QMessageBox.information(self, 'Done Uploading',
                                'The file was successfully uploaded to the server')
        self.lineEdit.setText('')

    except Exception:
        ret = QMessageBox.warning(self, 'Upload Failed',
                                  'Please select a valid file path or check the internet connection',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            upload(self, db, storage, QMessageBox)
