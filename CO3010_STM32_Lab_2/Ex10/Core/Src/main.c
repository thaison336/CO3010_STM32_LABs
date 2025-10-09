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
#include "software_timer.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
int led_counter = 100;
int seg_counter = 50;
int active_digit = 0;
const int MAX_LED = 4;
int index_led = 0;
int hour = 15, minute = 59, second = 45;
int led_buffer [4] = {1 , 5 ,5 , 9};
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
	0b11111111,
    0b11100111,
	0b11011011,
	0b10000001,
	0b10111101,
	0b10111101,
	0b10111101,
	0b10111101
};
uint8_t row_map[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int);
void update7SEG(int);
void updateClockBuffer();
void updateLEDMatrix(int);
void shiftDownLEDMatrix();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;
void setTimer0(int duration){
	timer0_counter = duration /TIMER_CYCLE;
	timer0_flag = 0;
}
void timer_run(){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0) timer0_flag = 1;
	}
}
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
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, DOT_Pin, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(1000);
  int timer_led = 100;
  int timer_dot = 50;
  int timer_clock = 25;
  int timer_seg = 10;
  int timer_matrix = 20;
  int timer_shift = 10;
  while (1) {

	  if (timer_led <= 0){
		  HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
		  timer_led = 101;
	  }

	  if (timer_dot <= 0){
		  HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
		  timer_dot = 51;
	  }

	  if (timer_clock <= 0){
		  second++;
		  if (second >= 60){
			  second = 0;
			  minute++;
			  if (minute >= 60){
				  minute = 0;
				  hour++;
				  if (hour >= 24) hour = 0;
			  }
		  }
		  updateClockBuffer();
		  timer_clock = 20;
	  }

	  if (timer_seg <= 0){
		  update7SEG((index_led++) % MAX_LED);
		  timer_seg = 20;
	  }

	  if (timer_matrix <= 0){
	      updateLEDMatrix(index_led_matrix++);
	      if (index_led_matrix >= MAX_LED_MATRIX)
	      {
	    	  index_led_matrix = 0;
	    	  if (timer_shift <= 0){
	    	 		  shiftDownLEDMatrix();
	    	 		  timer_shift = 11;
	    	  }
	      }
	      else timer_matrix = 1;

	  }

	  if (timer0_flag == 1){
		  timer_led--;
		  timer_dot--;
		  timer_clock--;
		  timer_seg--;
		  timer_matrix--;
		  timer_shift--;
		  setTimer0(10);
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
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	timer_run();
}
void display7SEG(int num) {
    switch(num) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_SET);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_SET);
            break;

        case 2:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 4:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 5:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 6:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 7:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_SET);
            break;

        case 8:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        case 9:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_RESET);
            break;

        default:
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG5_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_SET);
            break;
    }
}

void update7SEG(int index) {
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[0]);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[1]);
            break;

        case 2:
            HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[2]);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[3]);
            break;
        default:
            break;
    }
}

void updateClockBuffer(){
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}



//void updateLEDMatrix(int index){
//    switch (index){
//        case 0:
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[0] << 8, GPIO_PIN_SET);
//            break;
//        case 1:
//            HAL_GPIO_WritePin(GPIOA, ENM1_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[1] << 8, GPIO_PIN_SET);
//            break;
//        case 2:
//            HAL_GPIO_WritePin(GPIOA, ENM2_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[2] << 8, GPIO_PIN_SET);
//            break;
//        case 3:
//            HAL_GPIO_WritePin(GPIOA, ENM3_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[3] << 8, GPIO_PIN_SET);
//            break;
//        case 4:
//            HAL_GPIO_WritePin(GPIOA, ENM4_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[4] << 8, GPIO_PIN_SET);
//            break;
//        case 5:
//            HAL_GPIO_WritePin(GPIOA, ENM5_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[5] << 8, GPIO_PIN_SET);
//            break;
//        case 6:
//            HAL_GPIO_WritePin(GPIOA, ENM6_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM7_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[6] << 8, GPIO_PIN_SET);
//            break;
//        case 7:
//            HAL_GPIO_WritePin(GPIOA, ENM7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOB, matrix_buffer[7] << 8, GPIO_PIN_SET);
//            break;
//        default:
//            break;
//    }
//}
void set_row (int num) {
	HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, !(row_map[num] & 1 << 0));
	HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, !(row_map[num] & 1 << 1));
	HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, !(row_map[num] & 1 << 2));
	HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, !(row_map[num] & 1 << 3));
	HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, !(row_map[num] & 1 << 4));
	HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, !(row_map[num] & 1 << 5));
	HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, !(row_map[num] & 1 << 6));
	HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, !(row_map[num] & 1 << 7));
}

void set_col(int num) {
	HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, (matrix_buffer[num] >> 7) & 1);
	HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, (matrix_buffer[num] >> 6) & 1);
	HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, (matrix_buffer[num] >> 5) & 1);
	HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, (matrix_buffer[num] >> 4) & 1);
	HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, (matrix_buffer[num] >> 3) & 1);
	HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, (matrix_buffer[num] >> 2) & 1);
	HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, (matrix_buffer[num] >> 1) & 1);
	HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, (matrix_buffer[num] >> 0) & 1);
}

void updateLEDMatrix(int index){
	set_row(index);
	set_col(index);
}
void shiftDownLEDMatrix(){
	for (int i = 0; i < MAX_LED_MATRIX; ++i) {
		row_map[i] = (row_map[i] << 1 | row_map[i] >> 7);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
