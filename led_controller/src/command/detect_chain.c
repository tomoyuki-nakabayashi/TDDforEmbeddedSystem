// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/detect_chain.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DetectChainStruct {
  CommandStruct base;
  EventDetector detector;
  bool detector_started;
  ActiveObjectEngine engine;
  Command wakeup;
} DetectChainStruct;
typedef struct DetectChainStruct *DetectChain;

static void DetectChainExecute(Command super) {
  DetectChain self = (DetectChain)super;

  if (!self->detector_started) {
    self->detector_started = true;
    StartEventDetector(self->detector);
  }

  int rc = CheckEvent(self->detector);
  if (rc == DETECTOR_EVENT_DETECTED) {
    FuelEngine(self->engine, self->wakeup);
    self->detector_started = false;
    CleanupEventDetector(self->detector);
  } else if (rc == DETECTOR_EVENT_NOT_DETECTED) {
    FuelEngine(self->engine, (Command)self);
  } else {
    self->detector_started = false;
    CleanupEventDetector(self->detector);
  }
}

static CommandInterfaceStruct interface = {
  .Execute = DetectChainExecute
};

Command CreateDetectChain(EventDetector detector,
                          ActiveObjectEngine engine,
                          Command wakeup) {
  DetectChain self = calloc(1, sizeof(DetectChainStruct));
  self->base.vtable = &interface;
  self->detector = detector;
  self->detector_started = false;
  self->engine = engine;
  self->wakeup = wakeup;
}

void DestroyCreateDetectChain(Command super) {
  free(super);
}