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
  if(dev == NULL) return INPUT_DEV_INVALID_DEV;

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

int SetKeyInputDetectCondition(KeyInputDevice dev, const struct input_event *ev) {
  if (dev == NULL) return INPUT_DEV_INVALID_DEV;
  // Should I validate ev, here?
  memcpy(&dev->target_event, ev, sizeof(struct input_event));
}

static bool HasPendingEvent(struct libevdev *evdev, struct input_event *ev) {
  return libevdev_next_event(evdev, LIBEVDEV_READ_FLAG_NORMAL, ev)
          == LIBEVDEV_READ_STATUS_SUCCESS;
}

static bool IsTargetEvent(const struct input_event *target,
                          const struct input_event *ev) {
  return (target->type == ev->type
       && target->code == ev->code
       && target->value == ev->value);
}

int CheckKeyInput(KeyInputDevice dev) {
  if (dev == NULL) return INPUT_DEV_INVALID_DEV;
  struct input_event ev = {};
  if (HasPendingEvent(dev->evdev, &ev) && IsTargetEvent(&dev->target_event, &ev)) {
    return INPUT_DEV_EVENT_DETECTED;
  }
  return INPUT_DEV_NO_EVENT;
}

int CleanupKeyInputDevice(KeyInputDevice dev) {
  if(dev == NULL) return INPUT_DEV_INVALID_DEV;

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
