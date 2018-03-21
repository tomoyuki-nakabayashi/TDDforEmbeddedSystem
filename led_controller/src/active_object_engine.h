// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_ACTIVE_OBJECT_ENGINE_H_
#define LED_CONTROLLER_ACTIVE_OBJECT_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <command/command.h>

struct ActiveObjectEngineStruct;
typedef struct ActiveObjectEngineStruct *ActiveObjectEngine;

ActiveObjectEngine CreateActiveObjectEngine();
void DestroyActiveObjectEngine(ActiveObjectEngine engine);
void FuelEngine(ActiveObjectEngine engine, Command cmd);
void EngineRuns(ActiveObjectEngine engine);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_ACTIVE_OBJECT_ENGINE_H_
