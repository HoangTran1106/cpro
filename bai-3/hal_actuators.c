#include "hal_actuators.h"
#include <stdio.h>

void HAL_Actuators_Init(void) {
    printf("Khoi tao bom va LED...\n");
    HAL_TurnPumpOff();
    HAL_SetLedState(LED_NORMAL);
}

void HAL_TurnPumpOn(void) {
    printf(">>> BOM BAT <<<\n");
}

void HAL_TurnPumpOff(void) {
    printf(">>> BOM TAT <<<\n");
}

void HAL_SetLedState(LedState_t state) {
    // xuat ra trang thai LED
    if(state == LED_NORMAL) {
        printf("LED: XANH - Binh thuong\n");
    }
    else if(state == LED_WATERING) {
        printf("LED: VANG - Dang tuoi\n");
    }
    else if(state == LED_LOW_MOISTURE_ALERT) {
        printf("LED: DO NHAP NHAY - Canh bao\n");
    }
    else if(state == LED_ERROR) {
        printf("LED: DO - Loi\n");
    }
}
