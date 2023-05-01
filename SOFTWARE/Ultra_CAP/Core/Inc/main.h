/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "arm_math.h"
#include "struct_typedef.h"
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
#define ccmram_enable (1)
#if ccmram_enable==1
#define CCMRAM __attribute__((section("ccmram")))
#endif
#if ccmram_enable==0
#define CCMRAM /**/
#endif
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HRTIMB_Period 27200
#define HRTIMA_Period 27200
#define HRTIMMaster_Period 27200
#define Beep_Pin GPIO_PIN_0
#define Beep_GPIO_Port GPIOC
#define RGB_R_Pin GPIO_PIN_1
#define RGB_R_GPIO_Port GPIOC
#define RGB_G_Pin GPIO_PIN_2
#define RGB_G_GPIO_Port GPIOC
#define RGB_B_Pin GPIO_PIN_3
#define RGB_B_GPIO_Port GPIOC
#define c_in_Pin GPIO_PIN_1
#define c_in_GPIO_Port GPIOA
#define EC11_A_Pin GPIO_PIN_4
#define EC11_A_GPIO_Port GPIOA
#define EC11_B_Pin GPIO_PIN_5
#define EC11_B_GPIO_Port GPIOA
#define EC11_K_Pin GPIO_PIN_6
#define EC11_K_GPIO_Port GPIOA
#define c_cap_Pin GPIO_PIN_7
#define c_cap_GPIO_Port GPIOA
#define c_chassis_Pin GPIO_PIN_0
#define c_chassis_GPIO_Port GPIOB
#define IPS114_REST_Pin GPIO_PIN_11
#define IPS114_REST_GPIO_Port GPIOB
#define v_in_Pin GPIO_PIN_12
#define v_in_GPIO_Port GPIOB
#define IPS114_SCL_Pin GPIO_PIN_13
#define IPS114_SCL_GPIO_Port GPIOB
#define v_cap_Pin GPIO_PIN_14
#define v_cap_GPIO_Port GPIOB
#define IPS114_SDA_Pin GPIO_PIN_15
#define IPS114_SDA_GPIO_Port GPIOB
#define IPS114_DC_Pin GPIO_PIN_6
#define IPS114_DC_GPIO_Port GPIOC
#define IPS114_CS_Pin GPIO_PIN_7
#define IPS114_CS_GPIO_Port GPIOC
#define IPS114_BL_Pin GPIO_PIN_8
#define IPS114_BL_GPIO_Port GPIOC
#define R_OD_Pin GPIO_PIN_9
#define R_OD_GPIO_Port GPIOC
#define L_OD_Pin GPIO_PIN_9
#define L_OD_GPIO_Port GPIOA
#define GYRO_SCK_Pin GPIO_PIN_10
#define GYRO_SCK_GPIO_Port GPIOC
#define GYRO_MISO_Pin GPIO_PIN_11
#define GYRO_MISO_GPIO_Port GPIOC
#define GYRO_MOSI_Pin GPIO_PIN_12
#define GYRO_MOSI_GPIO_Port GPIOC
#define GYRO_CS_Pin GPIO_PIN_2
#define GYRO_CS_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
#define calibration (0) //calibration function
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
