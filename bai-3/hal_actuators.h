#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "config.h"

void HAL_Actuators_Init(void);
void HAL_TurnPumpOn(void);
void HAL_TurnPumpOff(void);
void HAL_SetLedState(LedState_t state);

#endif
