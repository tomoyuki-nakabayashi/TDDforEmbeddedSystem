// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
extern "C" {
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
}

namespace evdev_sample_test {
class EvdevSampleTest : public ::testing::Test {
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(EvdevSampleTest, InputEventFileCanOpen) {
  struct libevdev *dev = NULL;
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  // You might exucute the test as root user.
  EXPECT_GE(rc, 0);
}

TEST_F(EvdevSampleTest, ReturnsEAGAIN) {
  struct libevdev *dev = NULL;
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  struct input_event ev;
  rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  EXPECT_EQ(-EAGAIN, rc);
}
}