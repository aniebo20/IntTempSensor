
#include "stm32f7xx.h"
#include "adc.h"

#define ADC1EN					(1U<<8)						//Enable Clock for ADC1 on APB2 BUS
#define ADC1_CH18				(18U)
#define ADC1_SQR1_LEN_1			(0U)
#define SR_EOC					(1U<<1)
#define CR2_ADON				(1)
#define CR2_SWSTART				(1U<<30)
#define CR2_ALIGN				(1<<11)						//Right Align bits
#define CCR_VBATE				(1U<<22)
#define CCR_TSVREFE				(1U<<23)
#define CR2_CONT				(1U<<1)




//FOR USE OF THE INTERNAL TEMPERATURE SENSOR ON THE STMF767XX
//adc pin will be ADC1_IN18
//CHOOSE GPIO PIN FOR UART TX
//TEMPERATURE SENSOR CAN BE ENABLED IN THE ADC_CCR BIT23, DISABLE VBAT.




void int_temp_adc_init(void)
{
	/*Configure the ADC module
	 * 1. Enable clock access to ADC
	 * 2. Configure ADC parameters:
	 * 	a) Conversion Sequence start - What is the first channel you want to sample in the sequence register?
	 * 	b) Conversion Sequence length - How many channels are used?
	 * 	c) Enable ADC module*/

	//1.
	RCC->APB2ENR |= ADC1EN;
	//2.
	//a)
	ADC1->SQR3 = ADC1_CH18;
	//b)
	ADC1->SQR1 = ADC1_SQR1_LEN_1;
	//c)
	ADC1->CR2 |= CR2_ADON;
	ADC1->CR2 &= ~(CR2_ALIGN);

	/*1.Enable Temperature Sensor
	 *2.Disable VBAT*/

	//1.
	ADC->CCR |= CCR_TSVREFE;
	//2.
	ADC->CCR &= ~(CCR_VBATE);
}

void start_conversion(void)
{
	/*Set conversion mode to continuous*/
	ADC1->CR2 |= CR2_CONT;
	/*Start ADC conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint16_t adc_read(void)
{
	/*1.Wait for conversion to be complete
	 *2.Read conversion*/

	//1.
//	while ((ADC1->SR & SR_EOC)) {};

	//2.
	volatile uint16_t ADC1_DR_PROPER = (*(uint16_t*)0x4001204C);
	return ADC1_DR_PROPER;
}

