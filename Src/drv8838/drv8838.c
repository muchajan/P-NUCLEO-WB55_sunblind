/*
 * drv8838.c
 *
 *  Created on: 9. 6. 2020
 *      Author: janmu
 */

#include "drv8388.h"
#include "stm32wbxx_hal.h"

static LPTIM_HandleTypeDef hlptim1;

DRV8838_STATUS
Drv8838_Init (void)
{

//	hlptim1.Instance 			 = LPTIM1;
//	hlptim1.Init.Clock.Source    = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
//	hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
//	hlptim1.Init.Trigger.Source  = LPTIM_TRIGSOURCE_SOFTWARE;
//	hlptim1.Init.OutputPolarity  = LPTIM_OUTPUTPOLARITY_HIGH;
//	hlptim1.Init.UpdateMode 	 = LPTIM_UPDATE_IMMEDIATE;
//	hlptim1.Init.CounterSource   = LPTIM_COUNTERSOURCE_INTERNAL;
//	hlptim1.Init.Input1Source    = LPTIM_INPUT1SOURCE_GPIO;
//	hlptim1.Init.Input2Source    = LPTIM_INPUT2SOURCE_GPIO;
//	if (HAL_LPTIM_Init(&hlptim1) != HAL_OK) {
//		return DRV8838_ERROR;
//	}

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);

  return DRV8838_OK;
}

DRV8838_STATUS
Drv8838_Start (DRV8838_DIR eDir)
{
//	 if(HAL_LPTIM_PWM_Start(&hlptim1, 99, 49) != HAL_OK)
//	 {
//		 return DRV8838_ERROR;
//	 }

  if (eDir == DRV8838_DIR_CW)
    {
      HAL_GPIO_WritePin (GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    }
  else
    {
      HAL_GPIO_WritePin (GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
    }

  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

  return DRV8838_OK;
}

DRV8838_STATUS
Drv8838_Stop ()
{
//	  if (HAL_LPTIM_PWM_Stop(&hlptim1) != HAL_OK)
//	  {
//	    return DRV8838_ERROR;
//	  }

  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);

  return DRV8838_OK;
}
