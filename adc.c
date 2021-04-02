/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32l0xx.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"
#include <stdio.h>

//void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void setup_gpio(){
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // enables clock to port A
	GPIOA->MODER |= 0x3 << GPIO_MODER_MODE4_Pos;               // sets PA4 to analog mode
}


// This function should enable the clock to ADC,
// turn on the clocks, wait for ADC to be ready.
void setup_adc() {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;     // enable the clock to ADC
    RCC->CR |= RCC_CR_HSION;     			// turn on clock
    while(!(RCC->CR & RCC_CR_HSIRDY));  	// wait for clock to be ready
    ADC1->CR |= ADC_CR_ADEN;   				// enable ADC
    while(!(ADC1->ISR & ADC_ISR_ADRDY));    // wait for ADC to be ready
    while((ADC1->CR & ADC_CR_ADSTART));   	// wait for ADCstart to be 0.
}


// This function should return the value from the ADC
// conversion of the channel specified by the “channel” variable.
// Make sure to set the right bit in channel selection
// register and do not forget to start adc conversion.

uint16_t read_adc_channel(unsigned int channel) {
    ADC1->CHSELR = 0;
    ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));
    ADC1->CR |= ADC_CR_ADSTART;
    while(!(ADC1->ISR & ADC_ISR_EOC));
    return ADC1->DR;
}

void error();

ADC_HandleTypeDef hadc;

int main(void)
{
	HAL_Init();

	setup_gpio();
	setup_adc();
	BSP_EPD_Init();
	uint16_t raw;

	while(1) {
		raw = read_adc_channel(1);
		float outputV = (float)raw/(float)4096 * 3.3;

		char str[20];
		snprintf(str, 20, "raw: %hu; V: %d.%04d", raw, (int)outputV, (int)trunc((float)(outputV - (int)outputV) * 10000));
		BSP_EPD_DisplayStringAtLine(5, (uint8_t *)str);
		BSP_EPD_RefreshDisplay();
		HAL_Delay(2000);
	}
}

void error() {
	// Do something
	while(1) {

	}
}

/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32l0xx.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"
#include <stdio.h>

//void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void setup_gpio(){
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // enables clock to port A
	GPIOA->MODER |= 0x3 << GPIO_MODER_MODE4_Pos;               // sets PA4 to analog mode
}


// This function should enable the clock to ADC,
// turn on the clocks, wait for ADC to be ready.
void setup_adc() {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;     // enable the clock to ADC
    RCC->CR |= RCC_CR_HSION;     			// turn on clock
    while(!(RCC->CR & RCC_CR_HSIRDY));  	// wait for clock to be ready
    ADC1->CR |= ADC_CR_ADEN;   				// enable ADC
    while(!(ADC1->ISR & ADC_ISR_ADRDY));    // wait for ADC to be ready
    while((ADC1->CR & ADC_CR_ADSTART));   	// wait for ADCstart to be 0.
}


// This function should return the value from the ADC
// conversion of the channel specified by the “channel” variable.
// Make sure to set the right bit in channel selection
// register and do not forget to start adc conversion.

uint16_t read_adc_channel(unsigned int channel) {
    ADC1->CHSELR = 0;
    ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));
    ADC1->CR |= ADC_CR_ADSTART;
    while(!(ADC1->ISR & ADC_ISR_EOC));
    return ADC1->DR;
}

void error();

ADC_HandleTypeDef hadc;

int main(void)
{
	HAL_Init();

	setup_gpio();
	setup_adc();
	BSP_EPD_Init();
	uint16_t raw;

	while(1) {
		raw = read_adc_channel(1);
		float outputV = (float)raw/(float)4096 * 3.3;

		char str[20];
		snprintf(str, 20, "raw: %hu; V: %d.%04d", raw, (int)outputV, (int)trunc((float)(outputV - (int)outputV) * 10000));
		BSP_EPD_DisplayStringAtLine(5, (uint8_t *)str);
		BSP_EPD_RefreshDisplay();
		HAL_Delay(2000);
	}
}

void error() {
	// Do something
	while(1) {

	}
}

