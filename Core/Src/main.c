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
#include "can.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Dragon_CANbus.h"
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
void CANcrit_func_Reset(uint8_t aPayload[])
{
	HAL_NVIC_SystemReset();
}
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
  MX_CAN1_Init();
  MX_USART2_UART_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */
  CANbus_Init(&hcan1);
    CANbus_FilterInit();
     if (HAL_CAN_Start(&hcan1) != HAL_OK){
       Error_Handler(); /* Start Error */
     }
 SET_BIT(CAN1->MCR, CAN_MCR_ABOM); /*Set the Automatic buss-off management*/
 CAN1bus_SendData(CANcrit_ID_Pedal_status, 1, (CAN_RTR_DATA | CANdef_ALLMSG), 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

#ifndef _CAN1def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN1bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN1def_ONLY_INTERRUPT_MODE
#ifdef _DUAL_CAN_ACTIVATE
#ifndef _CAN2def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan3, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN2bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN2def_ONLY_INTERRUPT_MODE
#endif  //_DUAL_CAN_ACTIVATE


	  static uint16_t button_status = 0;
	  button_status = HAL_GPIO_ReadPin(board_button_GPIO_Port, board_button_Pin);

	  if (!button_status)
	  {
		  uint8_t data[] = {1};
		  CAN1bus_SendData(CANcrit_ID_Pedal_status, 1, (CAN_RTR_DATA | CANdef_ALLMSG), data);
		  uint32_t last_time = 0;
		  while(1)
		  {
#ifndef _CAN1def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN1bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN1def_ONLY_INTERRUPT_MODE
#ifdef _DUAL_CAN_ACTIVATE
#ifndef _CAN2def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan3, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN2bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN2def_ONLY_INTERRUPT_MODE
#endif  //_DUAL_CAN_ACTIVATE

			  uint16_t delay = 100;
			  if(HAL_GetTick() >= last_time + delay)
			  {
				  HAL_ADC_Start(&hadc3);
				  uint16_t conversion_done = 1;
				  while(conversion_done) /*checks till the conversion is done*/
				  {
					  conversion_done = HAL_ADC_PollForConversion(&hadc3, 10);
				  }
				  uint8_t adc_value = HAL_ADC_GetValue(&hadc3);
				  HAL_ADC_Stop(&hadc3);
				  uint8_t pedal_pos_data[] = {adc_value, 0, 0};
				  last_time = HAL_GetTick();
				  CAN1bus_SendData(CANcrit_ID_Pedal_position, 3, (CAN_RTR_DATA | CANdef_ALLMSG), pedal_pos_data);
			  }

		  }
	  }

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_8;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
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
