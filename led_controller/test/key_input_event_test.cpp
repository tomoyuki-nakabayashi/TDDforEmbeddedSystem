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
using ::testing::SetArgPointee;

class KeyInputEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
      dev_ = CreateKeyInputDevice();
      mock_io = new MOCK_IO {};
      mock_libevdev = new MOCK_LIBEVDEV {};
      errno = 0;
    }

    virtual void TearDown()
    {
      errno = 0;
      delete mock_libevdev;
      delete mock_io;
      DestroyKeyInputDevice(dev_);
    }

 protected:
    KeyInputDevice dev_;
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

static constexpr char kFilePath[]  {"/dev/input/event2"};

TEST_F(KeyInputEventTest, CanInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(3));
  EXPECT_EQ(INPUT_DEV_SUCCESS, InitKeyInputDevice(dev_, kFilePath));
}

TEST_F(KeyInputEventTest, FailToInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = ENOENT; return -1; }));
  EXPECT_EQ(INPUT_DEV_INIT_ERROR, InitKeyInputDevice(dev_, "./invalid"));
}

TEST_F(KeyInputEventTest, FileOpenPermissionDenied) {
  std::unique_ptr<char[]> spy {new char[128]};
  set_DEBUG_LOG_spy(spy.get(), 128);

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = EACCES; return -1; }));

  EXPECT_EQ(INPUT_DEV_INIT_ERROR, InitKeyInputDevice(dev_, kFilePath));
  EXPECT_STREQ("Fail to open file. You may need root permission.",
               spy.get());
}

TEST_F(KeyInputEventTest, CanInitEvdev) {
  const int kFileDescriptor = 3;
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(kFileDescriptor, _))
    .WillOnce(Return(0));

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(kFileDescriptor));
  EXPECT_EQ(INPUT_DEV_SUCCESS, InitKeyInputDevice(dev_, kFilePath));
}

TEST_F(KeyInputEventTest, InitEvdevFailed) {
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(_, _))
    .WillOnce(Return(-EBADF));

  EXPECT_EQ(INPUT_DEV_INIT_ERROR, InitKeyInputDevice(dev_, kFilePath));
}

static void InitHelper(KeyInputDevice dev,
                       const char *path,
                       int fd,
                       int res_evdev_new) {
  EXPECT_CALL(*mock_io, IO_OPEN(path, _)).WillOnce(Return(fd));
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(fd, _))
    .WillOnce(Return(res_evdev_new));

  InitKeyInputDevice(dev, path);
}

TEST_F(KeyInputEventTest, CanCleanupKeyInputDevice) {
  constexpr int kFd = 3;
  InitHelper(dev_, kFilePath, kFd, 0);

  EXPECT_CALL(*mock_libevdev, libevdev_free(_)).Times(1);
  EXPECT_CALL(*mock_io, IO_CLOSE(kFd)).WillOnce(Return(0));

  EXPECT_EQ(INPUT_DEV_SUCCESS, CleanupKeyInputDevice(dev_));
}

TEST_F(KeyInputEventTest, CleanupKeyInputDeviceFailed) {
  EXPECT_CALL(*mock_io, IO_CLOSE(-1)).WillOnce(Return(-1));

  EXPECT_EQ(INPUT_DEV_CLEANUP_ERROR, CleanupKeyInputDevice(dev_));
}

static constexpr input_event kPressA {timeval{}, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

TEST_F(KeyInputEventTest, AllApiHaveNullPointerGuard) {
  const KeyInputDevice kNullPointer = NULL;
  EXPECT_EQ(INPUT_DEV_INVALID_DEV, InitKeyInputDevice(kNullPointer, kFilePath));
  EXPECT_EQ(INPUT_DEV_INVALID_DEV, CleanupKeyInputDevice(kNullPointer));
  EXPECT_EQ(INPUT_DEV_INVALID_DEV, SetKeyInputDetectCondition(kNullPointer, &kPressA));
  EXPECT_EQ(INPUT_DEV_INVALID_DEV, KeyInputDetected(kNullPointer));
}

TEST_F(KeyInputEventTest, DetectCondition) {
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _)).WillOnce(
    DoAll(SetArgPointee<2>(kPressA), Return(LIBEVDEV_READ_STATUS_SUCCESS)));

  SetKeyInputDetectCondition(dev_, &kPressA);
  EXPECT_TRUE(KeyInputDetected(dev_));
}

TEST_F(KeyInputEventTest, CannotDetectEvent) {
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _))
    .WillOnce(Return(-EAGAIN));

  SetKeyInputDetectCondition(dev_, &kPressA);
  EXPECT_FALSE(KeyInputDetected(dev_));
}

TEST_F(KeyInputEventTest, DetectOnlyInterestedEvent) {
  constexpr input_event kPressB {timeval{}, EV_KEY, KEY_B, INPUT_KEY_PRESSED};
  constexpr input_event kReleaseA {timeval{}, EV_KEY, KEY_A, INPUT_KEY_RELEASED};
  constexpr auto kSuccess = LIBEVDEV_READ_STATUS_SUCCESS;
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _))
    .WillOnce(Return(-EAGAIN))
    .WillOnce(DoAll(SetArgPointee<2>(kPressB), Return(kSuccess)))
    .WillOnce(DoAll(SetArgPointee<2>(kReleaseA), Return(kSuccess)))
    .WillOnce(DoAll(SetArgPointee<2>(kPressA), Return(kSuccess)));

  SetKeyInputDetectCondition(dev_, &kPressA);
  EXPECT_FALSE(KeyInputDetected(dev_));
  EXPECT_FALSE(KeyInputDetected(dev_));
  EXPECT_FALSE(KeyInputDetected(dev_));
  EXPECT_TRUE(KeyInputDetected(dev_));
}
}  // namespace led_controller_test
