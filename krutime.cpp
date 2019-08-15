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
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// set initialized flag
				initialized = true;
				
				// clear error flag
				error = false;
				
				// set reConfig flag		
				state = s_read;
			} else {
				state = s_error;
			}
			break;

		case s_read: {
			
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, 10)) {
				// get current tickcnt
				tickcnt = get_tickcnt();
			
				uint8_t buff[3];
			/*/	if (i2c->read(channel, address, NULL, 0, buff, 3) == ESP_OK) {
					uint32_t res = (buff[0]<<16) | (buff[1]<<8) |buff[2];
							read_value = (uint32_t)res;
				} else{
					state = s_error;
				}*/
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

uint32_t KRUTIME::getRawValue(void){
    return read_value;
}

#endif