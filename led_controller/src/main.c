// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <detector/key_input_detector.h>
#include <detector/event_detector.h>
#include <detector/timeout_detector.h>
#include <led_driver.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define LED_DEVICE      "/sys/class/leds/input2::capslock/brightness"
#define NUM_DETECTORS 2

int main(void) {
  struct timeval kTime = {};
  const struct input_event kPressA = {kTime, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

  EventDetector detectors[NUM_DETECTORS+1];  // To null-terminate
  detectors[0] = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  detectors[1] = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
  detectors[2] = NULL;  // null-terminate
  
  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  for(int i = 0; detectors[i] != NULL; i++) {
    StartEventDetector(detectors[i]);
    while(CheckEvent(detectors[i]) != DETECTOR_EVENT_DETECTED) {}

    ToggleLed(caps_led);
  }

  for(int i = 0; detectors[i] != NULL; i++) {
    CleanupEventDetector(detectors[i]);
    DestroyKeyInputDetector(detectors[i]);
  }

  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}