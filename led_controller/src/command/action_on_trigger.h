// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_
#define LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <command/command.h>
#include <active_object_engine.h>
#include <detector/event_detector.h>

struct TriggerActionPairStruct;
typedef struct TriggerActionPairStruct *TriggerActionPair;

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Command command);
void DestroyTriggerActionPair(TriggerActionPair trigger_action);
// chain must be null terminated.
Command CreateActionOnTriggerChain(TriggerActionPair *chain,
                                   ActiveObjectEngine engine);
void DestroyActionOnTriggerChain(Command super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_
