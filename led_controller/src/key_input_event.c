// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <libevdev/libevdev.h>
#include <os/io.h>
#include <utils/logger.h>

static int fd = 0;
static struct libevdev *evdev = NULL;

bool InitKeyInputDevice(const char *device_file) {
  fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  if (fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return false;
  }

  int rc = libevdev_new_from_fd(fd, &evdev);
  if (rc < 0) return false;

  return true;
}

bool CleanupKeyInputDevice() {
  libevdev_free(evdev);
  int rc = close(fd);
  if (rc < 0) return false;

  return true;
}
