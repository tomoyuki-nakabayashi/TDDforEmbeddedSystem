// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>
#include <assert.h>

bool InitKeyInputDevice(const char *device_file) {
  int fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  assert(!(fd < 0));
  if (fd < 0) return false;

  return true;
}
