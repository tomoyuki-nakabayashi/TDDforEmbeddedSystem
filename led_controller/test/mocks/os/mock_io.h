// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LED_CONTROLLER_OS_IO_H_
#define MOCK_LED_CONTROLLER_OS_IO_H_

#include <gmock/gmock.h>
#include <os/io.h>

class MOCK_IO {
 public:
    MOCK_METHOD2(IO_OPEN, int(const char*, int));
};

extern MOCK_IO *mock_io;

extern "C" {
  int IO_OPEN(const char* pathname, int flags)
  {
    return mock_io->IO_OPEN(pathname, flags);
  }
}

#endif  // MOCK_LED_CONTROLLER_OS_IO_H_
