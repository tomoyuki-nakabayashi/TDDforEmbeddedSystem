// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <event_detector.h>

int CheckEvent(EventDetector detector) {
  if (detector == NULL) return EVENT_ERROR;
  return detector->vtable->CheckEvent(detector);
}
