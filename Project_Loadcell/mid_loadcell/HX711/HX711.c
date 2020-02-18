

#include "HX711.h"


#define HX711_CLK_OUT_PIN       GPIO_Pin_14 //D5
#define HX711_CLK_OUT_NUM       14  
#define HX711_DA_IN_PIN         GPIO_Pin_12 //D6
#define HX711_DA_IN_NUM         12

static int 	    GAIN;					// The user defined gain value.
static long 	OFFSET	= 0;	// The offset value used for tare weight.
static float    SCALE 	= 1;	// The scale value in order to get more accurate value.


void hx711_init(){
	GPIO_ConfigTypeDef io_out_conf;

    io_out_conf.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    io_out_conf.GPIO_Mode = GPIO_Mode_Output;
    io_out_conf.GPIO_Pin = HX711_CLK_OUT_PIN;
    // io_in_conf.GPIO_Pullup = GPIO_PullUp_EN;
    io_out_conf.GPIO_Pullup = GPIO_PullUp_DIS;
    gpio_config(&io_out_conf);


    GPIO_ConfigTypeDef io_in_conf;

    io_in_conf.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    io_in_conf.GPIO_Mode = GPIO_Mode_Input;
    io_in_conf.GPIO_Pin = HX711_DA_IN_PIN;
    // io_in_conf.GPIO_Pullup = GPIO_PullUp_EN;
    io_in_conf.GPIO_Pullup = GPIO_PullUp_DIS;
    gpio_config(&io_in_conf);
}

bool hx711_is_ready(){
		
		// When the data line goes low, the sensor is ready for retrieval.
		return GPIO_INPUT_GET(HX711_DA_IN_NUM)==0;
			
}

void hx711_set_gain(int gain){

	switch (gain) {
			case 128:		// channel A, gain factor 128
				GAIN = 1;
				break;
			case 64:		// channel A, gain factor 64
				GAIN = 3;
				break;
			case 32:		// channel B, gain factor 32
				GAIN = 2;
				break;
	}
	
		GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
}

long hx711_read(){

		// It checks the start sequence condition.
		while(!hx711_is_ready());

		int i;
	
		long value = 0;
		// 3 array each of 8 bit contain 24 bit data.
		uint8_t data[3] = {0};
		// The filler is used for preventing conflict if any in the case of negative number representation.
		uint8_t filler = 0x00;
	
		for(i = 0; i<8 ; i++){
			
			// The clock line is set.
			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,1);
			// The obtaining data is shifted(MSB first).
			data[2] |= GPIO_INPUT_GET(HX711_DA_IN_NUM) << (7-i);
			// The clock line is reset.
			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
	
	}

		for(i = 0; i<8 ; i++){
			
			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,1);
	

			data[1] |= GPIO_INPUT_GET(HX711_DA_IN_NUM) << (7-i);
			
			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
	
		}

		for(i = 0; i<8 ; i++){

			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,1);
	

			data[0] |= GPIO_INPUT_GET(HX711_DA_IN_NUM) << (7-i);
		

			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
	
		}

		// Channel and the gain factor are set for the next reading.
		for(i=0 ; i<GAIN; i++){

			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,1);
			GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
		}
	
		// It replicates the most significant bit to pad out a 32-bit signed integer.
		// It replicates the most significant bit to pad out a 32-bit signed integer.
		data[2] ^= 0x80;

		// It constructs a 32-bit signed integer.
		value =
				( (unsigned long)(data[2]) << 16
				| (unsigned long)(data[1]) << 8
				| (unsigned long)(data[0]) );

		return (long)(value);
	
	}

long hx711_read_average(int times){

	int i;

		long sum = 0;
		for(i =0; i<times ; i++){
			sum += hx711_read();
			//It does nothing but wait.
			vTaskDelay(10);
		}
		return sum / times;
	}

float hx711_get_units(int times) {
	long val= (hx711_read_average(times)-OFFSET);
	return (float)val / SCALE;
}

void hx711_tare(int times) {
	double sum = hx711_read_average(times);
	set_offset(sum);
}

void hx711_set_scale(float scale) {
	SCALE = scale;
}

float hx711_get_scale() {
	return SCALE;
}

void hx711_set_offset(long offset) {
	OFFSET = offset;
}

long hx711_get_offset() {
	return OFFSET;
}

void hx711_power_down() {
	GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
	GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,1);
}

void hx711_power_up() {
	GPIO_OUTPUT_SET(HX711_CLK_OUT_NUM,0);
}