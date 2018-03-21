// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <active_object_engine.h>
#include <command/command.h>
#include <command/action_on_trigger.h>
#include <detector/key_input_detector.h>
#include <detector/event_detector.h>
#include <detector/timeout_detector.h>
#include <operator/operator.h>
#include <operator/led_operator_factory.h>
#include <drivers/led_driver.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define LED_DEVICE      "/sys/class/leds/input2::capslock/brightness"
#define NUM_OPERATION_ON_DETECTION 2

int main(void) {
  struct timeval kTime = {};
  const struct input_event kPressA = {kTime, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

  TriggerActionPair actions[NUM_OPERATION_ON_DETECTION+1];
  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  // "A" press triggers CAPS LED turn on.
  actions[0] = CreateTriggerActionPair(
                  CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA),
                  LedOperatorFactory(caps_led, OP_LED_TURN_ON));
  // 5 sec timeout triggers CAPS LED turn off.
  actions[1] = CreateTriggerActionPair(
                  CreateTimeOutDetector(5000, TIMER_ONE_SHOT),
                  LedOperatorFactory(caps_led, OP_LED_TURN_OFF));
  actions[2] = NULL;  // null-termination.

  ActiveObjectEngine engine = CreateActiveObjectEngine();
  Command cmd = CreateActionOnTriggerChain(actions, engine);
  FuelEngine(engine, cmd);

  EngineRuns(engine);

  // Need cleanup.
  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}