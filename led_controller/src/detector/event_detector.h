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
  DETECTOR_SUCCESS = 0,
  DETECTOR_EVENT_DETECTED = 1,
  DETECTOR_EVENT_NOT_DETECTED = 2,
  DETECOTR_UNEXPECTED_EVENT = 3,
  DETECTOR_ERROR = -1,
  DETECTOR_INVALID_PARAMS = -2,
  DETECTOR_INVALID_DETECTOR = -3,
  DETECOTR_NOT_INITIALIZED = -4,
};

typedef struct EventDetectorInterfaceStruct *EventDetectorInterface;
typedef struct EventDetectorStruct *EventDetector;

typedef struct EventDetectorStruct {
  EventDetectorInterface vtable;
} EventDetectorStruct;

typedef struct EventDetectorInterfaceStruct {
  int (*Start)(EventDetector);
  int (*CheckEvent)(EventDetector);
  int (*Cleanup)(EventDetector);
} EventDetectorInterfaceStruct;

// Initialize EventDetector.
// params: detector  A derived EventDetector which has been already created.
// return: DETECTOR_SUCCESS if initialize success.
//         DETECTOR_ERROR, if detector is null or fail to initialize
//                               in the derived initialization.
int StartEventDetector(EventDetector detector);

// Check event occurance of the detector.
// params: detecor  A derived EventDetector which has been already Start.
// return: DETECTOR_EVENT_DETECTED if target event has been detected.
//         DETECTOR_EVENT_NOT_DETECTED if target event han NOT been detected.
//         DETECTOR_ERROR if an error occurs e.g., detector is not initialized.
int CheckEvent(EventDetector detector);

// Cleanup detector.
// params: detector  The detector will not be used after this function calls.
int CleanupEventDetector(EventDetector detector);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_EVENT_DETECTOR_H_
