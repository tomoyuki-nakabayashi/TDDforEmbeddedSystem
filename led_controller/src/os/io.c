// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <os/io.h>
#include <fcntl.h>
#include <unistd.h>

int IO_OPEN(const char *pathname, int flags) {
  return open(pathname, flags);
}

ssize_t IO_WRITE(int fd, const char *buf, size_t count) {
  return write(fd, buf, count);
}

int IO_CLOSE(int fd) {
  return close(fd);
}
