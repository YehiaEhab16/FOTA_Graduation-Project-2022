# Raspberry Pi GUI
This part is responsible for User ECU

Microcontroller -> Raspberry Pi 3 B+

The GUI is responsible for showing notification updates to the user

In addition to some functionalities like:

Phone - Maps - Weather - Music Player - Radio - Video Player - Calendar

The frontend is designed using QT Designer

The GUI is implemeted using PyQt5

## Dependencies 
### Notes 

Do **NOT** install any other version of PyQt5 as all the versions are modern and do not match certain sub libraries such as PyQt5.QtMultimedia

OpenCv library works only with Python v3.7

Please install the required packages:
```sh
sudo nano /etc/apt/sources.list
```
Then write:
```
deb http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
# Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
```
And
```sh
nano /etc/apt/sources.list.d/raspi.list
```
Then write:
``` 
deb http://archive.raspberrypi.org/debian/ buster main
# Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://archive.raspberrypi.org/debian/ buster main
```
```sh
pip install --user --upgrade pip

sudo apt update

sudo apt upgrade

sudo apt-get build-dep qtmultimedia5-dev

sudo apt-get source --compile qtmultimedia5-dev

sudo apt-get install libqt5multimedia5

sudo apt-get install libqt5multimedia5-plugins

sudo apt-get install qml-module-qtmultimedia

python3 -m pip install folium

sudo apt-get install python3-opencv

python3 -m pip install pyserial
```


## Run GUI at Booting Raspian OS
### Note 
This method lacks some features in the Desktop GUI
```sh
nano ~/bashrc 
```
Then write bash script: 
```sh
cd /home/pi/Desktop/Finial_project/FOTA_Graduation-Project-2022/RPI/GUI/Script 

python3 main.py
```
And
```sh
nano /home/pi/.config/lxsession/LXDE-pi/autostart
```

Then write in the file: 
```
@lxpanel --profile LXDE-pi
@pcmanfm --desktop --profile LXDE-pi
@xscreensaver -no-splash
@bash /home/pi/bashrc
```
