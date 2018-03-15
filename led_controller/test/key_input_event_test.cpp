// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <key_input_event.h>
#include <event_detector.h>
#include <fstream>
#include <memory>
#include <os/mock_io.h>
#include <utils/logger_spy.h>
#include <libs/mock_libevdev.h>
#include <errno.h>

// Definition of mock_io is in mock_io.cpp
MOCK_LIBEVDEV *mock_libevdev {};

namespace led_controller_test {
using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::SetArgPointee;

static constexpr char kFilePath[]  {"/dev/input/event2"};

class KeyInputEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
      dev_ = CreateKeyInputDetector(kFilePath, &in_ev_);
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
    EventDetector dev_;
    input_event in_ev_;
};
/* 
TEST_F(KeyInputEventTest, AbstractUse) {
  auto detector = CreateKeyInputDetector("path", condition);
  EXPECT_NE(nullptr, detector);
  EXPECT_TRUE(InitDetector(detector));

  for (int i = 0; i < 10; i++)
    EXPECT_FALSE(CheckEvent(detector));
  EXPECT_TRUE(CheckEvent(detector));

  EXPECT_TRUE(CleaupDetector(detector));
}
*/

TEST_F(KeyInputEventTest, CanInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(3));
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, StartEventDetector(dev_));
}

TEST_F(KeyInputEventTest, FailToInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = ENOENT; return -1; }));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(dev_));
}

TEST_F(KeyInputEventTest, FileOpenPermissionDenied) {
  std::unique_ptr<char[]> spy {new char[128]};
  set_DEBUG_LOG_spy(spy.get(), 128);

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(
    Invoke([](const char*, int) { errno = EACCES; return -1; }));

  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(dev_));
  EXPECT_STREQ("Fail to open file. You may need root permission.",
               spy.get());
}

TEST_F(KeyInputEventTest, CanInitEvdev) {
  const int kFileDescriptor = 3;
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(kFileDescriptor, _))
    .WillOnce(Return(0));

  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(kFileDescriptor));
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, StartEventDetector(dev_));
}

TEST_F(KeyInputEventTest, InitEvdevFailed) {
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(_, _))
    .WillOnce(Return(-EBADF));

  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(dev_));
}

static void InitHelper(EventDetector dev,
                       int fd,
                       int res_evdev_new) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(fd));
  EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(fd, _))
    .WillOnce(Return(res_evdev_new));

  StartEventDetector(dev);
}

TEST_F(KeyInputEventTest, CanCleanupKeyInputDevice) {
  constexpr int kFd = 3;
  InitHelper(dev_, kFd, 0);

  EXPECT_CALL(*mock_libevdev, libevdev_free(_)).Times(1);
  EXPECT_CALL(*mock_io, IO_CLOSE(kFd)).WillOnce(Return(0));

  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, CleanupEventDetector(dev_));
}

TEST_F(KeyInputEventTest, CleanupKeyInputDeviceFailed) {
  EXPECT_CALL(*mock_io, IO_CLOSE(-1)).WillOnce(Return(-1));

  EXPECT_EQ(EVENT_DETECTOR_ERROR, CleanupEventDetector(dev_));
}

static constexpr input_event kPressA {timeval{}, EV_KEY, KEY_A, INPUT_KEY_PRESSED};

TEST_F(KeyInputEventTest, AllApiHaveNullPointerGuard) {
  const KeyInputDevice kNullPointer = NULL;
  const EventDetector kNullDetector = nullptr;
  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(kNullDetector));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CleanupEventDetector(kNullDetector));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CheckEvent((EventDetector)kNullPointer));
}

class KeyInputEventDetectionTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
      mock_io = new MOCK_IO {};
      mock_libevdev = new MOCK_LIBEVDEV {};
      dev_ = CreateKeyInputDetector(kFilePath, &kPressA);
      EXPECT_CALL(*mock_libevdev, libevdev_new_from_fd(_, _)).WillOnce(
        Invoke([](int, libevdev **dev) {
          *dev = reinterpret_cast<libevdev*>(0x12345678); return 0;} )
      ).RetiresOnSaturation();
      EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(3));
      StartEventDetector(dev_);
    }

    virtual void TearDown()
    {
      DestroyKeyInputDevice(dev_);
      delete mock_libevdev;
      delete mock_io;
    }

 protected:
    EventDetector dev_;
};

TEST_F(KeyInputEventDetectionTest, DetectTargetEvent) {
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _)).WillOnce(
    DoAll(SetArgPointee<2>(kPressA), Return(LIBEVDEV_READ_STATUS_SUCCESS)));

  EXPECT_EQ(EVENT_DETECTED, CheckEvent(dev_));
}

TEST_F(KeyInputEventDetectionTest, DetectUsingInterface) {
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _)).WillOnce(
    DoAll(SetArgPointee<2>(kPressA), Return(LIBEVDEV_READ_STATUS_SUCCESS)));

  EXPECT_EQ(EVENT_DETECTED, CheckEvent(dev_));
}

TEST_F(KeyInputEventDetectionTest, CannotDetectEvent) {
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _))
    .WillOnce(Return(-EAGAIN));

  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(dev_));
}

TEST_F(KeyInputEventDetectionTest, DetectOnlyInterestedEvent) {
  constexpr input_event kPressB {timeval{}, EV_KEY, KEY_B, INPUT_KEY_PRESSED};
  constexpr input_event kReleaseA {timeval{}, EV_KEY, KEY_A, INPUT_KEY_RELEASED};
  constexpr auto kSuccess = LIBEVDEV_READ_STATUS_SUCCESS;
  EXPECT_CALL(*mock_libevdev, libevdev_next_event(_, _, _))
    .WillOnce(Return(-EAGAIN))
    .WillOnce(DoAll(SetArgPointee<2>(kPressB), Return(kSuccess)))
    .WillOnce(DoAll(SetArgPointee<2>(kReleaseA), Return(kSuccess)))
    .WillOnce(DoAll(SetArgPointee<2>(kPressA), Return(kSuccess)));

  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(dev_));
  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(dev_));
  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(dev_));
  EXPECT_EQ(EVENT_DETECTED, CheckEvent(dev_));
}

TEST_F(KeyInputEventDetectionTest, FailOperationAfterCleanup) {
  EXPECT_CALL(*mock_libevdev, libevdev_free(_)).Times(1);

  auto dev = CreateKeyInputDetector(kFilePath, &kPressA);
  CleanupEventDetector(dev);
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CheckEvent(dev));

  DestroyKeyInputDevice(dev);
}

TEST_F(KeyInputEventDetectionTest, TestFree) {
  int *mem = static_cast<int*>(calloc(1, sizeof(int)));
  int *tmp = mem;

  free(mem);
  EXPECT_EQ(tmp, mem);
}

} //  led_controller_test
