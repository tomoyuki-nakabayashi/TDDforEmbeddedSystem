// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <key_input_event.h>

int main(void) {
  //InitKeyInputDevice("/dev/input/event2");
  InitKeyInputDevice("/dev/input/not_found");
  return 0;
}