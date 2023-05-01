/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    opamp.h
  * @brief   This file contains all the function prototypes for
  *          the opamp.c file
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
#ifndef __OPAMP_H__
#define __OPAMP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern OPAMP_HandleTypeDef hopamp1;

extern OPAMP_HandleTypeDef hopamp2;

extern OPAMP_HandleTypeDef hopamp3;

extern OPAMP_HandleTypeDef hopamp5;

extern OPAMP_HandleTypeDef hopamp6;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_OPAMP1_Init(void);
void MX_OPAMP2_Init(void);
void MX_OPAMP3_Init(void);
void MX_OPAMP5_Init(void);
void MX_OPAMP6_Init(void);

/* USER CODE BEGIN Prototypes */
void OPAMP_Start(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __OPAMP_H__ */

