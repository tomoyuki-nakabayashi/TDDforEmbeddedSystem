// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <key_input_event.h>
#include <fstream>

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
  SetKeyInputEventListener(condition);

  for (int i = 0; i < 10; i++)
    EXPECT_FALSE(EventDetected());
  EXPECT_TRUE(EventDetected());

  EXPECT_TRUE(FinalizeKeyInputDevice());
}
*/

TEST_F(KeyInputEventTest, CanInitInputDevice) {
  std::ofstream("./test_event");
  EXPECT_TRUE(InitKeyInputDevice("./test_event"));
  std::remove("./test_event");
}

TEST_F(KeyInputEventTest, FailToInitInputDevice) {
  EXPECT_FALSE(InitKeyInputDevice("/dev/input/not_found"));
}
}  // namespace led_controller_test
