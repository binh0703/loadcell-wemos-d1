/* Created by matix21
 * MIT License
 */

#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include "esp_common.h"
#include "HX711.h"

#define ADC_MEASURES_NUM 10

typedef struct 
{
	float gram;
} measurements;

void set_gb_gram(float a);
void prepare_measurements(measurements *);



#endif
