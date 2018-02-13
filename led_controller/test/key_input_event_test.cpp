// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <key_input_event.h>

namespace led_controller_test {
class KeyInputEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};
/* 
TEST_F(KeyInputEventTest, AbstractUse) {
  EXPECT_TRUE(InitKeyInputDevice("path to device file."));
  SetKeyInputEventWatcher(condition);

  for (int i = 0; i < 10; i++)
    EXPECT_FALSE(EventDetected());
  EXPECT_TRUE(EventDetected());

  EXPECT_TRUE(FinalizeKeyInputDevice());
}
*/

TEST_F(KeyInputEventTest, CanInitInputDevice) {
  EXPECT_TRUE(InitKeyInputDevice());
}
}  // namespace led_controller_test
