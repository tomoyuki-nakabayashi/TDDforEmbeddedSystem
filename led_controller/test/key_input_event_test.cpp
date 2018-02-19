// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <key_input_event.h>
#include <fstream>
#include <memory>
#include <os/mock_io.h>
#include <utils/logger_spy.h>
#include <libs/mock_libevdev.h>
#include <errno.h>

MOCK_IO *mock_io {};
MOCK_LIBEVDEV *mock_libevdev {};

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
      mock_libevdev = new MOCK_LIBEVDEV {};
      errno = 0;
    }

    virtual void TearDown()
    {
      errno = 0;
      delete mock_libevdev;
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
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = ENOENT; return -1; }));
  EXPECT_FALSE(InitKeyInputDevice("./file_not_found"));
}

TEST_F(KeyInputEventTest, FileOpenPermissionDenied) {
  std::unique_ptr<char[]> spy {new char[128]};
  set_DEBUG_LOG_spy(spy.get(), 128);

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = EACCES; return -1; }));

  EXPECT_FALSE(InitKeyInputDevice("./test_event"));
  EXPECT_STREQ("Fail to open file. You may need root permission.",
               spy.get());
}

TEST_F(KeyInputEventTest, CanInitEvdev) {
  const int kFileDescriptor = 3;
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(kFileDescriptor, _))
    .WillOnce(Return(0));

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(kFileDescriptor));
  EXPECT_TRUE(InitKeyInputDevice("./test_event"));
}

TEST_F(KeyInputEventTest, InitEvdevFailed) {
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(_, _))
    .WillOnce(Return(-EBADF));

  EXPECT_FALSE(InitKeyInputDevice("./test_event"));
}

TEST_F(KeyInputEventTest, CleanupKeyInputDevice) {
  EXPECT_FALSE(CleanupKeyInputDevice());

  InitKeyInputDevice();
  EXPECT_TRUE(CleanupKeyInputDevice());

  EXPECT_FALSE(CleanupKeyInputDevice());
}

}  // namespace led_controller_test
