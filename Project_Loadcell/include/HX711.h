#ifndef _HX711_H
#define _HX711_H

#ifdef __cplusplus
extern "C" {
#endif
/* ESP8266. */
#include "esp_common.h"

#include "gpio.h"

void hx711_init();

bool hx711_is_ready();

// set the gain factor; takes effect only after a call to read()
// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
// depending on the parameter, the channel is also set to either A or B
void hx711_set_gain(int gain);

// waits for the chip to be ready and returns a reading
long hx711_read();

// returns an average reading; times = how many times to read
long hx711_read_average(int times);
		

// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
// times = how many readings to do
float hx711_get_units(int times);

// set the OFFSET value for tare weight; times = how many times to read the tare value
void hx711_tare(int times);

// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
void hx711_set_scale(float scale);

// get the current SCALE
float hx711_get_scale();

// set OFFSET, the value that's subtracted from the actual reading (tare weight)
void hx711_set_offset(long offset);

// get the current OFFSET
long hx711_get_offset();

// puts the chip into power down mode
void hx711_power_down();

// wakes up the chip after power down mode
void hx711_power_up();

#ifdef __cplusplus
}
#endif				


#endif