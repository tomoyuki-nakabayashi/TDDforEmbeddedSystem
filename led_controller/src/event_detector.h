// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_EVENT_DETECTOR_H_
#define LED_CONTROLLER_EVENT_DETECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

enum {
  EVENT_SUCCESS = 0,
  EVENT_DETECTED = 1,
  EVENT_NOT_DETECTED = -1,
  EVENT_ERROR = -2,
};

typedef struct EventDetectorInterfaceStruct *EventDetectorInterface;
typedef struct EventDetectorStruct *EventDetector;

typedef struct EventDetectorStruct {
  EventDetectorInterface vtable;
} EventDetectorStruct;

typedef struct EventDetectorInterfaceStruct {
  int (*CheckEvent)(EventDetector);
} EventDetectorInterfaceStruct;

inline int CheckEvent(EventDetector detector) {
  if (detector == NULL) return EVENT_ERROR;
  return detector->vtable->CheckEvent(detector);
}

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_EVENT_DETECTOR_H_
