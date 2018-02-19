// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LED_CONTROLLER_OS_IO_H_
#define MOCK_LED_CONTROLLER_OS_IO_H_

#include <gmock/gmock.h>
#include <os/io.h>

class MOCK_IO {
 public:
    MOCK_METHOD2(IO_OPEN, int(const char*, int));
    MOCK_METHOD1(IO_CLOSE, int(int));
};

extern MOCK_IO *mock_io;

extern "C" {
  int IO_OPEN(const char* pathname, int flags) {
    return mock_io->IO_OPEN(pathname, flags);
  }

  int IO_CLOSE(int fd) {
    return mock_io->IO_CLOSE(fd);
  }
}

#endif  // MOCK_LED_CONTROLLER_OS_IO_H_
