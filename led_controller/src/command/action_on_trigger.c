// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/action_on_trigger.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct TriggerActionPairStruct {
  EventDetector detector;
  Operator op;
} TriggerActionPairStruct;

typedef struct ActionOnTriggerChainStruct {
  CommandStruct base;
  TriggerActionPair *chain;  // null terminated.
  int32_t index;
  bool index_started;
} ActionOnTriggerChainStruct;
typedef struct ActionOnTriggerChainStruct *ActionOnTriggerChain;

static void ExecuteActionOnTrigger(Command super) {
  ActionOnTriggerChain self = (ActionOnTriggerChain)super;
  const int32_t index = self->index;
  if (self->chain[index] == NULL) return;

  if (!self->index_started) {
    StartEventDetector(self->chain[index]->detector);
    self->index_started = true;
  }

  if (CheckEvent(self->chain[index]->detector) == DETECTOR_EVENT_DETECTED) {
    TriggerOperation(self->chain[index]->op);
    CleanupEventDetector(self->chain[index]->detector);
    self->index++;
    self->index_started = false;
  }
}

static CommandInterfaceStruct interface = {
  .Execute = ExecuteActionOnTrigger
};

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Operator op) {
  TriggerActionPair pair = calloc(1, sizeof(TriggerActionPairStruct));
  pair->detector = detector;
  pair->op = op;
  return pair;
}

void DestroyTriggerActionPair(TriggerActionPair trigger_action) {
  free(trigger_action);
}

// Should give ActiveObjectEngine.
Command CreateActionOnTriggerChain(TriggerActionPair *chain) {
  ActionOnTriggerChain aot_chain = calloc(1, sizeof(ActionOnTriggerChainStruct));
  aot_chain->base.vtable = &interface;
  aot_chain->chain = chain;
  aot_chain->index = 0;
  aot_chain->index_started = false;

  return (Command)aot_chain;
}
