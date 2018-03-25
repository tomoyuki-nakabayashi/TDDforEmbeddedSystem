// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <active_object_engine.h>
#include <drivers/led_driver.h>
#include <command/command.h>
#include <command/led_operator_factory.h>
#include <command/detect_chain.h>
#include <detector/key_input_detector.h>
#include <detector/event_detector.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define LED_DEVICE      "/sys/class/leds/input2::capslock/brightness"

int main(void) {
  struct timeval kTime = {};
  const struct input_event kPressUp = {kTime, EV_KEY, KEY_UP, INPUT_KEY_PRESSED};
  const struct input_event kPressDown = {kTime, EV_KEY, KEY_DOWN, INPUT_KEY_PRESSED};
  const struct input_event kPressLeft = {kTime, EV_KEY, KEY_LEFT, INPUT_KEY_PRESSED};
  const struct input_event kPressRight = {kTime, EV_KEY, KEY_RIGHT, INPUT_KEY_PRESSED};
  const struct input_event kPressA = {kTime, EV_KEY, KEY_A, INPUT_KEY_PRESSED};
  const struct input_event kPressB = {kTime, EV_KEY, KEY_B, INPUT_KEY_PRESSED};

  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  // Create components.
  EventDetector press_up = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressUp);
  EventDetector press_down = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressDown);
  EventDetector press_left = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressLeft);
  EventDetector press_right = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressRight);
  EventDetector press_a = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  EventDetector press_b = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressB);
  Command caps_on = LedOperatorFactory(caps_led, OP_LED_TURN_ON);

  ActiveObjectEngine engine = CreateActiveObjectEngine();
  Command acceptted = CreateDetectChain(press_a, engine, caps_on);
  Command uuddlrlrb = CreateDetectChain(press_b, engine, acceptted);
  Command uuddlrlr = CreateDetectChain(press_right, engine, uuddlrlrb);
  Command uuddlrl = CreateDetectChain(press_left, engine, uuddlrlr);
  Command uuddlr = CreateDetectChain(press_right, engine, uuddlrl);
  Command uuddl = CreateDetectChain(press_left, engine, uuddlr);
  Command uudd = CreateDetectChain(press_down, engine, uuddl);
  Command uud = CreateDetectChain(press_down, engine, uudd);
  Command uu = CreateDetectChain(press_up, engine, uud);
  Command start = CreateDetectChain(press_up, engine, uu);

  FuelEngine(engine, start);

  EngineRuns(engine);

  return 0;
}