# Narcolepsy_Device
This narcolepsy device is for my Fall 2019 Senior Design Project. The device is used to assist invidviduals with narcolepsy. It is designed to help the individual stay awake during high risk situations. The device has blue lights and a buzzer that go off after a timer. The user can either snooze the alarm or turn it off completely. 

The device is controlled by a microprocessor. The processor we chose is the ESP32-PICO. This device is low powered and able to connect to bluetooth. It is also capable of running on Arduino libraries. The device's settings can be controlled by an iPhone app. The app connects through bluetooth, then sends the settings and writes to the device's memory. The code for the app can be found here: https://github.com/BrandonOng22/BluetoothApp

## How to upload code to the esp32-pico
Since we used the esp32, uploading the code is not as simple as it would be for an Arduino. However, if you follow the steps below, you should be able to upload the code without a problem.
- Download Visual Studio Code
- In Visual Studio Code, add the PlatformIO IDE extension
- Clone or download this repository. If you are unfamiliar with git, you can download a zip file
- In PlatformIO Home, click Open Project
- Select the folder that contains this repository
- You should be ready to upload the code now. Plug in a micro-USB to the esp32-pico and press the upload button at the bottom of the screen