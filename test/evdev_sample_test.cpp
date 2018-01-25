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
  struct input_event ev {};
  int actual = libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  EXPECT_EQ(-EAGAIN, actual);
}

static void write_key_event(int code, int value, int fd)
{
  struct input_event key_event {};
  
  gettimeofday(&key_event.time, NULL);
  key_event.type = EV_KEY;
  key_event.code = code;
  key_event.value = value;
  write(fd, &key_event, sizeof(key_event));
}

TEST_F(EvdevSampleTest, SuccessCaptureEvent) {
  int ev_count = 0;
  struct input_event ev {};
  // lambda that's result will change only when capturing an event
  std::thread t {([&]{ while(ev_count == 0) {ev_count += (libevdev_next_event(evdev_, LIBEVDEV_READ_FLAG_NORMAL, &ev) != -EAGAIN); }})};

  // write an event
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  write_key_event(KEY_A, 1, fd_);
  write_key_event(KEY_A, 0, fd_);
  t.join();

  EXPECT_EQ(1, ev_count);
}

TEST_F(EvdevSampleTest, HasEventPending) {
  auto event_pending = std::async(std::launch::async, [this]{ while(libevdev_has_event_pending(evdev_) != 0) {} return 1;});

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  write_key_event(KEY_A, 1, fd_);
  write_key_event(KEY_A, 0, fd_);

  EXPECT_EQ(1, event_pending.get());
}
}  // namespace evdev_sample_test