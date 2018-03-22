// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stdlib.h>
#include <command/led_operator_factory.h>

typedef struct LedOperatorStruct {
  CommandStruct base;
  LedDriver driver;
} LedOperatorStruct;

typedef struct LedOperatorStruct *LedOperator;

static void LedTurnOn(Command super) {
  LedOperator self = (LedOperator)super;
  TurnOnLed(self->driver);
}

static void LedTurnOff(Command super) {
  LedOperator self = (LedOperator)super;
  TurnOffLed(self->driver);
}

static void LedToggle(Command super) {
  LedOperator self = (LedOperator)super;
  ToggleLed(self->driver);
}

static CommandInterfaceStruct interface[OP_MAX_FACTORY_ID] = {
  { .Execute = LedTurnOn },
  { .Execute = LedTurnOff },
  { .Execute = LedToggle }
};

Command LedOperatorFactory(LedDriver driver, int32_t op_id) {
  if (driver == NULL) return NULL;
  if (op_id <= -1 || OP_MAX_FACTORY_ID <= op_id) return NULL;

  LedOperator command = calloc(1, sizeof(LedOperatorStruct));
  command->base.vtable = &interface[op_id];
  command->driver = driver;

  return (Command)command;
}

void DestroyLedOperator(Command super) {
  free(super);
}
