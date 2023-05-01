/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fdcan.h"
#include "fmac.h"
#include "hrtim.h"
#include "usart.h"
#include "opamp.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "function.h"
#include "power_ctrl.h"
#include "IIR_FIlter.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "CAN_receive.h"
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

/* volatile is below for debug convenience */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
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
  MX_DMA_Init();
  MX_FDCAN2_Init();
  MX_LPUART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_OPAMP2_Init();
  MX_OPAMP3_Init();
  MX_ADC4_Init();
  MX_ADC5_Init();
  MX_OPAMP5_Init();
  MX_OPAMP6_Init();
  MX_SPI3_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_HRTIM1_Init();
  MX_OPAMP1_Init();
  MX_FMAC_Init();
  MX_FDCAN1_Init();
  /* USER CODE BEGIN 2 */

    /*OD pin down to disable abnormal operations*/
    HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_RESET);

    /*open peripheral driver*/
    OPAMP_Start();
    ADC_Calib_Start();
    TIM1_PWM_Init();
    ips114_init();
    can_filter_init();
    HAL_FMAC_FilterConfig_my();
    power_init();

    /*initial finished*/
    printf("\n\r init complete\n\r");
    htim1.Instance->CCR1 = 0;
    htim1.Instance->CCR2 = 0;
    htim1.Instance->CCR3 = 0;
    htim1.Instance->CCR4 = 0;

    /*open timer interrupt*/
    HAL_TIM_Base_Start_IT(&htim2); //5mS interrupt
    HRTIM_Init();

    /*calibration function, calibration is defined in main.h*/
#if calibration == 1
//    HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_SET);
    HRTIM_DMA_Buffer[0] = (uint16_t)(0.95 * HRTIMB_Period);//BUCK duty
    HRTIM_DMA_Buffer[1] = (uint16_t)(0.95 * HRTIMB_Period) >> 1;//ADC sampling trigger
    HRTIM_DMA_Buffer[2] = MIN_REG_VALUE;//Boost duty
    HRTIM_DMA_Buffer[3] = (uint16_t)(0.96 * HRTIMA_Period);
#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        printf("power_in=%f\r\n", in.P);
        printf("v_in=%f\r\n", in.V);
        printf("c_in=%f\r\n", in.I);
        printf("v_cap=%f\r\n", cap.V);
        printf("c_cap=%f\r\n", cap.I);
        printf("c_chassis=%f\r\n", c_chassis.value_elec);
//        printf("full_bridge_in=%f\r\n", full_bridge_in.I);
        printf("\r\n");

//        CAN_cmd_chassis(5000,5000,5000,5000);

//        if (IPSShowCnt > 60) //300m flash once ips
//        {
//            IPSShowCnt = 0;
//            ips_usrdisplay();
//        }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the LPUART1 and Loop until the end of transmission */
    HAL_UART_Transmit(&hlpuart1, (uint8_t *) &ch, 1, 0xFFFF);

    return ch;
}

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
        /*turn on beep & led max light*/
        htim1.Instance->CCR1 = 3400;
        htim1.Instance->CCR2 = 3400;
        htim1.Instance->CCR3 = 0;
        htim1.Instance->CCR4 = 0;

        /*shut down MOS*/
        HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
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
