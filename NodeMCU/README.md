# <p align="center">Telematics Unit</p>

## 🌍 Overview

- The Telematics unit is the bridge connecting between the server and the whole system allowing to send and receive multiple data through it.
- We use the Telematics unit to communicate mainly with two other units, the server and the gateway (STM32).
- We used ESP32 module as it has a Wi-Fi module which is easy to be established using a few lines of code through Arduino IDE which gives us access to multiple libraries and functions in the ESP32.

## <img width="35" src="/assets/NodeMCU/circuit.svg"> Main Functions

- Communication with the server:

  - Download the update file.
  - Decrypt the downloaded file.
  - Send request to download the update file.
  - Send diagnostics to the server.

- Communcation with the Gateway:
  - Send update file to the Gateway.
  - Receive download request from the user.

## 📄 ESP32 Pinouts

<p  align="center">

<img  width="900"  src="/assets/NodeMCU/espPinouts.png">

</p>
