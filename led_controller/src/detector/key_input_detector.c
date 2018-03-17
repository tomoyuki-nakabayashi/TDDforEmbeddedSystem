// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <detector/key_input_detector.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <libevdev/libevdev.h>
#include <os/io.h>
#include <utils/logger.h>

typedef struct KeyInputDetectorStruct {
  EventDetectorStruct base;
  int fd;
  struct libevdev *evdev;
  struct input_event target_event;
  const char *device_file;
} KeyInputDetectorStruct;

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
  KeyInputDetector self = (KeyInputDetector)base;
  if (self == NULL || self->evdev == NULL) return DETECTOR_ERROR;
  struct input_event ev = {};
  if (HasPendingEvent(self->evdev, &ev) && IsTargetEvent(&self->target_event, &ev)) {
    return DETECTOR_EVENT_DETECTED;
  }
  return DETECTOR_EVENT_NOT_DETECTED;
}

static int InitKeyInputDetector(EventDetector super) {
  if(super == NULL) return DETECTOR_ERROR;
  KeyInputDetector self = (KeyInputDetector)super;

  self->fd = IO_OPEN(self->device_file, O_RDONLY|O_NONBLOCK);
  if (self->fd < 0) {
    if (errno == EACCES)
      DEBUG_LOG("Fail to open file. You may need root permission.");
    return DETECTOR_ERROR;
  }

  int rc = libevdev_new_from_fd(self->fd, &self->evdev);
  if (rc < 0) return DETECTOR_ERROR;

  return DETECTOR_SUCCESS;
}

static int CleanupKeyInputDetector(EventDetector super) {
  if(super == NULL) return DETECTOR_ERROR;
  KeyInputDetector self = (KeyInputDetector)super;

  libevdev_free(self->evdev);
  self->evdev = NULL;
  int rc = IO_CLOSE(self->fd);
  if (rc < 0) return DETECTOR_ERROR;

  return DETECTOR_SUCCESS;
}

static EventDetectorInterfaceStruct interface = {
  .Start = InitKeyInputDetector,
  .CheckEvent = CheckKeyInputEvent,
  .Cleanup = CleanupKeyInputDetector
};

EventDetector CreateKeyInputDetector(const char *device_file,
                                     const struct input_event *ev) {
  KeyInputDetector self = calloc(1, sizeof(KeyInputDetectorStruct));
  self->base.vtable = &interface;
  self->fd = -1;
  self->evdev = NULL;
  self->device_file = device_file;
  memcpy(&self->target_event, ev, sizeof(struct input_event));

  return (EventDetector)self;
}

void DestroyKeyInputDetector(EventDetector super) {
  if(super == NULL) return;

  free(super);
  super = NULL;
}
