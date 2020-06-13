/*
 * encoder.c
 *
 *  Created on: 13. 6. 2020
 *      Author: janmu
 */

#include "stm32wbxx_ll_tim.h"

void
Encoder_Init (void)
{
  LL_TIM_CC_EnableChannel (TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel (TIM2, LL_TIM_CHANNEL_CH2);
  LL_TIM_SetAutoReload (TIM2, 0xFFFFFFFF);
  LL_TIM_EnableCounter (TIM2);

}
