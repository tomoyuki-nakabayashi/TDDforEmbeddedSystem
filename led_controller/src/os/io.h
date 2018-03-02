// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_OS_IO_H_
#define LED_CONTROLLER_OS_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>

int IO_OPEN(const char *pathname, int flags);
ssize_t IO_WRITE(int fd, const void *buf, size_t count);
int IO_CLOSE(int fd);

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_OS_IO_H_
