#include <Wire.h>
#include <EEPROM.h>
#define KruF_START  0x01
#define KruF_STOP   0x02
#define KruF_Read   0x03
#define KruF_Read0  0x30
#define KruF_Read1  0x31
#define KruF_Read2  0x32
#define KruF_Clear  0x04

uint8_t NumPin=0, ReadPin=0,initPin=2,LastI;
uint8_t pnt[6];

  int sTime,cTime;
//uint8_t gPin[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};

//int InitTime,MyTime;
void setup() {
  //Serial.begin(115200);
  Wire.begin(0x0F);
  Wire.setClock(400000);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
 // InitTime=millis();
 for(uint8_t i=initPin; i<=12; i++){
  pinMode(i,INPUT);
  EEPROM.write(i*3, i*10);
 }
 digitalWrite(0,LOW);
 pinMode(13,OUTPUT);
}

void loop() {
  if(NumPin > 0){
    digitalWrite(13,LOW);
     for(uint8_t i=initPin; i<(NumPin+initPin); i++){
       
        while(digitalRead(i)==HIGH){
          ;
        }
        if(i==initPin){
            sTime=millis();
        }else{
                unsigned char EEPromAddr = i*3;
                byte tBuff[3];
                cTime = millis()- sTime;
                tBuff[0] = (cTime >> 16) & 0xFF;
                tBuff[1] = (cTime >> 8) & 0xFF;
                tBuff[2] = cTime & 0xFF;
                EEPROM.write(EEPromAddr, tBuff[0]);
                EEPROM.write(EEPromAddr+1, tBuff[1]);
                EEPROM.write(EEPromAddr+2, tBuff[2]);   
        }
     }
     digitalWrite(13,HIGH); 
     NumPin=0;
  }

}

void receiveEvent(int howMany){
 if(howMany >0){
     memset(pnt,0,sizeof(pnt));
     uint8_t i=0;
      while (Wire.available()) { // loop through all but the last
        pnt[i] = Wire.read(); // receive byte as a character
        
      // byte c = Wire.read();
      // Serial.print(i,DEC);
      // Serial.print("="); 
      // Serial.println(pnt[i],DEC);

       
       i++;
      }

      //Serial.println("+++");
      //memset(pnt, 0, sizeof(pnt));
 }

 /*
    if(pnt[0] == KruF_START){
      NumPin = pnt[1]-1;
    }else if(pnt[0] == KruF_STOP){
      //StartFlag = false;
    }else if(pnt[0] == KruF_Read){
      if(pnt[1]>0 && pnt[1]<=12){
          ReadPin = pnt[1];
      }else{
          ReadPin = 0;
      }
    }else if(pnt[0] == KruF_Clear){
      //ClearEEProm=true;
    }*/
    //Serial.println(pnt[0],DEC);
    //Serial.println(pnt[1],DEC);
   // Serial.println("+++++++++++");
  //}
}


void requestEvent() {

  //MyTime = millis() - InitTime;
  if(pnt[0] == KruF_Read){
   unsigned char EEPromAddrRead = (pnt[1]+initPin)*3;
   byte rBuff[3];
    rBuff[0] = EEPROM.read(EEPromAddrRead);
    rBuff[1] = EEPROM.read(EEPromAddrRead+1);
    rBuff[2] = EEPROM.read(EEPromAddrRead+2);
    Wire.write(rBuff,2);
    //ReadPin=0;
  }
  if(pnt[0] == KruF_Read0){
   unsigned char EEPromAddrRead = (pnt[1]+initPin)*3;
   byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead);
    Wire.write(rBuff);
  }
  if(pnt[0] == KruF_Read1){
   unsigned char EEPromAddrRead = (pnt[1]+initPin)*3;
   byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead+1);
    Wire.write(rBuff);
  }
  if(pnt[0] == KruF_Read2){
   unsigned char EEPromAddrRead = (pnt[1]+initPin)*3;
   byte rBuff;
    rBuff = EEPROM.read(EEPromAddrRead+2);
    Wire.write(rBuff);
  }
  if(pnt[0] == KruF_START){
    NumPin = pnt[1] & 0xFF;
    Wire.write(NumPin);
    //StartFlag = true;
    //Serial.println(buff[0],DEC);
   //Serial.println("+++++++++++");
  }
}
