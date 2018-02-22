// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <libevdev/libevdev.h>
#include <os/io.h>
#include <utils/logger.h>

typedef struct KeyInputDeviceStruct {
  int fd;
  struct libevdev *evdev;
  struct input_event target_event;
} KeyInputDeviceStruct;

KeyInputDevice CreateKeyInputDevice() {
  KeyInputDevice dev = calloc(1, sizeof(KeyInputDeviceStruct));
  dev->fd = -1;
  dev->evdev = NULL;

  return dev;
}

int InitKeyInputDevice(KeyInputDevice dev, const char *device_file) {
  if(dev == NULL) return INPUT_DEV_INIT_ERROR;

  dev->fd = IO_OPEN(device_file, O_RDONLY|O_NONBLOCK);
  if (dev->fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return INPUT_DEV_INIT_ERROR;
  }

  int rc = libevdev_new_from_fd(dev->fd, &dev->evdev);
  if (rc < 0) return INPUT_DEV_INIT_ERROR;

  return INPUT_DEV_SUCCESS;
}

int SetKeyInputDetectCondition(KeyInputDevice dev, struct input_event *ev) {
  memcpy(&dev->target_event, ev, sizeof(struct input_event));
  return INPUT_DEV_SUCCESS;
}

static bool IsTargetEvent(struct input_event *target, struct input_event ev) {
  return target->type == ev->type
      && target->code == ev->code
      && target->value == ev->value;
}

bool KeyInputDetected(KeyInputDevice dev) {
  struct input_event ev;
  if (libevdev_next_event(dev->evdev, LIBEVDEV_READ_FLAG_NORMAL, &ev)
      == LIBEVDEV_READ_STATUS_SUCCESS) {
    return IsTargetEvent(dev->target_event, &ev);
  }
  return false;
}

int CleanupKeyInputDevice(KeyInputDevice dev) {
  if(dev == NULL) return INPUT_DEV_CLEANUP_ERROR;

  libevdev_free(dev->evdev);
  int rc = IO_CLOSE(dev->fd);
  if (rc < 0) return INPUT_DEV_CLEANUP_ERROR;

  return INPUT_DEV_SUCCESS;
}

void DestroyKeyInputDevice(KeyInputDevice dev) {
  if(dev == NULL) return;

  free(dev);
  dev = NULL;
}
