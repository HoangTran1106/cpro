#include "hal_buttons.h"
#include <stdio.h>
#include <stdlib.h>

int btn1_count = 0; // dem cho nut 1
int btn2_count = 0; // dem cho nut 2

void HAL_Buttons_Init(void) {
    printf("Khoi tao nut nhan...\n");
}

bool HAL_IsButton1Pressed(void) {
    btn1_count++;
    
    // nut 1 nhan sau 50 lan kiem tra
    if (btn1_count >= 50) {
        btn1_count = 0;
        printf(">>> NUT 1 DUOC NHAN <<<\n");
        return true;
    }
    
    return false;
}

bool HAL_IsButton2Pressed(void) {
    btn2_count++;
    
    // nut 2 nhan ngau nhien
    if (btn2_count >= 80 && (rand() % 100) < 20) {
        btn2_count = 0;
        printf(">>> NUT 2 DUOC NHAN <<<\n");
        return true;
    }
    
    return false;
}
