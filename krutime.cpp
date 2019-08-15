#ifndef __KRUTIME_CPP__
#define __KRUTIME_CPP__

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "krutime.h"

KRUTIME::KRUTIME(int bus_ch, int dev_addr){
  channel = bus_ch;
	address = dev_addr;
	polling_ms = KRUTIME_POLLING_MS;
}

void KRUTIME::init(void){
    state = s_detect;
}

int KRUTIME::prop_count(void) {
	return 0;
}

bool KRUTIME::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool KRUTIME::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool KRUTIME::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool KRUTIME::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool KRUTIME::prop_write(int index, char *value) {
	// not supported
	return false;
}

void KRUTIME::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
  //  read_value=1;
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// set initialized flag
				initialized = true;
      //  read_value=2;
				// clear error flag
				error = false;

				// set reConfig flag
				state = StateFlag;
			} else {
				state = s_error;
        //read_value=3;
			}
			break;

		case s_read: {
      //read_value=4;
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, 10)) {
				// get current tickcnt
				tickcnt = get_tickcnt();

        pointer[0]=0x03;
        pointer[1]=0x03;

				if (i2c->read(channel, address, pointer, 2, buff, 3) == ESP_OK) {
					int res = (buff[0]<<16) | (buff[1]<<8) |buff[2];
							read_value = res;
				} else{
					state = s_error;
          //read_value=6;
				}
			}

			break;
		}

    case s_ReadPinTime: {
      //read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0]=0x03;
        pointer[1]=GateNum;

        if (i2c->read(channel, address, pointer, 2, buff, 3) == ESP_OK) {
          int res = (buff[0]<<16) | (buff[1]<<8) |buff[2];
              if(res==0){
                state=s_error;
              }else{
                read_value = res;
              }
        } else{
          state = s_error;
          //read_value=6;
        }
      }

      break;
    }

    case s_StartTime: {
      //read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0]=0x01;
        pointer[1]=PinNum & 0xFF;

        if (i2c->write(channel, address, pointer, 2) != ESP_OK) {
          state = s_error;
        }
      }

      break;
    }

    case s_StartTime2: {
      //read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0]=0x01;
        pointer[1]=PinNum & 0xFF;

        if (i2c->read(channel, address, pointer, 2, buff, 1) == ESP_OK) {
            if(buff[0] == pointer[1]){
              BoolStart=true;
            }else{
              BoolStart=false;
            }
        } else{
          state = s_error;
          //read_value=6;
        }
      }

      break;
    }

    case s_StopTime: {
      //read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0]=0x02;
        if (i2c->write(channel, address, pointer, 1) != ESP_OK) {
          state = s_error;
        }
      }

      break;
    }

    case s_ClearTime: {
      //read_value=4;
      // wait polling_ms timeout
      if (is_tickcnt_elapsed(tickcnt, 10)) {
        // get current tickcnt
        tickcnt = get_tickcnt();

        pointer[0]=0x04;
        if (i2c->write(channel, address, pointer, 1) != ESP_OK) {
          state = s_error;
        }
      }

      break;
    }

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

int KRUTIME::getRawValue(void){
    StateFlag=s_read;
    return read_value;
}

int KRUTIME::getGateTime(uint8_t num){
    GateNum = num;
    StateFlag=s_ReadPinTime;
    return read_value;
}

void KRUTIME::StartTime(uint8_t num){
    PinNum = num;
    StateFlag=s_StartTime;
}

bool KRUTIME::StartTime2(uint8_t num){
    PinNum = num;
    StateFlag=s_StartTime2;
    return BoolStart;
}

void KRUTIME::StopTime(void){
    StateFlag=s_StopTime;
}

void KRUTIME::ClearTime(void){
    StateFlag=s_ClearTime;
}

#endif