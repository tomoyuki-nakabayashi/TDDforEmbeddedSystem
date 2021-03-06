// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <active_object_engine.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>

typedef struct ActiveObjectEngineStruct {
  GSList *commands;
} ActiveObjectEngineStruct;

ActiveObjectEngine CreateActiveObjectEngine() {
  ActiveObjectEngine engine = calloc(1, sizeof(ActiveObjectEngineStruct));
  engine->commands = g_slist_alloc();

  return engine;
}

void DestroyActiveObjectEngine(ActiveObjectEngine engine) {
  g_slist_free(engine->commands);
  free(engine);
}

void FuelEngine(ActiveObjectEngine engine, Command cmd) {
  if ((engine == NULL) || (cmd == NULL)) return;
  engine->commands = g_slist_append(engine->commands, (gpointer)cmd);
}

void EngineRuns(ActiveObjectEngine engine) {
  while(g_slist_length(engine->commands) > 0) {
    // retreave head data.
    Command cmd = (Command)g_slist_nth_data(engine->commands, 0);
    CommandExecute(cmd);
    engine->commands = g_slist_remove(engine->commands, (gpointer)cmd);
  }
}

void FlushEngine(ActiveObjectEngine engine) {
  if ((engine == NULL) || (engine->commands == NULL)) return;
  g_slist_free(engine->commands);
  engine->commands = g_slist_alloc();
}
