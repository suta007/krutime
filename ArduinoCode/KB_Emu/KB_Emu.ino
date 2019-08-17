#include <Wire.h>

#define KruF_START  0x01
#define KruF_STOP   0x02
#define KruF_Read   0x03
#define KruF_Clear  0x04
#define I2C_addr    0x0F
#define Emu_int     18

uint8_t num=4;
byte a,b,c;
uint32_t Buff;
bool CheckByte=false;
int error_code;
void setup() {
  Wire.begin(4,5); 
  Serial.begin(9600);
  pinMode(Emu_int, INPUT);
  Serial.println("Connecting");
  while(CheckWire(I2C_addr) != 0){
    ;
  }
  
 /*Serial.println("Clear EEPROM");
  Wire.beginTransmission(I2C_addr); // transmit to device #8
  Wire.write(KruF_Clear);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
*/
  delay(1000);
  Serial.println("Send Start Cmd");
  Wire.beginTransmission(I2C_addr); // transmit to device #8
  Wire.write(KruF_START);        // sends five bytes
  Wire.write(num);
  error_code  = Wire.endTransmission();    // stop transmitting
     if ( error_code )
   {
        Serial.print( "i2c set register error : " );
        Serial.println(error_code);
   } 
  delay(100);
  
  Serial.println("Wait ACK");
  Wire.requestFrom(I2C_addr, 1);
  delay(10);
  while (Wire.available()==1) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
  }
  delay(200);
  if(c == num){
    Serial.println("Lab Start");
  }else{
    Serial.print("Error -> ");
    Serial.println(c,DEC);
  }
}

void loop() {
  if(digitalRead(Emu_int)==HIGH){
    delay(500);
    Serial.println("Reading");
    for(int i=1; i<num; i++){
      Wire.beginTransmission(I2C_addr); // transmit to device #8
      Wire.write(KruF_Read);        // sends five bytes
      Wire.write(i);
      Wire.endTransmission();    // stop transmitting
      delay(500);
      Wire.requestFrom(I2C_addr, 3);
      if (Wire.available()) { // slave may send less than requested
        a = Wire.read();
        b = Wire.read();
        c = Wire.read();
      }
        Buff = a;
        Buff = (Buff << 8) | b;
        Buff = (Buff << 8) | c;
            Serial.print("Time ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.print(Buff);
            Serial.println(" mSec");

    }

      while(digitalRead(Emu_int)== HIGH){
         ;
      }
  }

}

uint8_t CheckWire(byte addr)
{
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    return error;
}
