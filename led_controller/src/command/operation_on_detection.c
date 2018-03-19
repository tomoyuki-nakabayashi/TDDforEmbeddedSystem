// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/operation_on_detection.h>
#include <stdlib.h>

typedef struct OperationOnDetectionStruct {
  CommandStruct base;
  EventDetector detector;
  Operator operator;
} OperationOnDetectionStruct;
typedef struct OperationOnDetectionStruct *OperationOnDetection;

static void DoOperationOnDetection(Command super) {
  OperationOnDetection self = (OperationOnDetection)super;
  if(CheckEvent(self->detector) == DETECTOR_EVENT_DETECTED)
    TriggerOperation(self->operator);
}

static CommandInterfaceStruct interface = {
  .Execute = DoOperationOnDetection
};

Command CreateOperationOnDetection(EventDetector detector, Operator op) {
  OperationOnDetection self = calloc(1, sizeof(OperationOnDetectionStruct));
  self->base.vtable = &interface;
  self->detector = detector;
  self->operator = op;
  return (Command)self;
}
