#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include "config.h"

void SPWS_Init(SystemState_t* state, SystemSettings_t* settings);
void SPWS_RunAutoMode(SystemState_t* state, SystemSettings_t* settings, SensorData_t* sensorData);
void SPWS_RunManualMode(SystemState_t* state, SystemSettings_t* settings);
void SPWS_SwitchMode(SystemState_t* state);
void SPWS_StartManualWatering(SystemState_t* state, SystemSettings_t* settings);
void SPWS_UpdateLED(SystemState_t* state, SensorData_t* sensorData, SystemSettings_t* settings);

#endif
