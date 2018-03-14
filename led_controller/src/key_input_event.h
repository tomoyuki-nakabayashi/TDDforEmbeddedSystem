// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_KEY_INPUT_EVENT_H_
#define LED_CONTROLLER_KEY_INPUT_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <linux/input.h>
#include <event_detector.h>

enum {
  INPUT_KEY_RELEASED = 0,
  INPUT_KEY_PRESSED = 1,
};

struct KeyInputDeviceStruct;
typedef struct KeyInputDeviceStruct *KeyInputDevice;

// Creates an instance and returns EventDetector interface.
// This just allocates a memory area and copies given parameters.
// params: device_file  Path to target device file.
//         ev           input_event to be detected by CheckEvent.
EventDetector CreateKeyInputDetector(const char *device_file,
                                     const struct input_event *ev);

// Destroy the instance.
void DestroyKeyInputDevice(EventDetector super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_
