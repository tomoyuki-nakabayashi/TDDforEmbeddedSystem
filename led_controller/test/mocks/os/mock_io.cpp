// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <os/mock_io.h>

MOCK_IO *mock_io {};

int IO_OPEN(const char* pathname, int flags) {
  return mock_io->IO_OPEN(pathname, flags);
}

ssize_t IO_WRITE(int fd, const char *buf, size_t count) {
  return mock_io->IO_WRITE(fd, buf, count);
}

int IO_CLOSE(int fd) {
  return mock_io->IO_CLOSE(fd);
}
