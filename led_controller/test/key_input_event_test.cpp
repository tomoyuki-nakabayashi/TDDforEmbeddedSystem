// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.
//
// You might exucute these tests as root user.

#include <gtest/gtest.h>

namespace key_input_event_test {
class KeyInputEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(KeyInputEventTest, AbstractUse) {
  EXPECT_TRUE(InitKeyInputDevice("path to device file."));
  SetKeyInputEvent(condition);

  for (int i = 0; i < 10; i++)
    EXPECT_FALSE(IsEventDetected());
  EXPECT_TRUE(IsEventDetected());

  EXPECT_TRUE(FinalizeKeyInputDevice());
}

}  // namespace key_input_event_test
