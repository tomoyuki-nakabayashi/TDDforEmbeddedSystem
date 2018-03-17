// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <detector/timeout_detector.h>
#include <stdlib.h>
#include <os/time.h>

typedef struct TimeOutDetectorStruct {
  EventDetectorStruct base;
  uint32_t interval_msec;
  int32_t flag;
  uint32_t start_time;
  bool timer_started;
} TimeOutDetectorStruct;

static bool IsValidFlag(int32_t flag) {
  return (flag == TIMER_ONE_SHOT || flag == TIMER_REPEATEDLY);
}

static int StartTimeOutDetector(EventDetector super) {
  TimeOutDetector self = (TimeOutDetector)super;
  if (!IsValidFlag(self->flag)) return EVENT_DETECTOR_ERROR;
  self->start_time = GET_MSEC_OF_DAY();
  self->timer_started = true;

  return EVENT_DETECTOR_SUCCESS;
}

static int IsTimedOut(const uint32_t now,
                      const uint32_t start,
                      const uint32_t interval) {
  return (now - start >= interval);
}

static int CheckTimeOut(EventDetector super) {
  TimeOutDetector self = (TimeOutDetector)super;
  if (!self->timer_started) return EVENT_DETECTOR_ERROR;

  uint32_t now = GET_MSEC_OF_DAY();
  if (IsTimedOut(now, self->start_time, self->interval_msec)) {
    self->timer_started = false;
    return EVENT_DETECTED;
  }

  return EVENT_NOT_DETECTED;
}

static int CleanupTimeOutDetector(EventDetector super) {
  TimeOutDetector self = (TimeOutDetector)super;
  self->start_time = 0;
  self->timer_started = false;

  return EVENT_DETECTOR_SUCCESS;
}

static EventDetectorInterfaceStruct interface = {
  .Start = StartTimeOutDetector,
  .CheckEvent = CheckTimeOut,
  .Cleanup = CleanupTimeOutDetector
};

EventDetector CreateTimeOutDetector(const uint32_t interval_msec,
                                    const int32_t flag) {
  TimeOutDetector detector = calloc(1, sizeof(TimeOutDetectorStruct));
  detector->base.vtable = &interface;
  detector->interval_msec = interval_msec;
  detector->flag = flag;
  detector->start_time = 0;
  detector->timer_started = false;

  return (EventDetector)detector;
}

void DestroyTimeOutDetector(EventDetector self) {
  free(self);
}
