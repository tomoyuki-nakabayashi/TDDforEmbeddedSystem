// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_TIMEOUT_DETECTOR_H_
#define LED_CONTROLLER_TIMEOUT_DETECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <event_detector.h>

struct TimeOutDetectorStruct;
typedef struct TimeOutDetectorStruct *TimeOutDetector;

enum {
  TIMER_ONE_SHOT = 0,
  TIMER_REPEATEDLY = 1,
};

EventDetector CreateTimeOutDetector(const int32_t interval_msec,
                                    const int flag);

void DestroyTimeOutDetector(EventDetector self);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_TIMEOUT_DETECTOR_H_
