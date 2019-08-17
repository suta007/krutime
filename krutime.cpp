#ifndef __KRUTIME_CPP__
#define __KRUTIME_CPP__

#include "krutime.h"
#include "esp_system.h"
#include "kidbright32.h"
#include <stdio.h>
#include <string.h>

KRUTIME::KRUTIME(int bus_ch, int dev_addr) {
  channel = bus_ch;
  address = dev_addr;
  polling_ms = KRUTIME_POLLING_MS;
}

void KRUTIME::init(void) { state = s_detect; }

int KRUTIME::prop_count(void) { return 0; }

bool KRUTIME::prop_name(int index, char *name) { return false; }

bool KRUTIME::prop_unit(int index, char *unit) { return false; }

bool KRUTIME::prop_attr(int index, char *attr) { return false; }

bool KRUTIME::prop_read(int index, char *value) { return false; }

bool KRUTIME::prop_write(int index, char *value) { return false; }

void KRUTIME::process(Driver *drv) {
  I2CDev *i2c = (I2CDev *)drv;

  switch (state) {
  case s_detect:
    if (i2c->detect(channel, address) == ESP_OK) {
      initialized = true;
      error = false;
      state = StateFlag;
    } else {
      state = s_error;
    }
    break;
  /*
    case s_read:
      // read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0] = 0x03;
        pointer[1] = 0x03;

        if (i2c->read(channel, address, pointer, 2, buff, 3) == ESP_OK) {
          int res = (buff[0] << 16) | (buff[1] << 8) | buff[2];
          read_value = res;
        } else {
          state = s_error;
          // read_value=6;
        }
      }

      break;
  */
  case s_ReadPinTime:
    if (is_tickcnt_elapsed(tickcnt, 10)) {
      tickcnt = get_tickcnt();
      if (BoolRead == true) {
        pointer[0] = 0x03;
        pointer[1] = GateNum;
        memset(buff, 0, sizeof(buff));
        if (i2c->read(channel, address, pointer, 2, buff, 3) == ESP_OK) {
          int res = (buff[0] << 16) | (buff[1] << 8) | buff[2];
          read_value = res;
          BoolRead = false;
        } else {
          state = s_error;
        }
      }
    }
    break;

  /*
      case s_StartTime:
        //read_value=4;
        // wait polling_ms timeout
        if (is_tickcnt_elapsed(tickcnt, 10)) {
          // get current tickcnt
          tickcnt = get_tickcnt();
          if(BoolStart == true){
            pointer[0]=0x01;
            pointer[1]=PinNum & 0xFF;

            if (i2c->write(channel, address, pointer, 2) != ESP_OK) {
              state = s_error;
            }else{
              BoolStart=false;
            }
          }

        }

        break;

  */
  case s_StartTime2:
    if (is_tickcnt_elapsed(tickcnt, 10)) {
      tickcnt = get_tickcnt();
      if (BoolStart2 == true) {
        pointer[0] = 0x01;
        pointer[1] = PinNum;
        if (i2c->read(channel, address, pointer, 2, buff, 1) == ESP_OK) {
         /* if (buff[0] == pointer[1]) {
            RetStart = true;
            BoolStart2 = false;
          } else {
            RetStart = false;
            state = s_error;
          }
          */
         RetPin=buff[0];
        } else {
          state = s_error;
          RetPin=99;
        }
      }
    }
    break;

  case s_StopTime:
    if (is_tickcnt_elapsed(tickcnt, 10)) {
      if (BoolStop == true) {
        tickcnt = get_tickcnt();
        pointer[0] = 0x02;
        if (i2c->write(channel, address, pointer, 1) != ESP_OK) {
          state = s_error;
        } else {
          BoolStop = false;
        }
      }
    }
    break;

  case s_ClearTime:
    if (is_tickcnt_elapsed(tickcnt, 10)) {
      tickcnt = get_tickcnt();
      if (BoolClear == true) {
        pointer[0] = 0x04;
        if (i2c->write(channel, address, pointer, 1) != ESP_OK) {
          state = s_error;
        } else {
          BoolClear = false;
        }
      }
    }
    break;

  case s_wait:
    // wait polling_ms timeout
    if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
      state = s_detect;
    }
    break;

  case s_error:
    error = true;
    initialized = false;
    tickcnt = get_tickcnt();
    state = s_wait;
    break;
  }
}
/*
int KRUTIME::getRawValue(void){
    StateFlag=s_read;
    return read_value;
}
*/
/*int KRUTIME::getGateTime(uint8_t num){
    GateNum = num;
    StateFlag=s_ReadPinTime;
    return read_value;
}
*/

void KRUTIME::SetGatePin(uint8_t num) {
  GateNum = num;
  state = s_ReadPinTime;
  BoolRead = true;
}

int KRUTIME::getGateTime() { return read_value; }
/*
void KRUTIME::StartTime(uint8_t num){
    PinNum = num;
    StateFlag=s_StartTime;
    BoolStart=true;
}
*/
uint8_t KRUTIME::StartTime2(uint8_t num) {
  PinNum = num;
  StateFlag = s_StartTime2;
  BoolStart2 = true;
  //return RetStart;
  return RetPin;
}

void KRUTIME::StopTime(void) {
  StateFlag = s_StopTime;
  BoolStop = true;
}

void KRUTIME::ClearTime(void) {
  StateFlag = s_ClearTime;
  BoolClear = true;
}

#endif