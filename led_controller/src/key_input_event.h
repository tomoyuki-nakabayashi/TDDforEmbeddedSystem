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

// Create an instance.
KeyInputDevice CreateKeyInputDevice();

// Initialize key input device.
// params: dev  Must create an instance by CreateKeyInputDevice() before use.
// return: INPUT_DEV_SUCCESS if successfully initialize input device's handler.
//         INPUT_DEV_INVALID_DEV if dev is not initialized.
//         Otherwise, INPUT_DEV_INIT_ERROR
int InitKeyInputDevice(KeyInputDevice dev, const char *device_file);

// Set a condition you want to detect.
// params: dev  Must initialize an instance by InitKeyInputDevice() before use.
//         ev   Target event. time member will be ignored.
// return: INPUT_DEV_SUCCESS if dev has already been initialized.
//         Otherwire, INPUT_DEV_INVALID_DEV
int SetKeyInputDetectCondition(KeyInputDevice dev, const struct input_event *ev);

// Check key input you have set by SetKeyInputDetectCondition().
// params: dev  Must initialize an instance by InitKeyInputDevice() before use.
// return: INPUT_DEV_EVENT_DETECTED if target event detected.
//         INPUT_DEV_INVALID_DEV if dev is not initialized.
//         Otherwise, INPUT_DEV_NO_EVENT
int CheckKeyInput(KeyInputDevice dev);

// Cleanup key input device. Should call this function before destroy.
// Should not use the device after this function called.
// params: dev  Must initialize an instance by InitKeyInputDevice() before use.
// return: INPUT_DEV_SUCCESS if no error occurs.
//         INPUT_DEV_INVALID_DEV if dev is not initialized.
//         Otherwise, INPUT_DEV_CLEANUP_ERROR
int CleanupKeyInputDevice(KeyInputDevice dev);

// Destroy the instance.
void DestroyKeyInputDevice(KeyInputDevice dev);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_
