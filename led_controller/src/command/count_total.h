// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_COUNT_TOTAL_H_
#define LED_CONTROLLER_COMMAND_COUNT_TOTAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <command/command.h>

Command CreateCountTotal();
void DestroyCountTotal(Command super);
int32_t TotalIs(Command super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_COUNT_TOTAL_H_
