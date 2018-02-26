// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_KEY_INPUT_EVENT_H_
#define LED_CONTROLLER_KEY_INPUT_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <linux/input.h>

enum {
  INPUT_DEV_SUCCESS = 0,
  INPUT_DEV_INIT_ERROR = -1,
  INPUT_DEV_CLEANUP_ERROR = -2,
};

enum {
  INPUT_KEY_RELEASED = 0,
  INPUT_KEY_PRESSED = 1,
};

struct KeyInputDeviceStruct;
typedef struct KeyInputDeviceStruct *KeyInputDevice;

KeyInputDevice CreateKeyInputDevice();
int InitKeyInputDevice(KeyInputDevice dev, const char *device_file);
void SetKeyInputDetectCondition(KeyInputDevice dev,
                                const struct input_event *ev);
bool KeyInputDetected(KeyInputDevice dev);
int CleanupKeyInputDevice(KeyInputDevice dev);
void DestroyKeyInputDevice(KeyInputDevice dev);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_