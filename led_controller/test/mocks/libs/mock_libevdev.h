// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LIBS_MOCK_LIBEVDEV_H_
#define MOCK_LIBS_MOCK_LIBEVDEV_H_

#include <gmock/gmock.h>
#include <libevdev/libevdev.h>

class MOCK_LIBEVDEV {
 public:
    MOCK_METHOD2(libevdev_new_from_fd, int(int, libevdev**));
    MOCK_METHOD1(libevdev_free, void(libevdev*));
};

extern MOCK_LIBEVDEV *mock_libevdev;

extern "C" {
  int libevdev_new_from_fd(int fd, libevdev **dev) {
    return mock_libevdev->libevdev_new_from_fd(fd, dev);
  }

  void libevdev_free(libevdev *dev) {
    return mock_libevdev->libevdev_free(dev);
  }
}

#endif  // MOCK_LIBS_MOCK_LIBEVDEV_H_