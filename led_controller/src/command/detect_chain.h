// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_DETECT_CHAIN_H_
#define LED_CONTROLLER_COMMAND_DETECT_CHAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <command/command.h>
#include <active_object_engine.h>
#include <detector/event_detector.h>

Command CreateDetectChain(EventDetector detector,
                          ActiveObjectEngine engine,
                          Command wakeup);
void DestroyCreateDetectChain(Command super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_DETECT_CHAIN_H_
