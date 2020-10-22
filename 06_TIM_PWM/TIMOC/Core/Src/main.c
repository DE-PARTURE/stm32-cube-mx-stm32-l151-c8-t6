/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
	uint8_t ColorIndex = 1;  //颜色索引
	double Duty = 0;        //待计算的占空比
	double DutyTempR = 0;   //占空比临时值R
	double DutyTempG = 0;   //占空比临时值G
	double DutyTempB = 0;   //占空比临时值B
	double OperateTemp = 0; //计算产生的临时变量，用于使DutyTemp逼近Duty 
	//RGB数值列表
	uint8_t ValR[] = {255, 255, 255, 0  , 0  , 0  , 255};
	uint8_t ValG[] = {0  , 125, 255, 255, 255, 0  , 0  };
	uint8_t ValB[] = {0  , 0  , 0  , 0  , 255, 255, 255};
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	
	Duty = 100 - ((ValR[0] / 255) * 100);										//根据RGB数值计算出相应的占空比参数
	DutyTempR = Duty;
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, DutyTempR*(2000-1)/100);	//赋值
	Duty = 100 - ((ValG[0] / 255) * 100);										//根据RGB数值计算出相应的占空比参数
	DutyTempG = Duty;
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, DutyTempG*(2000-1)/100);	//赋值
	Duty = 100 - ((ValB[0] / 255) * 100);										//根据RGB数值计算出相应的占空比参数
	DutyTempB = Duty;
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, DutyTempB*(2000-1)/100);	//赋值
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//R
		Duty = 100 - ((ValR[ColorIndex] / 255) * 100);	//根据RGB数值计算出相应的占空比参数
		OperateTemp = Duty - DutyTempR;             	//计算总差值
		OperateTemp /= 15;                           	//差值分10次补偿给DutyTemp
		while (DutyTempR != Duty)
		{
				if (OperateTemp > 0 && DutyTempR > Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				if (OperateTemp < 0 && DutyTempR < Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				DutyTempR += OperateTemp;                	//差值补偿
				if(DutyTempR > 100)                    	//防溢出操作
						DutyTempR = 100;
				else if(DutyTempR < 0)
						DutyTempR = 0;
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, DutyTempR*(2000-1)/100);	//赋值
				HAL_Delay(100);                      //延时100ms
		}
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, DutyTempR*(2000-1)/100);//最终赋确定值，此时DutyTemp=Duty
		//G
		Duty = 100 - ((ValG[ColorIndex] / 255) * 100);	//根据RGB数值计算出相应的占空比参数
		OperateTemp = Duty - DutyTempG;             	//计算总差值
		OperateTemp /= 15;                           	//差值分10次补偿给DutyTemp
		while (DutyTempG != Duty)
		{
				if (OperateTemp > 0 && DutyTempG > Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				if (OperateTemp < 0 && DutyTempG < Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				DutyTempG += OperateTemp;                	//差值补偿
				if(DutyTempG > 100)                    	//防溢出操作
						DutyTempG = 100;
				else if(DutyTempG < 0)
						DutyTempG = 0;
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, DutyTempG*(2000-1)/100);	//赋值
				HAL_Delay(100);                      //延时100ms
		}
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, DutyTempG*(2000-1)/100);//最终赋确定值，此时DutyTemp=Duty
		//B
		Duty = 100 - ((ValB[ColorIndex] / 255) * 100);	//根据RGB数值计算出相应的占空比参数
		OperateTemp = Duty - DutyTempB;             	//计算总差值
		OperateTemp /= 15;                           	//差值分10次补偿给DutyTemp
		while (DutyTempB != Duty)
		{
				if (OperateTemp > 0 && DutyTempB > Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				if (OperateTemp < 0 && DutyTempB < Duty)	//解决因小数精度问题而无法满足循环解除条件的问题
						break;
				DutyTempB += OperateTemp;                	//差值补偿
				if(DutyTempB > 100)                    	//防溢出操作
						DutyTempB = 100;
				else if(DutyTempB < 0)
						DutyTempB = 0;
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, DutyTempB*(2000-1)/100);	//赋值
				HAL_Delay(100);                      //延时100ms
		}
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, DutyTempB*(2000-1)/100);//最终赋确定值，此时DutyTemp=Duty
		HAL_Delay(1000);
		 if(ColorIndex < 6)              //使颜色于红~紫轮流切换
        ColorIndex += 1;
    else
        ColorIndex = 0;

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
