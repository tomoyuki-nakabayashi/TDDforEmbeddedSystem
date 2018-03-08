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
/* 
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
*/

TEST_F(LedControllerTest, AbstractUse) {
  auto engine = CreateLedControlEngine();
  DetectThenOperateCommand toggle{press_a, toggle_led};
  DetectThenOperateCommand finish{press_b, flush_engine};
  SelfAddCommand repeat_toggle{engine, toggle};
  SelfAddCommand repeat_finish{engine, finish};

  AddCommandToEngine(engine, repeat_toggle);
  AddCommandToEngine(engine, repeat_finish);

  if (!IsEmpty(engine)) {
    ExecuteCommand(engine);
  }

  DestroyLedControlEngine(engine);
}
}  // namespace led_controller_test
