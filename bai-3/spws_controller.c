#include "spws_controller.h"
#include "hal_actuators.h"
#include <stdio.h>

void SPWS_Init(SystemState_t* state, SystemSettings_t* settings) {
    printf("\n========================================\n");
    printf("  HE THONG TUOI CAY TU DONG (SPWS)\n");
    printf("========================================\n\n");
    
    // gan trang thai ban dau
    state->currentMode = MODE_AUTO;
    state->pumpState = PUMP_OFF;
    state->ledState = LED_NORMAL;
    state->wateringTimeCounter = 0;
    state->sensorCheckCounter = 0;
    
    // gan cai dat mac dinh
    settings->minMoistureThreshold = DEFAULT_MIN_MOISTURE;
    settings->maxMoistureThreshold = DEFAULT_MAX_MOISTURE;
    settings->maxWateringDuration_s = DEFAULT_MAX_WATERING_TIME;
    settings->sensorReadInterval_s = DEFAULT_SENSOR_INTERVAL;
    settings->manualWateringDuration_s = DEFAULT_MANUAL_WATERING_TIME;
    
    printf("Khoi tao thanh cong!\n");
    printf("Che do: TU DONG\n");
    printf("Nguong do am: %.1f%% - %.1f%%\n\n", 
           settings->minMoistureThreshold, 
           settings->maxMoistureThreshold);
}

void SPWS_RunAutoMode(SystemState_t* state, SystemSettings_t* settings, SensorData_t* sensorData) {
    // neu bom dang tat
    if (state->pumpState == PUMP_OFF) {
        // kiem tra do am
        if (sensorData->soilMoisturePercent < settings->minMoistureThreshold) {
            // bat bom
            HAL_TurnPumpOn();
            state->pumpState = PUMP_ON;
            state->wateringTimeCounter = 0;
            state->ledState = LED_WATERING;
            HAL_SetLedState(state->ledState);
            printf("[AUTO] Bat dau tuoi (Do am thap: %.1f%%)\n", 
                   sensorData->soilMoisturePercent);
        }
    }
    // neu bom dang bat
    else if (state->pumpState == PUMP_ON) {
        state->wateringTimeCounter++;
        
        // kiem tra do am dat nguong
        if (sensorData->soilMoisturePercent > settings->maxMoistureThreshold) {
            HAL_TurnPumpOff();
            state->pumpState = PUMP_OFF;
            state->ledState = LED_NORMAL;
            HAL_SetLedState(state->ledState);
            printf("[AUTO] Ket thuc tuoi (Do am du: %.1f%%)\n", 
                   sensorData->soilMoisturePercent);
            state->wateringTimeCounter = 0;
        }
        // kiem tra timeout
        else if (state->wateringTimeCounter >= settings->maxWateringDuration_s) {
            HAL_TurnPumpOff();
            state->pumpState = PUMP_OFF;
            state->ledState = LED_ERROR;
            HAL_SetLedState(state->ledState);
            printf("[AUTO] TAT BOM - Qua thoi gian!\n");
            state->wateringTimeCounter = 0;
        }
        else {
            printf("[AUTO] Dang tuoi... (%d/%d giay)\n", 
                   state->wateringTimeCounter, 
                   settings->maxWateringDuration_s);
        }
    }
}

void SPWS_RunManualMode(SystemState_t* state, SystemSettings_t* settings) {
    // che do thu cong
    if (state->pumpState == PUMP_ON) {
        state->wateringTimeCounter++;
        
        // kiem tra het thoi gian
        if (state->wateringTimeCounter >= settings->manualWateringDuration_s) {
            HAL_TurnPumpOff();
            state->pumpState = PUMP_OFF;
            state->ledState = LED_NORMAL;
            HAL_SetLedState(state->ledState);
            printf("[MANUAL] Het thoi gian tuoi\n");
            state->wateringTimeCounter = 0;
        }
        else {
            printf("[MANUAL] Dang tuoi thu cong... (%d/%d giay)\n", 
                   state->wateringTimeCounter, 
                   settings->manualWateringDuration_s);
        }
    }
}

void SPWS_SwitchMode(SystemState_t* state) {
    // chuyen che do
    if (state->currentMode == MODE_AUTO) {
        state->currentMode = MODE_MANUAL;
        printf("\n>>> CHUYEN SANG CHE DO THU CONG <<<\n\n");
        
        // tat bom neu dang chay
        if (state->pumpState == PUMP_ON) {
            HAL_TurnPumpOff();
            state->pumpState = PUMP_OFF;
            state->wateringTimeCounter = 0;
        }
        
        state->ledState = LED_NORMAL;
        HAL_SetLedState(state->ledState);
    }
    else {
        state->currentMode = MODE_AUTO;
        printf("\n>>> CHUYEN SANG CHE DO TU DONG <<<\n\n");
        
        // tat bom neu dang chay
        if (state->pumpState == PUMP_ON) {
            HAL_TurnPumpOff();
            state->pumpState = PUMP_OFF;
            state->wateringTimeCounter = 0;
        }
        
        state->ledState = LED_NORMAL;
        HAL_SetLedState(state->ledState);
    }
}

void SPWS_StartManualWatering(SystemState_t* state, SystemSettings_t* settings) {
    // chi hoat dong o che do manual
    if (state->currentMode != MODE_MANUAL) {
        printf("Loi! Chi tuoi thu cong o che do MANUAL\n");
        return;
    }
    
    // kiem tra bom co dang chay khong
    if (state->pumpState == PUMP_ON) {
        printf("Bom dang chay roi!\n");
        return;
    }
    
    // bat bom
    HAL_TurnPumpOn();
    state->pumpState = PUMP_ON;
    state->wateringTimeCounter = 0;
    state->ledState = LED_WATERING;
    HAL_SetLedState(state->ledState);
    printf("[MANUAL] Bat dau tuoi thu cong\n");
}

void SPWS_UpdateLED(SystemState_t* state, SensorData_t* sensorData, SystemSettings_t* settings) {
    // cap nhat LED canh bao
    if (state->pumpState == PUMP_OFF && state->currentMode == MODE_AUTO) {
        if (sensorData->soilMoisturePercent < (settings->minMoistureThreshold - 5.0f)) {
            if (state->ledState != LED_LOW_MOISTURE_ALERT) {
                state->ledState = LED_LOW_MOISTURE_ALERT;
                HAL_SetLedState(state->ledState);
            }
        }
        else if (state->ledState != LED_NORMAL) {
            state->ledState = LED_NORMAL;
            HAL_SetLedState(state->ledState);
        }
    }
}
