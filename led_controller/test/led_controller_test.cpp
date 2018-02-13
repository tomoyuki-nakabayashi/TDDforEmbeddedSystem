// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>

namespace led_controller_test {
class LedControllerTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(LedControllerTest, AbstractUse) {
  InitKeyInputDevice("path to key input device.");
  InitLedDevice("path to led device.")
  SetKeyInputEventWatcher(condition);

  while (1) {
    if (EventDetected()) {
      ToggleLedDevice();
    }
  }

  FinalizeKeyInputDevice();
  FinalizeLedDevice();
}

}  // namespace led_controller_test
