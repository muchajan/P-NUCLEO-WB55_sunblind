/*
 * sunblind.c
 *
 *  Created on: 11. 6. 2020
 *      Author: janmu
 */

#include "sunblind.h"
#include "../drv8838/drv8388.h"
#include "stm32wbxx.h"

//static DRV8838_DIR eDir = DRV8838_DIR_CW;
static SUNBLIND_STATE ePreviousState = SUNBLIND_STATE_IDLE;
static SUNBLIND_STATE eState = SUNBLIND_STATE_IDLE;

static uint32_t eRange = 0;

void
Sunblind_Init ()
{
  Drv8838_Init ();
}

void
Sunblind_ConfigureCurrentLimit (void)
{
  if (eState == SUNBLIND_STATE_IDLE)
    {
      if (ePreviousState == SUNBLIND_STATE_GOING_DOWN)
	{
	  TIM2->CNT = 0;
	}
      else if (ePreviousState == SUNBLIND_STATE_GOING_UP)
	{
	  eRange = TIM2->CNT;
	}
    }
}

void
Sunblind_GoUp ()
{
  Drv8838_Start (DRV8838_DIR_CW);
  ePreviousState = eState;
  eState = SUNBLIND_STATE_GOING_UP;
}

void
Sunblind_GoDown ()
{
  Drv8838_Start (DRV8838_DIR_CCW);
  ePreviousState = eState;
  eState = SUNBLIND_STATE_GOING_DOWN;
}

void
Sunblind_Stop ()
{
  Drv8838_Stop ();
  ePreviousState = eState;
  eState = SUNBLIND_STATE_IDLE;
}

void
Sunblind_Run (void)
{

}
