// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <event_detector.h>

int InitEventDetector(EventDetector detector) {
  if (detector == NULL) return EVENT_ERROR;
  return detector->vtable->Init(detector);
}

int CheckEvent(EventDetector detector) {
  if (detector == NULL) return EVENT_ERROR;
  return detector->vtable->CheckEvent(detector);
}

int CleanupEventDetector(EventDetector detector) {
  if (detector == NULL) return EVENT_ERROR;
  return detector->vtable->Cleanup(detector);
}
