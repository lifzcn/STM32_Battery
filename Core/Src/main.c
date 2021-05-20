/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ds18b20.h"
#include "oled.h"
#include "stdio.h"
#include "addhot.h"
#include "addwind.h"
#include "switch.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int i = 0;
	int x = 0;
	int y = 0;
	float Temprature_Value_1;
	float Temprature_Value_2;
	
	int Temprature_Value_1_Integer;
	int Temprature_Value_1_Decimal;
	int Temprature_Value_2_Integer;
	int Temprature_Value_2_Decimal;
	
	float Temprature_Threshold_Low = 5;
	float Temprature_Threshold_High = 20;
	
	uint16_t AD_Value = 0;
	float Vol_Value = 0;
	float Cur_Value = 0;
	
	int Vol_Value_Integer;
	int Vol_Value_Decimal;
	int Cur_Value_Integer;
	int Cur_Value_Decimal;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OLED_Clear();
	
	OLED_ShowChinese(x, y, 2);
	OLED_ShowChinese(x + 1 * 16, y, 3);
	OLED_ShowChinese(x + 2 * 16, y, 0);
	OLED_ShowChinese(x + 3 * 16, y, 1);
	OLED_ShowChar(x + 4 * 16, y, ':', 16);
	
	
	OLED_ShowChinese(x, y + 1 * 2, 4);
	OLED_ShowChinese(x + 1 * 16, y + 1 * 2, 5);
	OLED_ShowChinese(x + 2 * 16, y + 1 * 2, 0);
	OLED_ShowChinese(x + 3 * 16, y + 1 * 2, 1);
	OLED_ShowChar(x + 4 * 16, y + 1 * 2, ':', 16);
	
	OLED_ShowChinese(x, y + 2 * 2, 4);
	OLED_ShowChinese(x + 1 * 16, y + 2 * 2, 6);
	OLED_ShowChinese(x + 2 * 16, y + 2 * 2, 8);
	OLED_ShowChar(x + 3 * 16, y + 2 * 2, ':', 16);
	
	OLED_ShowChinese(x, y + 3 * 2, 4);
	OLED_ShowChinese(x + 1 * 16, y + 3 * 2, 7);
	OLED_ShowChinese(x + 2 * 16, y + 3 * 2, 8);
	OLED_ShowChar(x + 3 * 16, y + 3 * 2, ':', 16);
	
	while(DS18B20_1_Init() && DS18B20_2_Init())
	{
		printf("DS18B20接入失败，请重试!\r\n");
		HAL_Delay(500);
	}
	printf("DS18B20接入成功!\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		i += 1;
		
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		
		if(i % 2 == 0)
		{
			Temprature_Value_1 = DS18B20_1_GetTemperture();
			Temprature_Value_2 = DS18B20_2_GetTemperture();
			
			Temprature_Value_1_Integer = (int)Temprature_Value_1;
			Temprature_Value_1_Decimal = 10 * (Temprature_Value_1 - (int)Temprature_Value_1);
			
			Temprature_Value_2_Integer = (int)Temprature_Value_2;
			Temprature_Value_2_Decimal = 10 * (Temprature_Value_2 - (int)Temprature_Value_2);
			
			AD_Value = HAL_ADC_GetValue(&hadc1);
			Vol_Value = AD_Value*(3.3/4096);
			Cur_Value = Vol_Value / 10;
			
			Vol_Value_Integer = (int)Vol_Value;
			Vol_Value_Decimal = 100 * (Vol_Value - (int)Vol_Value);
			
			Cur_Value_Integer = (int)Cur_Value;
			Cur_Value_Decimal = 100 * (Cur_Value - (int)Cur_Value);
			
			printf("======================\r\n");
			printf("环境温度为：%.1fC\r\n",Temprature_Value_1);
			printf("电池温度为：%.1fC\r\n",Temprature_Value_2);
			printf("ADC采集值为: %d\r\n",AD_Value);
			printf("电压值为: %.2fV\r\n",Vol_Value);
			printf("电流值为: %.2fA\r\n",Cur_Value);
			printf("======================\r\n");
		}
		
		OLED_ShowNum(x + 9 * 8, y, Temprature_Value_1_Integer, 2, 16);
		OLED_ShowChar(x + 11 * 8, y, '.', 16);
		OLED_ShowNum(x + 12 * 8, y, Temprature_Value_1_Decimal, 1, 16);
		OLED_ShowChar(x + 13 * 8, y, 'C', 16);
		OLED_ShowNum(x + 9 * 8, y + 1 * 2, Temprature_Value_2_Integer, 2, 16);
		OLED_ShowChar(x + 11 * 8, y + 1 * 2, '.', 16);
		OLED_ShowNum(x + 12 * 8, y + 1 * 2, Temprature_Value_2_Decimal, 1, 16);
		OLED_ShowChar(x + 13 * 8, y + 1 * 2, 'C', 16);
		OLED_ShowNum(x + 7 * 8, y + 2 * 2, Vol_Value_Integer, 1, 16);
		OLED_ShowChar(x + 8 * 8, y + 2 * 2, '.', 16);
		OLED_ShowNum(x + 9 * 8, y + 2 * 2, Vol_Value_Decimal, 2, 16);
		OLED_ShowChar(x + 11 * 8, y + 2 * 2, 'V', 16);
		OLED_ShowNum(x + 7 * 8, y + 3 * 2, Cur_Value_Integer, 1, 16);
		OLED_ShowChar(x + 8 * 8, y + 3 * 2, '.', 16);
		OLED_ShowNum(x + 9 * 8, y + 3 * 2, Cur_Value_Decimal, 2, 16);
		OLED_ShowChar(x + 11 * 8, y + 3 * 2, 'A', 16);
		
		if(Temprature_Value_1 >= Temprature_Threshold_High || Temprature_Value_2 >= Temprature_Threshold_High)
		{
			Disconnect();
			AddWind();
		}
		else if(Temprature_Value_2 <= Temprature_Threshold_Low || Temprature_Value_2 <= Temprature_Threshold_Low)
		{
			AddHot();
		}
		else
		{
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);
		}

		HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
