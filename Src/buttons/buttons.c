/*
 * buttons.c
 *
 *  Created on: 10. 6. 2020
 *      Author: janmu
 */

#include "stm32wbxx_hal.h"
#include "buttons.h"

static const uint32_t SW_DEBOUNCE_TIMEOUT = 100;
static uint32_t SW1_timestamp;

static uint32_t sample_timestamp;

static BUTTONS_STATUS SW1_lastState;
static BUTTONS_STATUS SW2_lastState;
static BUTTONS_STATUS SW3_lastState;

static BUTTONS_CALLBACK SW1_pressedCallback;
static BUTTONS_CALLBACK SW1_releasedCallback;

static BUTTONS_CALLBACK SW2_pressedCallback;
static BUTTONS_CALLBACK SW2_releasedCallback;

static BUTTONS_CALLBACK SW3_pressedCallback;
static BUTTONS_CALLBACK SW3_releasedCallback;

void
Buttons_Init ()
{
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct;

  // sw2
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  // sw3
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  // sw1
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);

  sample_timestamp = HAL_GetTick ();
}

void
Buttons_Run (void)
{
  if ((sample_timestamp + SW_DEBOUNCE_TIMEOUT) > HAL_GetTick ())
    {
      return;
    }

  sample_timestamp = HAL_GetTick ();

  // SW1
  BUTTONS_STATUS SW1_new_state = Buttons_GetSW1 ();
  if (SW1_lastState == BUTTONS_RELEASED && SW1_new_state == BUTTONS_PRESSED)
    {
      if (SW1_pressedCallback != NULL)
	{
	  SW1_pressedCallback ();
	}
    }
  else if (SW1_lastState == BUTTONS_PRESSED
      && SW1_new_state == BUTTONS_RELEASED)
    {
      if (SW1_releasedCallback != NULL)
	{
	  SW1_releasedCallback ();
	}
    }
  SW1_lastState = SW1_new_state;

  // SW2
  BUTTONS_STATUS SW2_new_state = Buttons_GetSW2 ();
  if (SW2_lastState == BUTTONS_RELEASED && SW2_new_state == BUTTONS_PRESSED)
    {
      if (SW2_pressedCallback != NULL)
	{
	  SW2_pressedCallback ();
	}
    }
  else if (SW2_lastState == BUTTONS_PRESSED
      && SW2_new_state == BUTTONS_RELEASED)
    {
      if (SW2_releasedCallback != NULL)
	{
	  SW2_releasedCallback ();
	}
    }
  SW2_lastState = SW2_new_state;

  // SW3
  BUTTONS_STATUS SW3_new_state = Buttons_GetSW3 ();
  if (SW3_lastState == BUTTONS_RELEASED && SW3_new_state == BUTTONS_PRESSED)
    {
      if (SW3_pressedCallback != NULL)
	{
	  SW3_pressedCallback ();
	}
    }
  else if (SW3_lastState == BUTTONS_PRESSED
      && SW3_new_state == BUTTONS_RELEASED)
    {
      if (SW3_releasedCallback != NULL)
	{
	  SW3_releasedCallback ();
	}
    }
  SW3_lastState = SW3_new_state;
}

BUTTONS_STATUS
Buttons_GetSW1 (void)
{
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_4) == GPIO_PIN_SET)
    {
      return BUTTONS_RELEASED;
    }
  else
    {
      return BUTTONS_PRESSED;
    }
}

BUTTONS_STATUS
Buttons_GetSW2 (void)
{
  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_0) == GPIO_PIN_SET)
    {
      return BUTTONS_RELEASED;
    }
  else
    {
      return BUTTONS_PRESSED;
    }
}

BUTTONS_STATUS
Buttons_GetSW3 (void)
{
  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_1) == GPIO_PIN_SET)
    {
      return BUTTONS_RELEASED;
    }
  else
    {
      return BUTTONS_PRESSED;
    }
}

/**
 *
 */
void
Buttons_SW1_SetPressedCallback (BUTTONS_CALLBACK pCallback)
{
  SW1_pressedCallback = pCallback;
}

void
Buttons_SW1_SetReleasedCallback (BUTTONS_CALLBACK pCallback)
{
  SW1_releasedCallback = pCallback;
}

void
Buttons_SW2_SetPressedCallback (BUTTONS_CALLBACK pCallback)
{
  SW2_pressedCallback = pCallback;
}

void
Buttons_SW2_SetReleasedCallback (BUTTONS_CALLBACK pCallback)
{
  SW2_releasedCallback = pCallback;
}

void
Buttons_SW3_SetPressedCallback (BUTTONS_CALLBACK pCallback)
{
  SW3_pressedCallback = pCallback;
}

void
Buttons_SW3_SetReleasedCallback (BUTTONS_CALLBACK pCallback)
{
  SW3_releasedCallback = pCallback;
}
