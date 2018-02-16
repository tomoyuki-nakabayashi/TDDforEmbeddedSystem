// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <utils/logger_spy.h>
#include <string.h>

static char *buffer = NULL;
static int buffer_size = 0;

void DEBUG_LOG(const char *message) {
  strncpy(buffer, message, buffer_size-1);
}

void set_DEBUG_LOG_spy(char *b, const int size) {
  buffer = b;
  buffer_size = size;
}
