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

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
static void MX_ADC_Init(void);
void error();

ADC_HandleTypeDef hadc;

int main(void)
{
	HAL_Init();
	BSP_EPD_Init();

	MX_ADC_Init();

	while(1) {
		if (HAL_ADC_Start(&hadc) != HAL_OK)
		{
			error();
		}
		if (HAL_ADC_PollForConversion(&hadc, 100) != HAL_OK) {
			error();
		}

		uint16_t raw = HAL_ADC_GetValue(&hadc);
		float outputV = (float)raw/(float)4096 * 3.3;

		char str[20];
		snprintf(str, 20, "raw: %hu; V: %d.%04d", raw, (int)outputV, (int)trunc((float)(outputV - (int)outputV) * 10000));
		BSP_EPD_DisplayStringAtLine(5, (uint8_t *)str);
		BSP_EPD_RefreshDisplay();

		HAL_ADC_Stop(&hadc);
		HAL_Delay(2000);
	}
}

static void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    error();
  }

  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
	  error();
  }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if (hadc->Instance == ADC1) {
		__HAL_RCC_ADC1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

void error() {
	// Do something
	while(1) {

	}
}
