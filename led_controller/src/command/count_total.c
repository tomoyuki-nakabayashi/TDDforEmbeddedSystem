// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/count_total.h>
#include <stdlib.h>

typedef struct CountTotalCommand {
  CommandStruct base;
  int32_t total;
} CountTotalCommand;
typedef struct CountTotalCommand *CountTotal;

static void IncrementTotalCounter(Command super) {
  CountTotal self = (CountTotal)super;
  self->total++;
}

static CommandInterfaceStruct total_counter_interface = {
  .Execute = IncrementTotalCounter
};

Command CreateCountTotal() {
  CountTotal cmd = calloc(1, sizeof(CountTotalCommand));
  cmd->base.vtable = &total_counter_interface;
  cmd->total = 0;
  return (Command)cmd;
}

void DestroyCountTotal(Command super) {
  free(super);
}

int32_t TotalIs(Command super) {
  CountTotal self = (CountTotal)super;
  return self->total;
}
