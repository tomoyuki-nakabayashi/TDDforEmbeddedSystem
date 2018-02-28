// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <stddef.h>

int main(void) {
  KeyInputDevice dev = CreateKeyInputDevice();
  InitKeyInputDevice(dev, "/dev/input/event2");
  struct timeval time = {};
  const struct input_event kPressA = {time, EV_KEY, KEY_A, INPUT_KEY_PRESSED};
  SetKeyInputDetectCondition(dev, &kPressA);

  int count = 0;
  while(count < 2) {
    if(CheckKeyInput(dev) == INPUT_DEV_EVENT_DETECTED) count++;
  }

  CleanupKeyInputDevice(dev);
  DestroyKeyInputDevice(dev);

  return 0;
}