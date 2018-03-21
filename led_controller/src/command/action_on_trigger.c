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
} ActionOnTriggerChainStruct;
typedef struct ActionOnTriggerChainStruct *ActionOnTriggerChain;

static void ExecuteActionOnTrigger(Command super) {
  ActionOnTriggerChain self = (ActionOnTriggerChain)super;
  const int32_t index = self->index;
  if(self->chain[index] == NULL) return;

  if(CheckEvent(self->chain[index]->detector) == DETECTOR_EVENT_DETECTED) {
    TriggerOperation(self->chain[index]->op);
    self->index++;
  }
}

static CommandInterfaceStruct interface = {
  .Execute = ExecuteActionOnTrigger
};

// Should give ActiveObjectEngine.
Command CreateActionOnTriggerChain(TriggerActionPair *chain) {
  ActionOnTriggerChain aot_chain = calloc(1, sizeof(ActionOnTriggerChainStruct));
  aot_chain->base.vtable = &interface;
  aot_chain->chain = chain;
  aot_chain->index = 0;

  return (Command)aot_chain;
}

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Operator op) {
  TriggerActionPair pair = calloc(1, sizeof(TriggerActionPairStruct));
  pair->detector = detector;
  pair->op = op;
  return pair;
}
