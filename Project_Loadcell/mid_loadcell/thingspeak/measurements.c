/* Created by matix21
 * MIT License
 */

#include "measurements.h"

float gb_gram = 0;

void set_gb_gram(float a){

	 gb_gram = a;

}

void ICACHE_FLASH_ATTR prepare_measurements(measurements *meas)
{

	// gb_gram = hx711_get_units(5);
	// uint8_t i = 10;
	// printf("Gb cabration: %d\n", (int)gb_gram);



	// while(1){
	char result[20] = "";
        // meas->gram = hx711_get_units(5) - gb_gram;
        // if(meas->gram < 0)
        //     meas->gram = 0;
        // dtostrf(meas->gram, 8, 1, result);
        // printf("Gia tri can: %s\n", result);
	// while(i > 0){
	// 	meas->gram = hx711_get_units(5) - gb_gram;
	// 	i--;
	// }
	meas->gram = hx711_get_units(5) + 26.0;

	dtostrf(meas->gram, 8, 1, result);
    printf("Gia tri can: %s\n", result);
    
}
