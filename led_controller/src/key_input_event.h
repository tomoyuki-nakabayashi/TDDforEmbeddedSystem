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
  INPUT_DEV_EVENT_DETECTED = 1,
  INPUT_DEV_SUCCESS = 0,
  INPUT_DEV_INIT_ERROR = -1,
  INPUT_DEV_CLEANUP_ERROR = -2,
  INPUT_DEV_INVALID_DEV = -3,    // Given KeyInputDevice is null.
  INPUT_DEV_NO_EVENT = -4,
};

enum {
  INPUT_KEY_RELEASED = 0,
  INPUT_KEY_PRESSED = 1,
};

struct KeyInputDeviceStruct;
typedef struct KeyInputDeviceStruct *KeyInputDevice;

KeyInputDevice CreateKeyInputDevice();

// params: dev  You must create this by CreateKeyInputDevice()
//              before you use this function.
// return: INPUT_DEV_SUCCESS if successfully initialize input device's handler.
//         INPUT_DEV_INVALID_DEV if given device has null pointer.
//         otherwise, INPUT_DEV_INIT_ERROR
int InitKeyInputDevice(KeyInputDevice dev, const char *device_file);

// params: dev  You must initialize this by InitKeyInputDevice() before use.
//         ev   Your interested event. time member will be ignored.
int SetKeyInputDetectCondition(KeyInputDevice dev, const struct input_event *ev);


int CheckKeyInput(KeyInputDevice dev);
int CleanupKeyInputDevice(KeyInputDevice dev);
void DestroyKeyInputDevice(KeyInputDevice dev);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_