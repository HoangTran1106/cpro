#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>

void HAL_Buttons_Init(void);
bool HAL_IsButton1Pressed(void);
bool HAL_IsButton2Pressed(void);

#endif
