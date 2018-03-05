// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_LED_CONTROLLER_OS_IO_H_
#define MOCK_LED_CONTROLLER_OS_IO_H_

#include <gmock/gmock.h>
#include <os/io.h>

class MOCK_IO {
 public:
    MOCK_METHOD2(IO_OPEN, int(const char*, int));
    MOCK_METHOD3(IO_WRITE, ssize_t(int, const char*, size_t));
    MOCK_METHOD1(IO_CLOSE, int(int));
};

extern MOCK_IO *mock_io;

#endif  // MOCK_LED_CONTROLLER_OS_IO_H_
