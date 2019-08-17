#include <Wire.h>
#include <EEPROM.h>
#define KruF_START  0x01
#define KruF_STOP   0x02
#define KruF_Read   0x03
#define KruF_Clear  0x04

uint8_t NumPin=0, ReadPin=0;
uint8_t pnt[6];
  unsigned char buff[3];
//uint8_t gPin[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};

//int InitTime,MyTime;
void setup() {
 // Serial.begin(115200);
  Wire.begin(0x0F);
  Wire.setClock(400000);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
 // InitTime=millis();
 for(uint8_t i=0; i<=12; i++){
  pinMode(i,INPUT_PULLUP);
  EEPROM.write(i*3, i*10);
 }
 pinMode(13,OUTPUT);
}

void loop() {
  if(NumPin > 0){
    digitalWrite(13,LOW);
     for(uint8_t i=0; i<=NumPin; i++){
       
        while(digitalRead(i)==HIGH){
          ;
        }
        EEPROM.write(i*3, i);
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
       //Serial.print(i,DEC);
       //Serial.print("="); 
       //Serial.println(pnt[i],DEC);

       
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
   unsigned char EEPromAddrRead = pnt[1]*3;
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = EEPROM.read(EEPromAddrRead);;
    Wire.write(buff,3);
    //ReadPin=0;

  }
  if(pnt[0] == KruF_START){
    NumPin = pnt[1] & 0xFF;
    Wire.write(NumPin);
    //StartFlag = true;
    //Serial.println(buff[0],DEC);
   //Serial.println("+++++++++++");
  }
}
