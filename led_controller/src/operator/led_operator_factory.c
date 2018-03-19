// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stdlib.h>
#include <operator/led_operator_factory.h>

typedef struct LedOperatorStruct {
  OperatorStruct base;
  LedDriver driver;
} LedOperatorStruct;

typedef struct LedOperatorStruct *LedOperator;

static void OperateLedTurnOn(Operator super) {
  LedOperator self = (LedOperator)super;
  TurnOnLed(self->driver);
}

static void OperateLedTurnOff(Operator super) {
  LedOperator self = (LedOperator)super;
  TurnOffLed(self->driver);
}

static void OperateLedToggle(Operator super) {
  LedOperator self = (LedOperator)super;
  ToggleLed(self->driver);
}

static OperatorInterfaceStruct interface[OP_MAX_FACTORY_ID] = {
  { .Operate = OperateLedTurnOn },
  { .Operate = OperateLedTurnOff },
  { .Operate = OperateLedToggle }
};

Operator LedOperatorFactory(LedDriver driver, int32_t op_id) {
  if (driver == NULL) return NULL;
  if (op_id <= -1 || OP_MAX_FACTORY_ID <= op_id) return NULL;

  LedOperator op = calloc(1, sizeof(LedOperatorStruct));
  op->base.vtable = &interface[op_id];
  op->driver = driver;
}
