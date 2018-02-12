// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.
//
// You might exucute these tests as root user.

#include <gtest/gtest.h>
extern "C" {
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
}

bool operator==(const input_event lhs, const input_event rhs) {
  return ((lhs.type == rhs.type)
        && (lhs.code == rhs.code)
        && (lhs.value == rhs.value));
}

namespace evdev_sample_test {
class EvdevSampleOpenTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(EvdevSampleOpenTest, InputEventFileCanOpenAsRoot) {
  struct libevdev *dev {nullptr};
  int fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(fd, &dev);

  EXPECT_GE(rc, 0);
}

class EvdevSampleTest : public ::testing::Test {
 public:
    EvdevSampleTest(): evdev_{nullptr}, fd_{} {}

 protected:
    virtual void SetUp()
    {
      fd_ = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
      int rc = libevdev_new_from_fd(fd_, &evdev_);
      input_event ev {};
    }

    virtual void TearDown()
    {
      // Flush all input events.
      input_event ev {};
      while(libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &ev) != -EAGAIN) {}
      while(libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_SYNC, &ev) != -EAGAIN) {}
      close(fd_);
    }
 protected:
    libevdev *evdev_;
    int fd_;
};

constexpr int KEY_RELEASED = 0;
constexpr int KEY_PRESSED = 1;

TEST_F(EvdevSampleTest, ReturnsEAGAIN) {
  input_event ev {};
  int actual = libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  EXPECT_EQ(-EAGAIN, actual);
}

static input_event create_key_event(uint16_t code, int value)
{
  timeval time {};
  gettimeofday(&time, NULL);
  return input_event {time, EV_KEY, code, value};
}

TEST_F(EvdevSampleTest, CaptureEnterKeyPress) {
  auto expect = create_key_event(KEY_ENTER, KEY_PRESSED);
  input_event actual {};
  while (true) {
    int rc = libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &actual);
    if ((rc == LIBEVDEV_READ_STATUS_SUCCESS) && actual == expect) break;
  }

  EXPECT_EQ(expect, actual);
}
}  // namespace evdev_sample_test