// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LIBS_MOCK_LIBEVDEV_H_
#define MOCK_LIBS_MOCK_LIBEVDEV_H_

#include <gmock/gmock.h>
#include <linux/input.h>
#include <libevdev/libevdev.h>

class MOCK_LIBEVDEV {
 public:
    MOCK_METHOD2(libevdev_new_from_fd, int(int, libevdev**));
    MOCK_METHOD1(libevdev_free, void(libevdev*));
    MOCK_METHOD3(libevdev_next_event,
                 int(libevdev*, unsinged int, input_event*));
};

extern MOCK_LIBEVDEV *mock_libevdev;

extern "C" {
  int libevdev_new_from_fd(int fd, libevdev **dev) {
    return mock_libevdev->libevdev_new_from_fd(fd, dev);
  }

  void libevdev_free(libevdev *dev) {
    return mock_libevdev->libevdev_free(dev);
  }

  int libevdev_next_event(libevdev* dev, unsinged int flags, input_event* ev) {
    return mock_libevdev->libevdev_next_event(dev, flags, ev);
  }
}

#endif  // MOCK_LIBS_MOCK_LIBEVDEV_H_