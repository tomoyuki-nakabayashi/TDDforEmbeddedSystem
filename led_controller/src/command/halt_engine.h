// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_HALT_ENGINE_H_
#define LED_CONTROLLER_COMMAND_HALT_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <command/command.h>
#include <active_object_engine.h>

Command CreateHaltEngine(ActiveObjectEngine engine);
void DestroyHaltEngine(Command super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_HALT_ENGINE_H_
