// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LED_CONTROLLER_OS_TIME_H_
#define MOCK_LED_CONTROLLER_OS_TIME_H_

#include <gmock/gmock.h>
#include <cstdint>
#include <os/time.h>

class MOCK_TIME {
 public:
    MOCK_METHOD0(GET_MSEC_OF_DAY, uint32_t(void));
};

extern MOCK_TIME *mock_time;

extern "C" {
  uint32_t GET_MSEC_OF_DAY() {
    return mock_time->GET_MSEC_OF_DAY();
  }
}

#endif  // MOCK_LED_CONTROLLER_OS_TIME_H_
