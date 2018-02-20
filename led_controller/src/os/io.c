// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <os/io.h>
#include <fcntl.h>
#include <unistd.h>

int IO_OPEN(const char *pathname, int flags) {
  return open(pathname, flags);
}

int IO_CLOSE(int fd) {
  return close(fd);
}
