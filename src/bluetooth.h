#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <EEPROM.h>
#define SERVICE_UUID        "3b7d9313-56b5-485a-9534-36846518775b"
#define CHARACTERISTIC_UUID "dd93f7ca-915b-4f26-98f7-79e381bfbc18"

class MyCallbacks;

struct{
    int sound = 0;
    int light = 0;
    int interval = 0;
    int freq = 0;
} bluetoothSettings;



void setupBluetooth();
void stopBluetooth();
