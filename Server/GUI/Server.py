# Server Functions
import pyrebase

# Firebase Configs
firebaseConfig = {
    'apiKey': "AIzaSyBRrnJB5r0m9v9YsBj-em7ZefzYT4LVkp4",
    'authDomain': "fota-project-new.firebaseapp.com",
    'databaseURL': 'https://fota-project-new-default-rtdb.firebaseio.com/',
    'projectId': "fota-project-new",
    'storageBucket': "fota-project-new.appspot.com",
    'messagingSenderId': "558566920335",
    'appId': "1:558566920335:web:54c446e9387ccbbc04a0fa",
    'measurementId': "G-RF41KQX9GM"
}


# Initialization Function
def init():
    firebase = pyrebase.initialize_app(firebaseConfig)
    storage = firebase.storage()
    db = firebase.database()
    return storage, db
