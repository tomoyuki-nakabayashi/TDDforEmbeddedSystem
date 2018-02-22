// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_KEY_INPUT_EVENT_H_
#define LED_CONTROLLER_KEY_INPUT_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum {
  INPUT_DEV_SUCCESS = 0,
  INPUT_DEV_INIT_ERROR = -1,
  INPUT_DEV_CLEANUP_ERROR = -2,
};

struct KeyInputDeviceStruct;
typedef struct KeyInputDeviceStruct *KeyInputDevice;

KeyInputDevice CreateKeyInputDevice();
int InitKeyInputDevice(KeyInputDevice dev, const char *device_file);
int CleanupKeyInputDevice(KeyInputDevice dev);
void DestroyKeyInputDevice(KeyInputDevice dev);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_