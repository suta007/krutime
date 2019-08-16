#include <EEPROM.h>
#include <Wire.h>

//#define sStart  HIGH

#define TrigPin 13
#define RefPin A0

#define KruF_START  0x01
#define KruF_STOP   0x02
#define KruF_Read   0x03
#define KruF_Clear  0x04

uint8_t sDetect;

uint8_t cmdBuff[2], dataBuff[4], pnt[6];

uint32_t cTime=0, sTime=0;
uint8_t NumPin, ReadPin;

bool StartFlag = false, ClearEEProm = false ,ReadFlag = false;

void setup() {
  //Serial.begin(9600);

  for(uint8_t i=0; i<=12; i++){
    pinMode(i, INPUT);
  }

  pinMode(TrigPin, OUTPUT);
  digitalWrite(TrigPin, LOW);
  
  pinMode(RefPin, INPUT);
  sDetect = digitalRead(RefPin);
  Wire.begin(0x0F);
  Wire.setClock(400000);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  if(ClearEEProm == true){
      for(int i=0; i< 40; i++){
        EEPROM.write(i, 0);
      }
      ClearEEProm =false;
  }

  if(StartFlag == true && NumPin > 0){
    bool Wait = true;
    for(int i=0; i<=NumPin; i++){
        while(StartFlag && Wait){
          if(digitalRead(i)== sDetect){
            if(i==0){
                sTime = millis();
            }else{
                unsigned char buff[3];
                unsigned char EEPromAddr = i*3;
                cTime = millis()- sTime;
                buff[0] = cTime >> 16;
                buff[1] = cTime >> 8;
                buff[2] = cTime & 0xFF;
                EEPROM.write(EEPromAddr, buff[0]);
                EEPROM.write(EEPromAddr+1, buff[1]);
                EEPROM.write(EEPromAddr+2, buff[2]);                
            }
            while(digitalRead(i)== sDetect){
              ;
            }
            Wait = false;
          }
        }
        Wait = true;
    }
    digitalWrite(TrigPin, HIGH);
    StartFlag = false;
    NumPin=0;
    delay(200);
    digitalWrite(TrigPin, LOW);
  }else{
    StartFlag = false;
  }
  
}

void requestEvent() {
  unsigned char buff[3];
  if(pnt[0] == KruF_Read && ReadPin >0){
    unsigned char EEPromAddrRead = ReadPin*3;
    buff[0] = EEPROM.read(EEPromAddrRead);
    buff[1] = EEPROM.read(EEPromAddrRead+1);
    buff[2] = EEPROM.read(EEPromAddrRead+2);
    Wire.write(buff,3);
    ReadPin=0;
  }

  if(pnt[0] == KruF_START && NumPin>0){
    buff[0] = NumPin+1;
    Wire.write(buff,1);
    StartFlag = true;
  }
}

void receiveEvent(int howMany) {
  if(howMany >0){
     memset(0, pnt, sizeof(pnt));
     uint8_t i=0;
      while (Wire.available()) { // loop through all but the last
        pnt[i] = Wire.read(); // receive byte as a character
        i++;
      }
  
    if(pnt[0] == KruF_START){
      //StartFlag = true;
      NumPin = pnt[1]-1;
    }else if(pnt[0] == KruF_STOP){
      StartFlag = false;
    }else if(pnt[0] == KruF_Read){
      if(pnt[1]>0 && pnt[1]<=12){
          ReadPin = pnt[1];
      }else{
          ReadPin = 0;
      }
    }else if(pnt[0] == KruF_Clear){
      ClearEEProm=true;
    }
  }
}
