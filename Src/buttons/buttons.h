/*
 * buttons.h
 *
 *  Created on: 10. 6. 2020
 *      Author: janmu
 */

#ifndef BUTTONS_BUTTONS_H_
#define BUTTONS_BUTTONS_H_

typedef void
(*BUTTONS_CALLBACK) (void);

typedef enum
{
  BUTTONS_PRESSED, BUTTONS_RELEASED,
} BUTTONS_STATUS;

void
Buttons_Init (void);

void
Buttons_Run (void);

void
Buttons_SW1_SetPressedCallback (BUTTONS_CALLBACK pCallback);
void
Buttons_SW1_SetReleasedCallback (BUTTONS_CALLBACK pCallback);

void
Buttons_SW2_SetPressedCallback (BUTTONS_CALLBACK pCallback);
void
Buttons_SW2_SetReleasedCallback (BUTTONS_CALLBACK pCallback);

void
Buttons_SW3_SetPressedCallback (BUTTONS_CALLBACK pCallback);
void
Buttons_SW3_SetReleasedCallback (BUTTONS_CALLBACK pCallback);

BUTTONS_STATUS
Buttons_GetSW1 (void);

BUTTONS_STATUS
Buttons_GetSW2 (void);

BUTTONS_STATUS
Buttons_GetSW3 (void);

#endif /* BUTTONS_BUTTONS_H_ */
