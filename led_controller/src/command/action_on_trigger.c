// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/action_on_trigger.h>
#include <stdlib.h>

typedef struct TriggerActionPairStruct {
  EventDetector detector;
  Operator op;
} TriggerActionPairStruct;

typedef struct ActionOnTriggerChainStruct {
  CommandStruct base;
  TriggerActionPair *chain;
} ActionOnTriggerChainStruct;
typedef struct ActionOnTriggerChainStruct *ActionOnTriggerChain;

static void ExecuteActionOnTrigger(Command super) {
  ActionOnTriggerChain self = (ActionOnTriggerChain)super;
  if(CheckEvent(self->chain[0]->detector) == DETECTOR_EVENT_DETECTED)
    TriggerOperation(self->chain[0]->op);
}

static CommandInterfaceStruct interface = {
  .Execute = ExecuteActionOnTrigger
};

Command CreateActionOnTriggerChain(TriggerActionPair *chain) {
  ActionOnTriggerChain aot_chain = calloc(1, sizeof(ActionOnTriggerChainStruct));
  aot_chain->base.vtable = &interface;
  aot_chain->chain = chain;

  return (Command)aot_chain;
}

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Operator op) {
  TriggerActionPair pair = calloc(1, sizeof(TriggerActionPairStruct));
  pair->detector = detector;
  pair->op = op;
  return pair;
}
