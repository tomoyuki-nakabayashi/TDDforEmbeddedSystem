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
#include <command/led_operator_factory.h>
#include <drivers/led_driver.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define LED_DEVICE      "/sys/class/leds/input2::capslock/brightness"
#define NUM_OPERATION_ON_DETECTION 2

int main(void) {
  struct timeval kTime = {};
  const struct input_event kPressA = {kTime, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  // Create components.
  EventDetector press_a = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  EventDetector five_sec_timeout = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
  Command caps_on = LedOperatorFactory(caps_led, OP_LED_TURN_ON);
  Command caps_off = LedOperatorFactory(caps_led, OP_LED_TURN_OFF);

  TriggerActionPair actions[NUM_OPERATION_ON_DETECTION+1];
  actions[0] = CreateTriggerActionPair(press_a, caps_on);
  actions[1] = CreateTriggerActionPair(five_sec_timeout, caps_off);
  actions[2] = NULL;  // null-termination.

  ActiveObjectEngine engine = CreateActiveObjectEngine();
  Command cmd = CreateActionOnTriggerChain(actions, engine);
  FuelEngine(engine, cmd);

  EngineRuns(engine);

  // Need cleanup.
  DestroyActionOnTriggerChain(cmd);
  DestroyActiveObjectEngine(engine);
  DestroyTriggerActionPair(actions[0]);
  DestroyTriggerActionPair(actions[1]);
  DestroyLedOperator(caps_on);
  DestroyLedOperator(caps_off);
  DestroyKeyInputDetector(press_a);
  DestroyTimeOutDetector(five_sec_timeout);
  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}