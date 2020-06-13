/*
 * sunblind.h
 *
 *  Created on: 11. 6. 2020
 *      Author: janmu
 */

#ifndef SUNBLIND_SUNBLIND_H_
#define SUNBLIND_SUNBLIND_H_

typedef enum
{
  SUNBLIND_STATE_IDLE,
  SUNBLIND_STATE_GOING_UP,
  SUNBLIND_STATE_GOING_DOWN,
  SUNBLIND_STATE_UP,
  SUNBLIND_STATE_DOWN
} SUNBLIND_STATE;

typedef enum
{
  SUNBLIND_RESPONSE_OK
} SUNBLIND_RESPONSE;

void
Sunblind_Init (void);

void
Sunblind_ConfigureCurrentLimit (void);

void
Sunblind_GoDown (void);

void
Sunblind_Stop (void);

void
Sunblind_GoUp (void);

void
Sunblind_Run (void);

#endif /* SUNBLIND_SUNBLIND_H_ */
