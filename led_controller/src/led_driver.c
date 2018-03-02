// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <led_driver.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <os/io.h>
#include <utils/logger.h>

typedef struct LedDriverStruct {
  int fd;
  LedStatus status;
} LedDriverStruct;

LedDriver CreateLedDriver() {
  LedDriver led = calloc(1, sizeof(LedDriverStruct));
  led->fd = -1;
  led->status = LED_UNKNOWN;

  return led;
}

int InitLedDriver(LedDriver self, const char* device_file) {
  self->fd = IO_OPEN(device_file, O_WRONLY|O_NONBLOCK);
  if (self->fd < 0) {
    // TODO: Look into possible errors.
    return LED_DRIVER_INIT_ERROR;
  }

  return LED_DRIVER_SUCCESS;
}

void DestroyLedDriver(LedDriver self) {
  if (self == NULL) return;

  free(self);
  self = NULL;
}
