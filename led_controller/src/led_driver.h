// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_LED_DRIVER_EVENT_H_
#define LED_CONTROLLER_LED_DRIVER_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct LedDriverStruct;
typedef struct LedDriverStruct *LedDriver;

typedef enum {
  LED_UNKNOWN = -1,
  LED_TURN_OFF = 0,
  LED_TURN_ON = 1,
} LedStatus;

LedDriver CreateLedDriver();

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_LED_DRIVER_EVENT_H_