#ifndef CONFIG_H
#define CONFIG_H

// che do
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

// trang thai bom
typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

// trang thai LED
typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState_t;

// du lieu cam bien
typedef struct {
    float soilMoisturePercent;
    float airTemperatureCelsius;
} SensorData_t;

// cai dat he thong
typedef struct {
    float minMoistureThreshold;
    float maxMoistureThreshold;
    unsigned int maxWateringDuration_s;
    unsigned int sensorReadInterval_s;
    unsigned int manualWateringDuration_s;
} SystemSettings_t;

// trang thai he thong
typedef struct {
    SystemMode_t currentMode;
    PumpState_t pumpState;
    LedState_t ledState;
    unsigned int wateringTimeCounter;
    unsigned int sensorCheckCounter;
} SystemState_t;

// cac gia tri mac dinh
#define DEFAULT_MIN_MOISTURE 30.0f
#define DEFAULT_MAX_MOISTURE 70.0f
#define DEFAULT_MAX_WATERING_TIME 60
#define DEFAULT_SENSOR_INTERVAL 5
#define DEFAULT_MANUAL_WATERING_TIME 10

#endif
