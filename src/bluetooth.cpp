#include "bluetooth.h"

BLECharacteristic* pCharacteristic = NULL;
int settingsIndex = 0;
int sound = 0;
int light = 0;
int vibration = 0;
int minute = 0;
int sec = 0;
int interval = 0;
int freq = 0;

bool bluetoothEnabled = false;

class MyCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic) {
      Serial.println("write");

      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {

        Serial.println("*********");
        Serial.print("New value: ");

        for (int i = 0; i < value.length(); i++)

          // Serial.print(value[i]);
          Serial.print((int)value[0]);

        Serial.println();

        Serial.println("*********");

        Serial.print("Settings Index: ");
        Serial.println(settingsIndex);
        switch(settingsIndex){
            case 0: 
                sound = (int)value[0];
                Serial.print("Sound: ");
                Serial.println(sound);
                bluetoothSettings.sound = sound;
                settingsIndex++;
                break;
            case 1:
                light = (int)value[0];
                Serial.print("Light: ");
                Serial.println(light);
                bluetoothSettings.light = light;
                settingsIndex++;
                break;
            // case 2:
            //     vibration = (int)value[0];
            //     Serial.print("Vibration: ");
            //     Serial.println(vibration);
            //     bluetoothSettings.vibration = vibration;
            //     settingsIndex++;
            //     break;
            case 2:
                minute = (int)value[0];
                Serial.print("Minutes: ");
                Serial.println(minute);
                settingsIndex++;
                break;
            case 3:
                sec = (int)value[0];
                interval = minute*60+sec;
                Serial.print("Seconds: ");
                Serial.println(sec);
                Serial.print("Interval: ");
                Serial.println(interval);
                bluetoothSettings.interval = interval;
                
                settingsIndex++;
                break;
            case 4:
                freq = 16*(int)value[0]+400;
                Serial.print("Frequency: ");
                Serial.println(freq);
                bluetoothSettings.freq = freq;
                EEPROM.put(0,bluetoothSettings);
                EEPROM.commit();
                ESP.restart();
                Serial.println("Writing to EEPROM");
                settingsIndex=0;
                break;
            default:
                Serial.println("settingsIndex is out of bounds.");

        }
      }

    }

};



void setupBluetooth(){

    if(!bluetoothEnabled){

        bluetoothEnabled = true;

        Serial.println("Starting BLE work!");

        BLEDevice::init("Long name works now");

        BLEServer *pServer = BLEDevice::createServer();

        BLEService *pService = pServer->createService(SERVICE_UUID);

        pCharacteristic = pService->createCharacteristic(

                                                CHARACTERISTIC_UUID,

                                                BLECharacteristic::PROPERTY_READ |

                                                BLECharacteristic::PROPERTY_WRITE |

                                                BLECharacteristic::PROPERTY_NOTIFY

                                            );


        pCharacteristic->setCallbacks(new MyCallbacks());

        pCharacteristic->setValue("Test");

        pCharacteristic->setReadProperty(true);

        pService->start();

        // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility

        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

        pAdvertising->addServiceUUID(SERVICE_UUID);

        pAdvertising->setScanResponse(true);

        pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue

        pAdvertising->setMinPreferred(0x12);

        BLEDevice::startAdvertising();

        Serial.println("Characteristic defined! Now you can read it in your phone!");
    }
};

void stopBluetooth(){
    if(bluetoothEnabled){
        bluetoothEnabled = false;
        BLEDevice::deinit();
        Serial.println("Bluetooth Disabled");
    }
};