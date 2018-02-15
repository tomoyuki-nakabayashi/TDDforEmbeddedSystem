// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <key_input_event.h>
#include <fstream>
#include <os/mock_io.h>

MOCK_IO *mock_io {};

namespace led_controller_test {
using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;

class KeyInputEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
      mock_io = new MOCK_IO {};
      errno = 0;
    }

    virtual void TearDown()
    {
      errno = 0;
      delete mock_io;
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
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(3));
  EXPECT_TRUE(InitKeyInputDevice("./test_event"));
}

TEST_F(KeyInputEventTest, FailToInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _))
    .WillOnce(Invoke([](const char*, int) {
      errno = EACCES; return -1; }));
  EXPECT_FALSE(InitKeyInputDevice("./file_not_found"));
}
}  // namespace led_controller_test
