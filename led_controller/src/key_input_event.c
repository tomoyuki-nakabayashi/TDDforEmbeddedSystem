// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <libevdev/libevdev.h>
#include <os/io.h>
#include <utils/logger.h>

typedef struct KeyInputDeviceStruct {
  int fd;
  struct libevdev *evdev;
} KeyInputDeviceStruct;

KeyInputDevice CreateKeyInputDevice() {
  KeyInputDevice dev = calloc(1, sizeof(KeyInputDeviceStruct));
  dev->fd = -1;
  dev->evdev = NULL;

  return dev;
}

bool InitKeyInputDevice(KeyInputDevice dev, const char *device_file) {
  if(dev == NULL) return false;

  dev->fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  if (dev->fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return false;
  }

  int rc = libevdev_new_from_fd(dev->fd, &dev->evdev);
  if (rc < 0) return false;

  return true;
}

bool CleanupKeyInputDevice(KeyInputDevice dev) {
  if(dev == NULL) return false;

  libevdev_free(dev->evdev);
  int rc = IO_CLOSE(dev->fd);
  if (rc < 0) return false;

  return true;
}

void DestroyKeyInputDevice(KeyInputDevice dev) {
  if(dev == NULL) return;

  free(dev);
  dev = NULL;
}
