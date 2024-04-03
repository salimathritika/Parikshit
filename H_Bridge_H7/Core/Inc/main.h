/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BIN2_3_Pin GPIO_PIN_8
#define BIN2_3_GPIO_Port GPIOF
#define BIN1_2_Pin GPIO_PIN_2
#define BIN1_2_GPIO_Port GPIOA
#define BIN2_2_Pin GPIO_PIN_3
#define BIN2_2_GPIO_Port GPIOA
#define AIN2_3_Pin GPIO_PIN_0
#define AIN2_3_GPIO_Port GPIOB
#define BIN1_3_Pin GPIO_PIN_1
#define BIN1_3_GPIO_Port GPIOB
#define nSleep_1_Pin GPIO_PIN_7
#define nSleep_1_GPIO_Port GPIOE
#define nSleep_2_Pin GPIO_PIN_8
#define nSleep_2_GPIO_Port GPIOE
#define nSleep_3_Pin GPIO_PIN_9
#define nSleep_3_GPIO_Port GPIOE
#define nFault_1_Pin GPIO_PIN_10
#define nFault_1_GPIO_Port GPIOE
#define nFault_2_Pin GPIO_PIN_11
#define nFault_2_GPIO_Port GPIOE
#define nFault_3_Pin GPIO_PIN_12
#define nFault_3_GPIO_Port GPIOE
#define AIN1_1_Pin GPIO_PIN_14
#define AIN1_1_GPIO_Port GPIOB
#define AIN2_1_Pin GPIO_PIN_15
#define AIN2_1_GPIO_Port GPIOB
#define BIN1_1_Pin GPIO_PIN_12
#define BIN1_1_GPIO_Port GPIOD
#define BIN2_1_Pin GPIO_PIN_13
#define BIN2_1_GPIO_Port GPIOD
#define AIN1_2_Pin GPIO_PIN_14
#define AIN1_2_GPIO_Port GPIOD
#define AIN2_2_Pin GPIO_PIN_15
#define AIN2_2_GPIO_Port GPIOD
#define AIN1_3_Pin GPIO_PIN_7
#define AIN1_3_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
