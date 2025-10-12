/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
<<<<<<< HEAD
#define LED_PA5_Pin GPIO_PIN_5
#define LED_PA5_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_6
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_7
#define LED_2_GPIO_Port GPIOA
#define SEG_a_Pin GPIO_PIN_0
#define SEG_a_GPIO_Port GPIOB
#define SEG_b_Pin GPIO_PIN_1
#define SEG_b_GPIO_Port GPIOB
#define SEG_c_Pin GPIO_PIN_2
#define SEG_c_GPIO_Port GPIOB
#define SEG_2c_Pin GPIO_PIN_10
#define SEG_2c_GPIO_Port GPIOB
#define SEG_2d_Pin GPIO_PIN_11
#define SEG_2d_GPIO_Port GPIOB
#define SEG_2e_Pin GPIO_PIN_12
#define SEG_2e_GPIO_Port GPIOB
#define SEG_2f_Pin GPIO_PIN_13
#define SEG_2f_GPIO_Port GPIOB
#define SEG_2g_Pin GPIO_PIN_14
#define SEG_2g_GPIO_Port GPIOB
#define LED_3_Pin GPIO_PIN_8
#define LED_3_GPIO_Port GPIOA
#define LED_4_Pin GPIO_PIN_9
#define LED_4_GPIO_Port GPIOA
#define LED_5_Pin GPIO_PIN_10
#define LED_5_GPIO_Port GPIOA
#define LED_6_Pin GPIO_PIN_11
#define LED_6_GPIO_Port GPIOA
#define SEG_d_Pin GPIO_PIN_3
#define SEG_d_GPIO_Port GPIOB
#define SEG_e_Pin GPIO_PIN_4
#define SEG_e_GPIO_Port GPIOB
#define SEG_f_Pin GPIO_PIN_5
#define SEG_f_GPIO_Port GPIOB
#define SEG_g_Pin GPIO_PIN_6
#define SEG_g_GPIO_Port GPIOB
#define SEG_2a_Pin GPIO_PIN_8
#define SEG_2a_GPIO_Port GPIOB
#define SEG_2b_Pin GPIO_PIN_9
#define SEG_2b_GPIO_Port GPIOB
=======
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_6
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_7
#define EN1_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_0
#define SEG0_GPIO_Port GPIOB
#define SEG1_Pin GPIO_PIN_1
#define SEG1_GPIO_Port GPIOB
#define SEG2_Pin GPIO_PIN_2
#define SEG2_GPIO_Port GPIOB
#define SEG3_Pin GPIO_PIN_3
#define SEG3_GPIO_Port GPIOB
#define SEG4_Pin GPIO_PIN_4
#define SEG4_GPIO_Port GPIOB
#define SEG5_Pin GPIO_PIN_5
#define SEG5_GPIO_Port GPIOB
#define SEG6_Pin GPIO_PIN_6
#define SEG6_GPIO_Port GPIOB
>>>>>>> Ex1

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
