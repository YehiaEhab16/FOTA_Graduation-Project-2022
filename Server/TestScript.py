#       Script for testing upload and update files on server


#import json
#import requests
#import pyrebase

#   INITIALIZE SERVER CONFIGS AND ACCESS
# firebaseConfig = {
#    'apiKey': "AIzaSyDR_u8I3FcZD3tA5fLZUzAoWWxwFHR9PsM",
#    'authDomain': "fota-graduation-project-3c764.firebaseapp.com",
#    'databaseURL': "https://fota-graduation-project-3c764-default-rtdb.firebaseio.com",
#    'projectId': "fota-graduation-project-3c764",
#    'storageBucket': "fota-graduation-project-3c764.appspot.com",
#    'messagingSenderId': "491013029871",
#    'appId': "1:491013029871:web:fde1e60c30874be47b001a",
#    'measurementId': "G-9G7CPD1N1S"
# }
#firebase = pyrebase.initialize_app(firebaseConfig)
#db = firebase.database()
#storage = firebase.storage()

#   REPLACE/OVERRIDE FILE, OVERRIDE EXISTING FILE ON STORAGE WITH A NEW FILE ON YOUR MACHINE

# storage.child('storageFileName.extension').put('filepath/newFileName.extension')


#   UPLOAD FILE, FIRST TYPE IN THE NAME OF YOUR FILE ON YOUR MACHINE THEN TYPE IN THE NAME YOU WISH TO HOLD IN THE STORAGE
#   MACHINE FILE SHOULD BE PATHNAME/FILENAME.EXTENSION, STORAGE FILE SHOULD BE PATHNAME.EXTENSION


#file = input("Enter the name of the file you want to upload to storage: ")
#cloudFileName = input("Enter the name for the file in storage: ")
# storage.child(cloudFileName).put(file)

#   PRINT THE URL OF THE FILE ON THE STORAGE SERVER
# print(storage.child(cloudFileName).get_url(None))


#   DOWNLOAD FILE, ENTER THE DOWNLOAD LINK FROM STORAGE AND NAME IT ON YOUR MACHINE

#downloadLink = input("Enter download URL")
#downloadName = input("Enter the name you wish to have on your machine: ")
# storage.child(downloadLink).download(downloadName)


#   FETCH DATA FROM THE SOFTWARE BRANCH OF THE DATABASE

#data = db.child("Software").get()
# print(data.val())


#   POST DATA TO SOFTWARE BRANCH OF THE DATABASE

#data = {"SoftwareV": "1"}
# db.child("Software").update(data)
