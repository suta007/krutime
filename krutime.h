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
       s_ReadPinTime,
       s_StartTime,
	   s_StartTime2,
       s_StopTime,
       s_ClearTime,
			 s_error,
			 s_wait
		} state, StateFlag;
		TickType_t tickcnt, polling_tickcnt;
    uint8_t pointer[3];
    uint8_t buff[3];
    uint8_t PinNum,GateNum;
	bool BoolStart=false;

		int read_value = 0;
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
		int getRawValue(void) ;
		int getGateTime(uint8_t num);
		void StartTime(uint8_t num);
		bool StartTime2(uint8_t num);
		void StopTime(void);
		void ClearTime(void);
};
#endif
