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

// Creates an instance and returns EventDetector interface.
// params: device_file  Path to target device file.
//         ev           input_event to be detected by CheckEvent.
EventDetector CreateKeyInputDetector(const char *device_file,
                                     const struct input_event *ev);

// Initialize key input device.
// params: super Must create an instance by CreateKeyInputDetector() before use.
// return:EVENT_SUCCESS if successfully initialize input device's handler.
//         EVENT_ERROR if dev is not initialized.
int InitKeyInputDetector(EventDetector super);

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
int CleanupKeyInputDevice(EventDetector super);

// Destroy the instance.
void DestroyKeyInputDevice(EventDetector super);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_
