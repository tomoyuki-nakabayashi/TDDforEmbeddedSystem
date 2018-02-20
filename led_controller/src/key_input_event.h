// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_KEY_INPUT_EVENT_H_
#define LED_CONTROLLER_KEY_INPUT_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct KeyInputDeviceStruct;
typedef struct KeyInputDeviceStruct *KeyInputDevice;

KeyInputDevice CreateKeyInputDevice();
bool InitKeyInputDevice(KeyInputDevice dev, const char *device_file);
bool CleanupKeyInputDevice(KeyInputDevice dev);
void DestroyKeyInputDevice(KeyInputDevice dev);

#include "key_input_event_private.h"

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_KEY_INPUT_EVENT_H_