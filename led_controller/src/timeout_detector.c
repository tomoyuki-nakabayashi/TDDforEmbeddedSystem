// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <timeout_detector.h>
#include <stdlib.h>

typedef struct TimeOutDetectorStruct {
  EventDetectorStruct base;
  int32_t interval_msec;
  int32_t flag;
} TimeOutDetectorStruct;

static int InitTimeOutDetector(EventDetector super) {
  return EVENT_DETECTOR_SUCCESS;
}

static int CheckTimeOut(EventDetector super) {
  return EVENT_DETECTED;
}

static int CleanupTimeOutDetector(EventDetector super) {
  return EVENT_DETECTOR_SUCCESS;
}

static EventDetectorInterfaceStruct interface = {
  .Init = InitTimeOutDetector,
  .CheckEvent = CheckTimeOut,
  .Cleanup = CleanupTimeOutDetector
};

EventDetector CreateTimeOutDetector(const int32_t interval_msec,
                                    const int32_t flag) {
  TimeOutDetector detector = calloc(1, sizeof(TimeOutDetectorStruct));
  detector->base.vtable = &interface;
  detector->interval_msec = interval_msec;
  detector->flag = flag;

  return (EventDetector)detector;
}

void DestroyTimeOutDetector(EventDetector self) {
  free(self);
}
