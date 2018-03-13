// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <key_input_event.h>
#include <event_detector.h>
#include <led_driver.h>
#include <utils/logger.h>

#define KEYBOARD_DEVICE "/dev/input/event2"
#define LED_DEVICE      "/sys/class/leds/input2::capslock/brightness"

int main(void) {
  struct timeval time = {};
  const struct input_event kPressA = {time, EV_KEY, KEY_A, INPUT_KEY_PRESSED};
  EventDetector press_a = CreateKeyInputDetector(KEYBOARD_DEVICE, &kPressA);
  if (InitEventDetector(press_a) != EVENT_SUCCESS) {
    DEBUG_LOG("Fail to init input device\n");
    exit(1);
  }

  LedDriver caps_led = CreateLedDriver();
  if (InitLedDriver(caps_led, LED_DEVICE) != LED_DRIVER_SUCCESS) {
    DEBUG_LOG("Fail to init led device\n");
    exit(1);
  }

  while(1) {
    if(CheckEvent(press_a) == EVENT_DETECTED)
      ToggleLed(caps_led);
  }

  CleanupEventDetector(press_a);
  DestroyKeyInputDevice(press_a);

  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}