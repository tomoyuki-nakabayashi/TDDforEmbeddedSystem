// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef MOCK_UTILS_LOGGER_SPY_H_
#define MOCK_UTILS_LOGGER_SPY_H_

#include <utils/logger.h>

#ifdef __cplusplus
extern "C" {
#endif

void DEBUG_LOG(const char *message);
void set_DEBUG_LOG_spy(char* b, const int size);

#ifdef __cplusplus
}
#endif

#endif  // MOCK_UTILS_LOGGER_SPY_H_
