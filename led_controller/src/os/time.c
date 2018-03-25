// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <os/time.h>
#include <sys/time.h>
#include <stddef.h>

uint32_t GET_MSEC_OF_DAY() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (uint32_t)((tv.tv_sec*1000) + (tv.tv_usec*0.001));
}
