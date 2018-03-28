// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/action_on_trigger.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct TriggerActionPairStruct {
  EventDetector detector;
  Command command;
} TriggerActionPairStruct;

typedef struct ActionOnTriggerChainStruct {
  CommandStruct base;
  TriggerActionPair chain;
  ActiveObjectEngine engine;
  int32_t loop_flag;
  int32_t index;
  bool started;
} ActionOnTriggerChainStruct;
typedef struct ActionOnTriggerChainStruct *ActionOnTriggerChain;

static void ExecuteActionOnTrigger(Command super) {
  ActionOnTriggerChain self = (ActionOnTriggerChain)super;

  if (!self->started) {
    StartEventDetector(self->chain->detector);
    self->started = true;
  }

  if (CheckEvent(self->chain->detector) == DETECTOR_EVENT_DETECTED) {
    FuelEngine(self->engine, self->chain->command);
    CleanupEventDetector(self->chain->detector);
    self->started = false;
    if (self->loop_flag == ONE_SHOT_CHAIN)
      return;  // Finish this chain by avoiding FuelEngine().
  }

  FuelEngine(self->engine, (Command)self);
}

static CommandInterfaceStruct interface = {
  .Execute = ExecuteActionOnTrigger
};

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Command command) {
  TriggerActionPair pair = calloc(1, sizeof(TriggerActionPairStruct));
  pair->detector = detector;
  pair->command = command;
  return pair;
}

void DestroyTriggerActionPair(TriggerActionPair trigger_action) {
  free(trigger_action);
}

// Should give ActiveObjectEngine.
Command CreateActionOnTriggerChain(TriggerActionPair chain,
                                   ActiveObjectEngine engine,
                                   int32_t loop_flag) {
  ActionOnTriggerChain self = calloc(1, sizeof(ActionOnTriggerChainStruct));
  self->base.vtable = &interface;
  self->chain = chain;
  self->engine = engine;
  self->loop_flag = loop_flag;
  self->started = false;

  return (Command)self;
}

void DestroyActionOnTriggerChain(Command super) {
  free(super);
}
