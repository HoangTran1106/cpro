#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"

// bien toan cuc
SystemState_t systemState;
SystemSettings_t systemSettings;
SensorData_t sensorData;

void System_Init(void) {
    // khoi tao cac module
    HAL_Sensors_Init();
    HAL_Actuators_Init();
    HAL_Buttons_Init();
    
    // khoi tao controller
    SPWS_Init(&systemState, &systemSettings);
}

int main(void) {
    // khoi tao
    System_Init();
    
    int count = 0; // bien dem
    
    printf("Bat dau vong lap...\n");
    printf("Nhan Ctrl+C de dung\n\n");
    
    // vong lap chinh
    while(1) {
        // doi 1 giay
        sleep(1);
        count++;
        
        // kiem tra nut nhan
        
        // nut 1: chuyen che do
        if (HAL_IsButton1Pressed()) {
            SPWS_SwitchMode(&systemState);
        }
        
        // nut 2: tuoi thu cong
        if (HAL_IsButton2Pressed()) {
            SPWS_StartManualWatering(&systemState, &systemSettings);
        }
        
        // doc cam bien
        systemState.sensorCheckCounter++;
        if (systemState.sensorCheckCounter >= systemSettings.sensorReadInterval_s) {
            HAL_ReadAllSensors(&sensorData);
            systemState.sensorCheckCounter = 0;
            
            // cap nhat LED
            SPWS_UpdateLED(&systemState, &sensorData, &systemSettings);
        }
        
        // chay logic theo che do
        if (systemState.currentMode == MODE_AUTO) {
            SPWS_RunAutoMode(&systemState, &systemSettings, &sensorData);
        }
        else if (systemState.currentMode == MODE_MANUAL) {
            SPWS_RunManualMode(&systemState, &systemSettings);
        }
        
        // in trang thai moi 10 giay
        if (count % 10 == 0) {
            printf("\n--- Trang thai (Loop: %d) ---\n", count);
            if(systemState.currentMode == MODE_AUTO) {
                printf("Che do: TU DONG\n");
            } else {
                printf("Che do: THU CONG\n");
            }
            
            if(systemState.pumpState == PUMP_ON) {
                printf("Bom: BAT\n");
            } else {
                printf("Bom: TAT\n");
            }
            
            printf("Do am: %.1f%%\n", sensorData.soilMoisturePercent);
            printf("Nhiet do: %.1fC\n", sensorData.airTemperatureCelsius);
            printf("-----------------------------\n\n");
        }
    }
    
    return 0;
}
