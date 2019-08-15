#ifndef __KRUTIME_H__
#define __KRUTIME_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define KRUTIME_POLLING_MS 1000

class KRUTIME : public Device{
    private:
		enum {
			 s_detect, 
			 s_read, 
			 s_error, 
			 s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		uint32_t read_value = 0;
    public:
		// constructor
		KRUTIME(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		uint32_t getRawValue(void) ;
		void testfunction(void);
};

#endif
