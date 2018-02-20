// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <stddef.h>

int main(void) {
  KeyInputDevice dev = CreateKeyInputDevice();
  InitKeyInputDevice(dev, "/dev/input/event2");
  return 0;
}