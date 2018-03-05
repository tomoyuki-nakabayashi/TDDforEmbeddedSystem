// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <led_driver.h>
#include <stddef.h>

int main(void) {
  KeyInputDevice press_a = CreateKeyInputDevice();
  InitKeyInputDevice(press_a, "/dev/input/event2");
  struct timeval time = {};
  const struct input_event kPressA = {time, EV_KEY, KEY_A, INPUT_KEY_PRESSED};
  SetKeyInputDetectCondition(press_a, &kPressA);

  LedDriver caps_led = CreateLedDriver();
  InitLedDriver(caps_led, "/sys/class/leds/input2::capslock/brightness");
  TurnOffLed(caps_led);

  while(1) {
    if(CheckKeyInput(press_a) == INPUT_DEV_EVENT_DETECTED)
      ToggleLed(caps_led);
  }

  CleanupKeyInputDevice(press_a);
  DestroyKeyInputDevice(press_a);

  CleanupLedDriver(caps_led);
  DestroyLedDriver(caps_led);

  return 0;
}