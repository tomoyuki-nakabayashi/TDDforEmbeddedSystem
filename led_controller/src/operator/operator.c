// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <operator/operator.h>

void TriggerOperation(Operator op) {
  op->vtable->Operate(op);
}
