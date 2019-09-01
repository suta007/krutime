#include <EEPROM.h>
#include <Wire.h>

#define KruF_START 0x01
#define KruF_STOP 0x02
#define KruF_Read 0x03
#define KruF_Read0 0x30
#define KruF_Read1 0x31
#define KruF_Read2 0x32
#define KruF_Clear 0x04

uint8_t NumPin = 0, ReadPin = 0, initPin = 2, LastI;
uint8_t pnt[6];

int sTime, cTime;
void setup() {
  Wire.begin(0x0F);
  Wire.setClock(400000);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  for (uint8_t i = initPin; i <= 12; i++) {
    pinMode(i, INPUT);
    EEPROM.write(i * 3, i * 10);
  }
  digitalWrite(0, LOW);
  pinMode(13, OUTPUT);
}

void loop() {
  if (NumPin > 0) {
    digitalWrite(13, LOW);
    for (uint8_t i = initPin; i < (NumPin + initPin); i++) {

      while (digitalRead(i) == HIGH) {
        ;
      }
      if (i == initPin) {
        sTime = millis();
      } else {
        unsigned char EEPromAddr = i * 3;
        byte tBuff[3];
        cTime = millis() - sTime;
        tBuff[0] = (cTime >> 16) & 0xFF;
        tBuff[1] = (cTime >> 8) & 0xFF;
        tBuff[2] = cTime & 0xFF;
        EEPROM.write(EEPromAddr, tBuff[0]);
        EEPROM.write(EEPromAddr + 1, tBuff[1]);
        EEPROM.write(EEPromAddr + 2, tBuff[2]);
      }
    }
    digitalWrite(13, HIGH);
    NumPin = 0;
  }
}

void receiveEvent(int howMany) {
  if (howMany > 0) {
    memset(pnt, 0, sizeof(pnt));
    uint8_t i = 0;
    while (Wire.available()) {
      pnt[i] = Wire.read();

      i++;
    }
  }
}

void requestEvent() {

  if (pnt[0] == KruF_Read) {
    unsigned char EEPromAddrRead = (pnt[1] + initPin) * 3;
    byte rBuff[3];
    rBuff[0] = EEPROM.read(EEPromAddrRead);
    rBuff[1] = EEPROM.read(EEPromAddrRead + 1);
    rBuff[2] = EEPROM.read(EEPromAddrRead + 2);
    Wire.write(rBuff, 2);
  }
  if (pnt[0] == KruF_Read0) {
    unsigned char EEPromAddrRead = (pnt[1] + initPin) * 3;
    byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead);
    Wire.write(rBuff);
  }
  if (pnt[0] == KruF_Read1) {
    unsigned char EEPromAddrRead = (pnt[1] + initPin) * 3;
    byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead + 1);
    Wire.write(rBuff);
  }
  if (pnt[0] == KruF_Read2) {
    unsigned char EEPromAddrRead = (pnt[1] + initPin) * 3;
    byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead + 2);
    Wire.write(rBuff);
  }
  if (pnt[0] == KruF_START) {
    NumPin = pnt[1] & 0xFF;
    Wire.write(NumPin);
  }
}