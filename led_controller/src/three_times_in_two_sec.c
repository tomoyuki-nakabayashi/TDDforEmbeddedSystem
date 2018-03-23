// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <active_object_engine.h>
#include <command/command.h>
#include <command/count_total.h>
#include <command/halt_engine.h>
#include <command/action_on_trigger.h>
#include <detector/key_input_detector.h>
#include <detector/event_detector.h>
#include <detector/timeout_detector.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define NUM_OPERATION_ON_DETECTION 2

int main(void) {
  struct timeval kTime = {};
  const struct input_event kPressA = {kTime, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

  ActiveObjectEngine engine = CreateActiveObjectEngine();

  // Create components.
  EventDetector press_a = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  EventDetector two_sec_timeout = CreateTimeOutDetector(2000, TIMER_ONE_SHOT);
  Command total = CreateCountTotal();
  Command halt = CreateHaltEngine(engine);

  TriggerActionPair action_one[2], action_two[2];
  action_one[0] = CreateTriggerActionPair(press_a, total);
  action_one[1] = NULL;  // null-termination.
  action_two[0] = CreateTriggerActionPair(two_sec_timeout, halt);
  action_two[1] = NULL;  // null-termination.

  Command cmd_one = CreateActionOnTriggerChain(action_one, engine, LOOP_CHAIN);
  Command cmd_two = CreateActionOnTriggerChain(action_two, engine, ONE_SHOT_CHAIN);
  FuelEngine(engine, cmd_one);
  FuelEngine(engine, cmd_two);

  EngineRuns(engine);

  printf("Press A key %d times in two seconds\n.", TotalIs(total));

  // Need cleanup.
  DestroyActionOnTriggerChain(cmd_one);
  DestroyActionOnTriggerChain(cmd_two);
  DestroyActiveObjectEngine(engine);
  DestroyTriggerActionPair(action_one[0]);
  DestroyTriggerActionPair(action_two[0]);
  DestroyKeyInputDetector(press_a);
  DestroyTimeOutDetector(two_sec_timeout);

  return 0;
}
