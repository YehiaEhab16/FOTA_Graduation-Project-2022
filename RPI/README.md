# Raspberry Pi GUI
This part is responsible for User ECU

Microcontroller -> Raspberry Pi 3 B+

The GUI is responsible for showing ntification updates to the user
in addition to some functionalties like:
Phone - Maps - Weather - Music Player - Radio - Video Player - Calendar

The frontend is designed using QT Designer

The GUI is implemeted using PYQT

# Dependencies 
##Notes 

No intall any version of PyQt5 from the server because all versions are modren and no matching with some librarys as multimedia library

OpenCv Library work only in python3.7

Please install the required packcages:
```sh
sudo nano /etc/apt/sources.list
```
save : 
deb http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
# Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi

```sh
nano /etc/apt/sources.list.d/raspi.list
```
save : 
deb http://archive.raspberrypi.org/debian/ buster main
# Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://archive.raspberrypi.org/debian/ buster main

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

```


#Run GUI at Booting Raspian Os 
##Note 
this method loss some feature in GUI Desktop , i can not slove it

```sh
nano ~/bashrc 
```
Write bash script : 

```sh
cd /home/pi/Desktop/Finial_project/FOTA_Graduation-Project-2022/RPI/GUI/Script 

python3 main.py

```

```sh
nano /home/pi/.config/lxsession/LXDE-pi/autostart

```
Write in file : 
```
	@lxpanel --profile LXDE-pi
	@pcmanfm --desktop --profile LXDE-pi
	@xscreensaver -no-splash
	@bash /home/pi/bashrc

```




