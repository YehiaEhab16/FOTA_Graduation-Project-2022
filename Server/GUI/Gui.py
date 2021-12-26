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


# Upload button
def upload(self, db, storage, QMessageBox):
    # Extracting filename and path
    filePath = self.lineEdit.text()
    if '/' in filePath:
        fileName = filePath.split('/')[-1]
        fileNameWithoutExtension = filePath.split('/')[-1][:-2]
        print(filePath, fileName, fileNameWithoutExtension)
    else:
        fileName = filePath.split("\\")[-1]
        fileNameWithoutExtension = filePath.split('\\')[-1][:-2]
        print(filePath, fileName, fileNameWithoutExtension)

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
    except:
        ret = QMessageBox.warning(self, 'Upload Failed',
                                  'Please select a valid file path or check the internet connection',
                                  QMessageBox.Retry | QMessageBox.Ok)
        if ret == QMessageBox.Retry:
            upload(self, db, storage, QMessageBox)
