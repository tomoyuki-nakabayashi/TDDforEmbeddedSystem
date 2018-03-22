// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_OPERATOR_OPERATOR_H_
#define LED_CONTROLLER_OPERATOR_OPERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CommandInterfaceStruct *OperatorInterface;
typedef struct OperatorStruct *Operator;

typedef struct OperatorStruct {
  OperatorInterface vtable;
} OperatorStruct;

typedef struct CommandInterfaceStruct {
  void (*Operate)(Operator);
} CommandInterfaceStruct;

void TriggerOperation(Operator op);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_OPERATOR_OPERATOR_H_
