// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_KEY_INPUT_EVENT_PRIVATE_H_
#define LED_CONTROLLER_KEY_INPUT_EVENT_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <key_input_event.h>

typedef struct KeyInputDeviceStruct {
  int fd;
  struct libevdev *evdev;
} KeyInputDeviceStruct;

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_PRIVATE_H_