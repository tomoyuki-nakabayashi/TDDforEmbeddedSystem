// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_OPERATOR_OPERATOR_H_
#define LED_CONTROLLER_OPERATOR_OPERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OperatorInterfaceStruct *OperatorInterface;
typedef struct OperatorStruct *Operator;

typedef struct OperatorStruct {
  OperatorInterface vtable;
} OperatorStruct;

typedef struct OperatorInterfaceStruct {
  void (*Operate)(Operator);
} OperatorInterfaceStruct;

void TriggerOperation(Operator op);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_OPERATOR_OPERATOR_H_
