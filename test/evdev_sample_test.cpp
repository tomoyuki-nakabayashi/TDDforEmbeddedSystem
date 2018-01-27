// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.
//
// You might exucute these tests as root user.

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <future>
extern "C" {
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
}

bool operator==(const input_event lhs, const input_event rhs) {
  return ((lhs.time.tv_sec == rhs.time.tv_sec)
        && (lhs.time.tv_usec == rhs.time.tv_usec)
        && (lhs.type == rhs.type)
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
      fd_ = open("/dev/input/event2", O_RDWR|O_NONBLOCK);
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

TEST_F(EvdevSampleTest, SuccessCaptureEvent) {
  input_event actual {};
  while (true) {
    int rc = libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &actual);
    if ((rc == LIBEVDEV_READ_STATUS_SUCCESS) && actual.type == EV_KEY) break;
  }
  // write an event
  auto expect = create_key_event(KEY_A, 1);
  write(fd_, &expect, sizeof(expect));
  // lambda that's result will change only when capturing an event
/*   auto result = [&]()->input_event {
    input_event actual {};
    while (libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &actual) != LIBEVDEV_READ_STATUS_SUCCESS) {}
    return actual;
  };
 */
  while (true) {
    int rc = libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &actual);
    if ((rc == LIBEVDEV_READ_STATUS_SUCCESS) && actual.type == EV_KEY) break;
  }
  EXPECT_EQ(expect, actual);
}

TEST_F(EvdevSampleTest, HasEventPending) {
  auto event_pending = std::async(std::launch::async, [this]{ 
    while(libevdev_has_event_pending(evdev_) != 0) {} return true;
  });
  auto event = create_key_event(KEY_A, 0);
  write(fd_, &event, sizeof(event));

  EXPECT_TRUE(event_pending.get());
}
}  // namespace evdev_sample_test