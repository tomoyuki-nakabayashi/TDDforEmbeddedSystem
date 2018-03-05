// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_LED_DRIVER_EVENT_H_
#define LED_CONTROLLER_LED_DRIVER_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct LedDriverStruct;
typedef struct LedDriverStruct *LedDriver;

enum {
  LED_DRIVER_SUCCESS = 0,
  LED_DRIVER_INIT_ERROR = -1,
  LED_DRIVER_CLEAUP_ERROR = -2,
};

typedef enum {
  LED_UNKNOWN = -1,
  LED_TURN_OFF = 0,
  LED_TURN_ON = 1,
} LedStatus;

LedDriver CreateLedDriver();
int InitLedDriver(LedDriver self, const char* device_file);
void TurnOnLed(LedDriver self);
void TurnOffLed(LedDriver self);
void ToggleLed(LedDriver self);
int CleanupLedDriver(LedDriver self);
void DestroyLedDriver(LedDriver self);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_LED_DRIVER_EVENT_H_
