#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "adc.h"

/*READING TEMPERATURE FROM INTERNAL TEMPERATURE SENSOR AND OUTPUTTING IT OVER UART*/
//Keep in mind printf has been re-targeted in the included files to output over TX line of UART3
uint16_t sensor_value = 0;
double temperature = 0;

double temp_from_raw(uint16_t raw)
{
	/*Derived from calibration data*/
	double out = (0.319 * raw) - 272;
	return out;
}

int main()
{
	uart3_tx_init();
	int_temp_adc_init();

	while(1)
	{
		start_conversion();

		sensor_value = adc_read();

		temperature = temp_from_raw(sensor_value);

		printf("Sensor value: %d Temperature: %.2f \n\r", (int)sensor_value, temperature);
	}
}





