// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/action_on_trigger.h>
#include <stdlib.h>

typedef struct ActionOnTriggerCommandStruct {
  CommandStruct base;
  ActionOnTrigger aot;
  ActionOnTrigger next;
} ActionOnTriggerCommandStruct;
typedef struct ActionOnTriggerCommandStruct *ActionOnTriggerCommand;

static void ExecuteActionOnTrigger(Command super) {
  ActionOnTriggerCommand self = (ActionOnTriggerCommand)super;
  if(CheckEvent(self->aot->detector) == DETECTOR_EVENT_DETECTED)
    TriggerOperation(self->aot->op);
}

static CommandInterfaceStruct interface = {
  .Execute = ExecuteActionOnTrigger
};

Command CreateActionOnTrigger(EventDetector detector, Operator op) {
  ActionOnTriggerCommand self = calloc(1, sizeof(ActionOnTriggerCommandStruct));
  self->base.vtable = &interface;
  self->aot->detector = detector;
  self->aot->op = op;
  return (Command)self;
}
