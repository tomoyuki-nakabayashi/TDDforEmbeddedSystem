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
  EVENT_DETECTOR_SUCCESS = 0,
  EVENT_DETECTED = 1,
  EVENT_NOT_DETECTED = -1,
  EVENT_DETECTOR_ERROR = -2,
};

typedef struct EventDetectorInterfaceStruct *EventDetectorInterface;
typedef struct EventDetectorStruct *EventDetector;

typedef struct EventDetectorStruct {
  EventDetectorInterface vtable;
} EventDetectorStruct;

typedef struct EventDetectorInterfaceStruct {
  int (*Init)(EventDetector);
  int (*CheckEvent)(EventDetector);
  int (*Cleanup)(EventDetector);
} EventDetectorInterfaceStruct;

// Initialize EventDetector.
// params: detector  A derived EventDetector which has been already created.
// return: EVENT_DETECTOR_SUCCESS if initialize success.
//         EVENT_DETECTOR_ERROR, if detector is null or fail to initialize
//                               in the derived initialization.
int InitEventDetector(EventDetector detector);


int CheckEvent(EventDetector detector);
int CleanupEventDetector(EventDetector detector);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_EVENT_DETECTOR_H_
