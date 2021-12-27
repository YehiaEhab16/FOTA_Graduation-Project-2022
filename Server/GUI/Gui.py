# Gui Functions

# Setting window title and size
def window(self):
    self.setWindowTitle("Server Manager")
    self.setFixedSize(452, 346)


# Browse button
def browse(self, QFileDialog):
    # getting path of required file
    save_place = str(QFileDialog.getOpenFileName(
        self, caption="Choose file to  upload", directory=".", filter="Object Files (*.c *.o))"))
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
            db.child("Feedback").update({"Uid": "0"})
            self.error.setText("Error Code 0xff")
            QMessageBox.warning(self, 'Error Detected', 'Check the error code for more details')
            self.error.setText("No Errors Detected")


# Upload button
def upload(self, db, storage, QMessageBox):
    # Extracting filename and path
    filePath = self.lineEdit.text()
    if '/' in filePath:
        fileName = filePath.split('/')[-1]
        fileNameWithoutExtension = filePath.split('/')[-1][:-2]
    else:
        fileName = filePath.split("\\")[-1]
        fileNameWithoutExtension = filePath.split('\\')[-1][:-2]

    try:
        versionCheck = db.child("Software").child(
            fileNameWithoutExtension).get()  # checking if the file is already on the server
        if versionCheck.val() is None:
            # if file doesn't exist -> add path in database and update the storage
            db.child("Software").update(
                {fileNameWithoutExtension: "1"})
            storage.child(fileName).put(filePath)
        else:
            # if file is existing -> update version in database and update storage
            versionNumber = str(int(versionCheck.val()) + 1)
            db.child("Software").update(
                {fileNameWithoutExtension: versionNumber})
            storage.child(fileName).put(filePath)
        QMessageBox.information(self, 'Done Uploading',
                                'The file was successfully uploaded to the server')
        self.lineEdit.setText('')

    except Exception:
        ret = QMessageBox.warning(self, 'Upload Failed',
                                  'Please select a valid file path or check the internet connection',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            upload(self, db, storage, QMessageBox)
