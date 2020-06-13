/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "usart.h"
#include "usb.h"
#include "gpio.h"
#include "drv8838/drv8388.h"
#include "buttons/buttons.h"
#include "sunblind/sunblind.h"

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
void
SystemClock_Config (void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int
main (void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init ();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config ();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init ();
  MX_TIM2_Init ();
  MX_USART1_UART_Init ();
  MX_USB_PCD_Init ();
  /* USER CODE BEGIN 2 */

  LL_TIM_CC_EnableChannel (TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel (TIM2, LL_TIM_CHANNEL_CH2);
  LL_TIM_SetAutoReload (TIM2, 0xFFFFFFFF);
  LL_TIM_EnableCounter (TIM2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  Buttons_Init();
  Sunblind_Init();

  Buttons_SW1_SetPressedCallback(Sunblind_GoUp);
  Buttons_SW1_SetReleasedCallback(Sunblind_Stop);
  Buttons_SW2_SetPressedCallback(Sunblind_GoDown);
  Buttons_SW2_SetReleasedCallback(Sunblind_Stop);

  while (1)
    {
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */

      Buttons_Run();

    }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void
SystemClock_Config (void)
{
  LL_FLASH_SetLatency (LL_FLASH_LATENCY_1);
  if (LL_FLASH_GetLatency () != LL_FLASH_LATENCY_1)
    {
      Error_Handler ();
    }

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable ();
  while (LL_RCC_HSE_IsReady () != 1)
    {
    };

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable ();
  while (LL_RCC_HSI_IsReady () != 1)
    {
    };

  /* MSI configuration and activation */
  LL_RCC_MSI_Enable ();
  while (LL_RCC_MSI_IsReady () != 1)
    {
    };

  LL_RCC_MSI_EnablePLLMode ();
  LL_PWR_EnableBkUpAccess ();
  LL_RCC_LSE_SetDriveCapability (LL_RCC_LSEDRIVE_LOW);
  LL_RCC_LSE_Enable ();

  /* Wait till LSE is ready */
  while (LL_RCC_LSE_IsReady () != 1)
    {
    };

  LL_RCC_PLLSAI1_ConfigDomain_48M (LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 24,
				   LL_RCC_PLLSAI1Q_DIV_2);
  LL_RCC_PLLSAI1_Enable ();
  LL_RCC_PLLSAI1_EnableDomain_48M ();

  /* Wait till PLLSAI1 is ready */
  while (LL_RCC_PLLSAI1_IsReady () != 1)
    {
    };

  /* Sysclk activation on the HSE */
  /* Set CPU1 prescaler*/
  LL_RCC_SetAHBPrescaler (LL_RCC_SYSCLK_DIV_1);

  /* Set CPU2 prescaler*/
  LL_C2_RCC_SetAHBPrescaler (LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetSysClkSource (LL_RCC_SYS_CLKSOURCE_HSE);
  while (LL_RCC_GetSysClkSource () != LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
    {
    };

  /* Set AHB SHARED prescaler*/
  LL_RCC_SetAHB4Prescaler (LL_RCC_SYSCLK_DIV_1);

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler (LL_RCC_APB1_DIV_1);

  /* Set APB2 prescaler*/
  LL_RCC_SetAPB2Prescaler (LL_RCC_APB2_DIV_1);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock (32000000);
  LL_RCC_SetUSARTClockSource (LL_RCC_USART1_CLKSOURCE_PCLK2);
  LL_RCC_SetUSBClockSource (LL_RCC_USB_CLKSOURCE_PLLSAI1);
  LL_RCC_SetSMPSClockSource (LL_RCC_SMPS_CLKSOURCE_HSI);
  LL_RCC_SetSMPSPrescaler (LL_RCC_SMPS_DIV_1);
  LL_RCC_SetRFWKPClockSource (LL_RCC_RFWKP_CLKSOURCE_NONE);
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void
Error_Handler (void)
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
void
assert_failed (uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
