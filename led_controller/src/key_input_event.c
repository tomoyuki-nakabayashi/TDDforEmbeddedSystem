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
  EventDetectorStruct base;
  int fd;
  struct libevdev *evdev;
  struct input_event target_event;
  const char *device_file;
} KeyInputDeviceStruct;

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

static int CheckKeyInputEvent(EventDetector base) {
  KeyInputDevice self = (KeyInputDevice)base;
  if (self == NULL || self->evdev == NULL) return EVENT_DETECTOR_ERROR;
  struct input_event ev = {};
  if (HasPendingEvent(self->evdev, &ev) && IsTargetEvent(&self->target_event, &ev)) {
    return EVENT_DETECTED;
  }
  return EVENT_NOT_DETECTED;
}

static int InitKeyInputDetector(EventDetector super) {
  if(super == NULL) return EVENT_DETECTOR_ERROR;
  KeyInputDevice self = (KeyInputDevice)super;

  self->fd = IO_OPEN(self->device_file, O_RDONLY|O_NONBLOCK);
  if (self->fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return EVENT_DETECTOR_ERROR;
  }

  int rc = libevdev_new_from_fd(self->fd, &self->evdev);
  if (rc < 0) return EVENT_DETECTOR_ERROR;

  return EVENT_DETECTOR_SUCCESS;
}

static int CleanupKeyInputDevice(EventDetector super) {
  if(super == NULL) return EVENT_DETECTOR_ERROR;
  KeyInputDevice self = (KeyInputDevice)super;

  libevdev_free(self->evdev);
  self->evdev = NULL;
  int rc = IO_CLOSE(self->fd);
  if (rc < 0) return EVENT_DETECTOR_ERROR;

  return EVENT_DETECTOR_SUCCESS;
}

static EventDetectorInterfaceStruct interface = {
  .Init = InitKeyInputDetector,
  .CheckEvent = CheckKeyInputEvent,
  .Cleanup = CleanupKeyInputDevice
};

EventDetector CreateKeyInputDetector(const char *device_file,
                                     const struct input_event *ev) {
  KeyInputDevice self = calloc(1, sizeof(KeyInputDeviceStruct));
  self->base.vtable = &interface;
  self->fd = -1;
  self->evdev = NULL;
  self->device_file = device_file;
  memcpy(&self->target_event, ev, sizeof(struct input_event));

  return (EventDetector)self;
}

void DestroyKeyInputDevice(EventDetector super) {
  if(super == NULL) return;

  free(super);
  super = NULL;
}
