// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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

  EventDetector detectors[NUM_OPERATION_ON_DETECTION];
  detectors[0] = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  detectors[1] = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
  
  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  Operator operators[NUM_OPERATION_ON_DETECTION];
  operators[0] = LedOperatorFactory(caps_led, OP_LED_TURN_ON);
  operators[1] = LedOperatorFactory(caps_led, OP_LED_TURN_OFF);

  for(int i = 0; i < NUM_OPERATION_ON_DETECTION; i++) {
    StartEventDetector(detectors[i]);
    while(CheckEvent(detectors[i]) != DETECTOR_EVENT_DETECTED) {}

    TriggerOperation(operators[i]);
  }

  for(int i = 0; i < NUM_OPERATION_ON_DETECTION; i++) {
    CleanupEventDetector(detectors[i]);
  }

  DestroyKeyInputDetector(detectors[0]);
  DestroyTimeOutDetector(detectors[1]);
  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}