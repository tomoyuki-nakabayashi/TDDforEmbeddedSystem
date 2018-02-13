// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>

#define DEVICE_FILE "/dev/input/event2"

bool InitKeyInputDevice() {
  int fd = open(DEVICE_FILE, O_RDONLY|O_NONBLOCK);
  if (fd < 0) return false;

  return true;
}
