/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
<<<<<<< HEAD
#define red 1
#define yellow 2
#define green 3
=======
>>>>>>> Ex1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
<<<<<<< HEAD
void SET_LED(int color);
void RESET_LED(int color);
void TOGGLE_LED(int color);
void display7SEG(int num);
void SET_LED2(int color);
void RESET_LED2(int color);
void TOGGLE_LED2(int color);
void display7SEG_2(int num);
=======

>>>>>>> Ex1
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
//  HAL_TIM_Base_Start_IT(&htim2);
<<<<<<< HEAD
=======
  int state = 0;
  int counter = 0;
>>>>>>> Ex1
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
<<<<<<< HEAD
  int state_ew = 0;
  int counter_ew = 0;

  int state_ns = 0;
  int counter_ns = 0;

=======
>>>>>>> Ex1
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
<<<<<<< HEAD
	  switch(state_ew) {
	          case 0:
	              RESET_LED(red);
	              SET_LED(green);
	              SET_LED(yellow);
	              counter_ew = 5;
	              state_ew = green;
	              break;

	          case green:
	              display7SEG(counter_ew--);
	              if(counter_ew <= 0) {
	                  TOGGLE_LED(red);
	                  TOGGLE_LED(green);
	                  counter_ew = 3;
	                  state_ew = yellow;
	              }
	              break;

	          case yellow:
	              display7SEG(counter_ew-- );
	              if(counter_ew <= 0) {
	                  TOGGLE_LED(green);
	                  TOGGLE_LED(yellow);
	                  counter_ew = 2;
	                  state_ew = red;
	              }
	              break;

	          case red:
	              display7SEG(counter_ew-- );
	              if(counter_ew <= 0) {
	                  TOGGLE_LED(yellow);
	                  TOGGLE_LED(red);
	                  counter_ew = 5;
	                  state_ew = green;
	              }
	              break;
	      }

	      switch(state_ns) {
	          case 0:
	              RESET_LED2(green);
	              SET_LED2(red);
	              SET_LED2(yellow);
	              counter_ns = 3;
	              state_ns = yellow;
	              break;

	          case yellow:
	              display7SEG_2(counter_ns--);
	              if(counter_ns <= 0) {
	                  TOGGLE_LED2(yellow);
	                  TOGGLE_LED2(green);
	                  counter_ns = 2;
	                  state_ns = red;
	              }
	              break;

	          case red:
	              display7SEG_2(counter_ns--);
	              if(counter_ns <= 0) {
	                  TOGGLE_LED2(red);
	                  TOGGLE_LED2(yellow);
	                  counter_ns = 5;
	                  state_ns = green;
	              }
	              break;

	          case green:
	              display7SEG_2(counter_ns--);
	              if(counter_ns <= 0) {
	                  TOGGLE_LED2(red);
	                  TOGGLE_LED2(green);
	                  counter_ns = 3;
	                  state_ns = yellow;
	              }
	              break;
	      }
	  //	  if (counter >= 10) counter = 0;
	  //	  display7SEG(counter++);
	  	  HAL_GPIO_TogglePin(LED_PA5_GPIO_Port, LED_PA5_Pin);
	  	  HAL_Delay(1000);
=======
	  switch(state) {
	  case 0: // INIT
		  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, 1);
		  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, 1);
		  counter = 2;
		  state = 1;
		  break;
	  case 1: // RED
		  --counter;
		  if (counter <= 0) {
		 	HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, 0);
		 	HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, 1);
		 	counter = 2;
		 	state = 2;
		  }
		  break;
	  case 2: // YELLOW
		  --counter;
		  if (counter <= 0) {
			 HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, 1);
			 HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, 0);
			 counter = 2;
			 state = 1;
		  }
	  	  break;
	  default:
	  	  break;
	  }
	  HAL_Delay(1000);
>>>>>>> Ex1
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 79;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
<<<<<<< HEAD
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_PA5_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_a_Pin|SEG_b_Pin|SEG_c_Pin|SEG_2c_Pin
                          |SEG_2d_Pin|SEG_2e_Pin|SEG_2f_Pin|SEG_2g_Pin
                          |SEG_d_Pin|SEG_e_Pin|SEG_f_Pin|SEG_g_Pin
                          |SEG_2a_Pin|SEG_2b_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_PA5_Pin LED_1_Pin LED_2_Pin LED_3_Pin
                           LED_4_Pin LED_5_Pin LED_6_Pin */
  GPIO_InitStruct.Pin = LED_PA5_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin;
