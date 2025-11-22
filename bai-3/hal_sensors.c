#include "hal_sensors.h"
#include <stdio.h>
#include <stdlib.h>

float moisture = 25.0f; // bien toan cuc luu do am
int direction = 1; // huong tang hay giam

void HAL_Sensors_Init(void) {
    printf("Khoi tao cam bien...\n");
    // chua lam gi
}

float HAL_ReadSoilMoisture(void) {
    // mo phong do am tu 20 den 80%
    moisture = moisture + (direction * 2.0f);
    
    if (moisture >= 80.0f) {
        direction = -1;
    } else if (moisture <= 20.0f) {
        direction = 1;
    }
    
    return moisture;
}

float HAL_ReadAirTemperature(void) {
    // nhiet do tu 25-30 do C
    float temp = 25.0f + (rand() % 50) / 10.0f;
    return temp;
}

void HAL_ReadAllSensors(SensorData_t* data) {
    data->soilMoisturePercent = HAL_ReadSoilMoisture();
    data->airTemperatureCelsius = HAL_ReadAirTemperature();
    
    printf("Doc cam bien: Do am = %.1f%%, Nhiet do = %.1fC\n", 
           data->soilMoisturePercent, data->airTemperatureCelsius);
}
