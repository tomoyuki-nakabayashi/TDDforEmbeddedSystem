// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <led_driver.h>
#include <stdlib.h>

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