=======

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin LED_YELLOW_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin;
>>>>>>> Ex1
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

<<<<<<< HEAD
  /*Configure GPIO pins : SEG_a_Pin SEG_b_Pin SEG_c_Pin SEG_2c_Pin
                           SEG_2d_Pin SEG_2e_Pin SEG_2f_Pin SEG_2g_Pin
                           SEG_d_Pin SEG_e_Pin SEG_f_Pin SEG_g_Pin
                           SEG_2a_Pin SEG_2b_Pin */
  GPIO_InitStruct.Pin = SEG_a_Pin|SEG_b_Pin|SEG_c_Pin|SEG_2c_Pin
                          |SEG_2d_Pin|SEG_2e_Pin|SEG_2f_Pin|SEG_2g_Pin
                          |SEG_d_Pin|SEG_e_Pin|SEG_f_Pin|SEG_g_Pin
                          |SEG_2a_Pin|SEG_2b_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
//  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_PA5_Pin, GPIO_PIN_SET);
=======
  /* USER CODE BEGIN MX_GPIO_Init_2 */
//  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
>>>>>>> Ex1
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
<<<<<<< HEAD
//int counter = 100;
=======
//int counter = 200;
>>>>>>> Ex1
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	if (counter > 0) {
//		counter--;
//		if (counter <= 0) {
<<<<<<< HEAD
//			counter = 100;
//			HAL_GPIO_TogglePin(LED_PA5_GPIO_Port, LED_PA5_Pin);
//		}
//	}
//}
void SET_LED(int color) {
	switch(color) {
	case red:
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, 1);
		break;
	case yellow:
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, 1);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA, LED_3_Pin, 1);
		break;
	}
}

void RESET_LED(int color) {
	switch(color) {
	case red:
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, 0);
		break;
	case yellow:
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, 0);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA, LED_3_Pin, 0);
		break;
	}
}
void TOGGLE_LED(int color) {
	switch(color) {
	case red:
		HAL_GPIO_TogglePin(GPIOA, LED_1_Pin);
		break;
	case yellow:
		HAL_GPIO_TogglePin(GPIOA, LED_2_Pin);
		break;
	case green:
		HAL_GPIO_TogglePin(GPIOA, LED_3_Pin);
		break;
	}
}
void display7SEG(int num) {
    switch(num) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_SET);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_SET);
            break;

        case 2:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_SET);
            break;

        case 8:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        case 9:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_RESET);
            break;

        default:
            HAL_GPIO_WritePin(GPIOB, SEG_a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_c_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_g_Pin, GPIO_PIN_SET);
            break;
    }
}
void display7SEG_2(int num) {
    switch(num) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_SET);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_SET);
            break;

        case 2:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_SET);
            break;

        case 8:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        case 9:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_RESET);
            break;

        default:
            HAL_GPIO_WritePin(GPIOB, SEG_2a_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2b_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2c_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2d_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2e_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2f_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG_2g_Pin, GPIO_PIN_SET);
            break;
    }
}
void SET_LED2(int color) {
	switch(color) {
	case red:
		HAL_GPIO_WritePin(GPIOA, LED_4_Pin, 1);
		break;
	case yellow:
		HAL_GPIO_WritePin(GPIOA, LED_5_Pin, 1);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA, LED_6_Pin, 1);
		break;
	}
}

void RESET_LED2(int color) {
	switch(color) {
	case red:
		HAL_GPIO_WritePin(GPIOA, LED_4_Pin, 0);
		break;
	case yellow:
		HAL_GPIO_WritePin(GPIOA, LED_5_Pin, 0);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA, LED_6_Pin, 0);
		break;
	}
}

void TOGGLE_LED2(int color) {
	switch(color) {
	case red:
		HAL_GPIO_TogglePin(GPIOA, LED_4_Pin);
		break;
	case yellow:
		HAL_GPIO_TogglePin(GPIOA, LED_5_Pin);
		break;
	case green:
		HAL_GPIO_TogglePin(GPIOA, LED_6_Pin);
		break;
	}
}


=======
//			counter = 200;
//			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
//			HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
//		}
//	}
//}
>>>>>>> Ex1
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
#ifdef USE_FULL_ASSERT
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
