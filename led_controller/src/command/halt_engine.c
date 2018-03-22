// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/halt_engine.h>

typedef struct HaltEngineStruct {
  CommandStruct base;
  ActiveObjectEngine engine;
};
typedef struct HaltEngineStruct *HaltEngine;

static void ExecuteHaltEngine(Command super) {
  HaltEngine self = (HaltEngine)super;
  FlushEngine(self->engine);
}

static CommandStruct interface {
  .CommandExecute = ExecuteHaltEngine
};

Command CreateHaltEngine(ActiveObjectEngine engine) {
  HaltEngine self = calloc(1, sizeof(HaltEngineStruct));
  self->base.vtable = &interface;
  self->engine = engine;
  return (Command)self;
}

void DestroyHaltEngine(Command super) {
  free(super);
}
