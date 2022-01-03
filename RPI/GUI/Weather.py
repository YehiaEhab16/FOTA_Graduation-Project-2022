# importing required packages
import ntpath
from PyQt5.QtWidgets import QWidget, QMessageBox
from PyQt5.uic import loadUiType
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtGui import QPixmap
import requests
import urllib.request
import time

# Flag to indicate whether the api is working or not
Flag = 1

# Load UI
FormClass, _ = loadUiType(ntpath.join(
    ntpath.dirname(__file__), "UI/Weather.ui"))


# Thread for accessing weather api
class MyThread(QThread):
    change_value = pyqtSignal(int)  # value to periodically update gui labels

    def run(self):
        cnt = 0
        while True:
            cnt += 1
            self.change_value.emit(cnt)
            time.sleep(60)  # Processing thread every 1 min


# Thread for updating weather widget
class MyThread2(QThread):
    change_value = pyqtSignal(int)  # value to periodically update gui labels

    def run(self):
        cnt = 0
        while True:
            cnt += 1
            self.change_value.emit(cnt)
            time.sleep(1)  # Processing thread every 1 sec


# Define main window
class MainAPP_Weather(QWidget, FormClass):
    def __init__(self, parent=None):
        super(MainAPP_Weather, self).__init__(parent)
        QWidget.__init__(self)
        self.setupUi(self)
        self.window()
        self.Handle_Buttons()
        self.thread = MyThread()
        self.thread.change_value.connect(self.Handle_WeatherUpdate)
        self.thread.start()
        self.thread2 = MyThread2()
        self.thread2.change_value.connect(self.Handle_UpdateDisplay)
        self.thread2.start()

    # GUI Buttons
    def Handle_Buttons(self):
        self.back.clicked.connect(self.Handle_Exit)

    # Window Size and Title
    def window(self):
        self.setWindowTitle("Weather")
        self.setFixedSize(800, 480)

    def Handle_WeatherUpdate(self):
        global Flag
        try:
            # Get data of current weather
            currentWeather = requests.get(
                'http://api.weatherapi.com/v1/current.json?key=e5ba2b962a7649e5967220742220101&q=Alexandria&aqi=no')

            # Setting flag (api request is successful)
            Flag = 1

            # Set current weather temperature
            self.weather.setText(
                str(int(currentWeather.json()['current']['temp_c'])) + '°')

            # Set current weather condition
            self.state.setText(
                str(currentWeather.json()['current']['condition']['text']))

            # Set current weather image
            currentTempImage = currentWeather.json(
            )['current']['condition']['icon']
            currentTempImage = currentTempImage.replace('64x64', '128x128')
            currentTempImagePixmap = QPixmap()
            currentTempImageData = urllib.request.urlopen(
                'http:' + currentTempImage).read()
            currentTempImagePixmap.loadFromData(currentTempImageData)
            self.icon.setPixmap(QPixmap(currentTempImagePixmap))

            # Get data of forecast weather
            forecastWeather = requests.get(
                'http://api.weatherapi.com/v1/forecast.json?key=e5ba2b962a7649e5967220742220101&q=Alexandria&days=1'
                '&aqi=no&alerts=no')

            # Set maximum temperature of the day
            maxTemp = str(int(forecastWeather.json()['forecast']
                              ['forecastday'][0]['day']['maxtemp_c'])) + '°'

            # Set minimum temperature of the day
            minTemp = str(int(forecastWeather.json()['forecast']
                              ['forecastday'][0]['day']['mintemp_c'])) + '°'

            # Set Min-Max temperature of the day label
            self.weather_2.setText(minTemp + ' - ' + maxTemp)

            # Set 3 AM temperature label
            firstForecastTemp = str(int(forecastWeather.json()['forecast']
                                        ['forecastday'][0]['hour'][3]['temp_c'])) + '°'
            self.temp1.setText(firstForecastTemp)

            # Set 9 AM temperature label
            secondForecastTemp = str(int(forecastWeather.json()['forecast']
                                         ['forecastday'][0]['hour'][9]['temp_c'])) + '°'
            self.temp2.setText(secondForecastTemp)

            # Set 3 PM temperature label
            thirdForecastTemp = str(int(forecastWeather.json()['forecast']
                                        ['forecastday'][0]['hour'][15]['temp_c'])) + '°'
            self.temp3.setText(thirdForecastTemp)

            # Set 9 PM temperature label
            fourthForecastTemp = str(int(forecastWeather.json()['forecast']
                                         ['forecastday'][0]['hour'][21]['temp_c'])) + '°'
            self.temp4.setText(fourthForecastTemp)

            # Set 3 AM temperature image
            firstforecastImage = forecastWeather.json(
            )['forecast']['forecastday'][0]['hour'][3]['condition']['icon']
            firstforecastImage = firstforecastImage.replace('64x64', '128x128')
            firstforecastImagePixmap = QPixmap()
            firstforecastImageData = urllib.request.urlopen(
                'http:' + firstforecastImage).read()
            firstforecastImagePixmap.loadFromData(firstforecastImageData)
            self.icon1.setPixmap(QPixmap(firstforecastImagePixmap))

            # Set 9 AM temperature image
            secondforecastImage = forecastWeather.json(
            )['forecast']['forecastday'][0]['hour'][9]['condition']['icon']
            secondforecastImage = secondforecastImage.replace('64x64', '128x128')
            secondforecastImagePixmap = QPixmap()
            secondforecastImageData = urllib.request.urlopen(
                'http:' + secondforecastImage).read()
            secondforecastImagePixmap.loadFromData(secondforecastImageData)
            self.icon2.setPixmap(QPixmap(secondforecastImagePixmap))

            # Set 3 PM temperature image
            thirdforecastImage = forecastWeather.json(
            )['forecast']['forecastday'][0]['hour'][15]['condition']['icon']
            thirdforecastImage = thirdforecastImage.replace('64x64', '128x128')
            thirdforecastImagePixmap = QPixmap()
            thirdforecastImageData = urllib.request.urlopen(
                'http:' + thirdforecastImage).read()
            thirdforecastImagePixmap.loadFromData(thirdforecastImageData)
            self.icon3.setPixmap(QPixmap(thirdforecastImagePixmap))

            # Set 9 PM temperature image
            fourthforecastImage = forecastWeather.json(
            )['forecast']['forecastday'][0]['hour'][21]['condition']['icon']
            fourthforecastImage = fourthforecastImage.replace('64x64', '128x128')
            fourthforecastImagePixmap = QPixmap()
            fourthforecastImageData = urllib.request.urlopen(
                'http:' + fourthforecastImage).read()
            fourthforecastImagePixmap.loadFromData(fourthforecastImageData)
            self.icon4.setPixmap(QPixmap(fourthforecastImagePixmap))
        except Exception:
            Flag = 0

    # Function to display warning message
    def Handle_UpdateDisplay(self):
        if QWidget.isVisible(self) and Flag == 0:
            self.thread2.terminate()
            QMessageBox.warning(self, 'Weather Update Failed',
                                'Please check your internet connection')

    # Exit Function
    def Handle_Exit(self):
        self.thread2.start()
        self.close()
