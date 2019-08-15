#include <Wire.h>

#define KruF_START  0x01
#define KruF_STOP   0x02
#define KruF_Read   0x03
#define KruF_Clear  0x04

uint8_t NumPin=0, ReadPin=0;
uint8_t pnt[6];

void setup() {
  Wire.begin(0x0F);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void receiveEvent(int howMany){
 if(howMany >0){
     memset(0, pnt, sizeof(pnt));
     uint8_t i=0;
      while (Wire.available()) { // loop through all but the last
        pnt[i] = Wire.read(); // receive byte as a character
        i++;
      }
  
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
    }
  }
}

void requestEvent() {
  unsigned char buff[3];
  if(pnt[0] == KruF_Read && ReadPin >0){
    unsigned char EEPromAddrRead = ReadPin*3;
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = ReadPin;
    Wire.write(buff,3);
    ReadPin=0;
  }
  if(pnt[0] == KruF_START && NumPin>-1){
    buff[0] = NumPin+1;
    Wire.write(buff,1);
    //StartFlag = true;
  }
}
