// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <os/io.h>

bool InitKeyInputDevice(const char *device_file) {
  int fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  if (fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return false;
  }

  return true;
}
