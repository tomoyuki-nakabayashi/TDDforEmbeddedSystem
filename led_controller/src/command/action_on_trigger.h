// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_
#define LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <command/command.h>
#include <detector/event_detector.h>
#include <operator/operator.h>

struct TriggerActionPairStruct;
typedef struct TriggerActionPairStruct *TriggerActionPair;

TriggerActionPair CreateTriggerActionPair(EventDetector detector, Operator op);
Command CreateActionOnTriggerChain(TriggerActionPair *chain);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_OPERATION_ON_DETECTION_H_
