#include <Arduino.h>
#include "bluetooth.h"
#include <EEPROM.h>

#define motor 0
#define powerLED 34
#define lowBat 5
#define light1 21
#define light2 22
#define bluetooth 26
#define buzzer 32
#define snoozeIn 15
#define snoozeOut 14

struct{
    int sound = 0;
    int light = 0;
    // int vibration = 0;
    int interval = 0;
    int freq = 2000;
} mainSettings;
int count;
unsigned long startMillis;
float voltageLevel;

void snooze(){
  startMillis = millis();
  Serial.println("Snooze");
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(16);
  EEPROM.get(0,mainSettings);
  Serial.println("Old values are: "+String(mainSettings.sound)+","+String(mainSettings.light)+","+String(mainSettings.interval)+","+String(mainSettings.freq));
  setupBluetooth();

  count = .25*mainSettings.freq;
  startMillis = millis();
  voltageLevel=0;
  // startup(5);                 // initialize the board and let it set up for about 5 seconds
  pinMode(motor, OUTPUT); // Vibrating Motor
  // pinMode(powerLED, INPUT); // Power LED
  pinMode(lowBat, OUTPUT); // Low Battery Indicator LED
  pinMode(light1, OUTPUT); // Lights
  pinMode(light2, OUTPUT);
  pinMode(bluetooth, INPUT); //  ???
  pinMode(buzzer, OUTPUT); // Buzzer
  // pinMode(snoozeIn, INPUT);  // Snooze button reciever
  pinMode(snoozeIn, INPUT_PULLDOWN);
  attachInterrupt(snoozeIn, snooze, RISING);
  pinMode(snoozeOut, OUTPUT); // Snooze button transmitter

  digitalWrite(motor, LOW); // Set all outputs to LOW after initializing them
  digitalWrite(lowBat, LOW); 
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  // digitalWrite(unknown, LOW);
  digitalWrite(buzzer, LOW);

  // digitalWrite(powerLED, LOW);
  digitalWrite(snoozeOut, HIGH);
}

void loop() {

  if(digitalRead(bluetooth)) setupBluetooth();
  else stopBluetooth();

  voltageLevel = analogRead(powerLED);
  voltageLevel = 3.3*voltageLevel/4095;
  Serial.println(voltageLevel);
  if(voltageLevel < 3.15){
    digitalWrite(lowBat,HIGH);
  }
  else digitalWrite(lowBat, LOW);

  if(millis() -startMillis > mainSettings.interval * 1000){
    if(mainSettings.light){;
    digitalWrite(light1, HIGH);
    Serial.println("LED on");
    }
    digitalWrite(light2, LOW);
    for(int i = 0; i < count; i++){
      if(mainSettings.sound)
        digitalWrite(buzzer, HIGH);
      delayMicroseconds(500000/mainSettings.freq);
      digitalWrite(buzzer, LOW);
      delayMicroseconds(500000/mainSettings.freq);
    }
    if(mainSettings.light){
      Serial.println("LED off");
      digitalWrite(light1, LOW);
      digitalWrite(light2, HIGH);
    }
    for(int i = 0; i < count; i++){
      if(mainSettings.sound)
        digitalWrite(buzzer, HIGH);
      delayMicroseconds(500000/mainSettings.freq);
      digitalWrite(buzzer, LOW);
      delayMicroseconds(500000/mainSettings.freq);
    }
  }else{
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    delay(100);
  }
}