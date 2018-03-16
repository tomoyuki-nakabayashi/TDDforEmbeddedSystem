// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <timeout_detector.h>
#include <stdlib.h>

typedef struct TimeOutDetectorStruct {
  EventDetectorStruct base;
  uint32_t interval_sec;
  int32_t flag;
} TimeOutDetectorStruct;

static bool IsValidFlag(int32_t flag) {
  return (flag == TIMER_ONE_SHOT || flag == TIMER_REPEATEDLY);
}

static int StartTimeOutDetector(EventDetector super) {
  TimeOutDetector self = (TimeOutDetector)super;
  if (!IsValidFlag(self->flag)) return EVENT_DETECTOR_ERROR;

  return EVENT_DETECTOR_SUCCESS;
}

static int CheckTimeOut(EventDetector super) {
  return EVENT_DETECTED;
}

static int CleanupTimeOutDetector(EventDetector super) {
  return EVENT_DETECTOR_SUCCESS;
}

static EventDetectorInterfaceStruct interface = {
  .Start = StartTimeOutDetector,
  .CheckEvent = CheckTimeOut,
  .Cleanup = CleanupTimeOutDetector
};

EventDetector CreateTimeOutDetector(const uint32_t interval_sec,
                                    const int32_t flag) {
  TimeOutDetector detector = calloc(1, sizeof(TimeOutDetectorStruct));
  detector->base.vtable = &interface;
  detector->interval_sec = interval_sec;
  detector->flag = flag;

  return (EventDetector)detector;
}

void DestroyTimeOutDetector(EventDetector self) {
  free(self);
}
