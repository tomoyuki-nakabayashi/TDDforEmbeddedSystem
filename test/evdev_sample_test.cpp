// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.
//
// You might exucute these tests as root user.

#include <gtest/gtest.h>
#include <thread>
extern "C" {
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
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

TEST_F(EvdevSampleTest, InputEventFileCanOpenAsRoot) {
  struct libevdev *dev = nullptr;
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  EXPECT_GE(rc, 0);
}

TEST_F(EvdevSampleTest, ReturnsEAGAIN) {
  struct libevdev *dev = nullptr;
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  struct input_event ev {};
  rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  EXPECT_EQ(-EAGAIN, rc);
}

static void write_key_event(int code, int value, int fd)
{
  struct input_event key_event;
  
  gettimeofday(&key_event.time, NULL);
  key_event.type = EV_KEY;
  key_event.code = code;
  key_event.value = value;
  write(fd, &key_event, sizeof(key_event));
}

TEST_F(EvdevSampleTest, SuccessCaptureEvent) {
  struct libevdev *dev = nullptr;
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  int ev_count = 0;
  struct input_event ev {};
  // lambda that's result will change only when capturing an event
  std::thread t {([&]{ while(ev_count == 0) {ev_count += (libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev) != -EAGAIN); }})};
  // write an event
  write_key_event(KEY_A, 1, fd);
  t.join();

  EXPECT_EQ(1, ev_count);
}
}