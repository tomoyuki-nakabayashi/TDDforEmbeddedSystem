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

typedef struct {
  int fd;
  struct libevdev *evdev;
} EvdevHandlerStruct;

enum {INVALID_FD = -1};
static EvdevHandlerStruct ev = {INVALID_FD, NULL};

bool InitKeyInputDevice(const char *device_file) {
  ev.fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  if (ev.fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return false;
  }

  int rc = libevdev_new_from_fd(ev.fd, &ev.evdev);
  if (rc < 0) return false;

  return true;
}

bool CleanupKeyInputDevice() {
  libevdev_free(ev.evdev);
  int rc = IO_CLOSE(ev.fd);
  if (rc < 0) return false;

  return true;
}
