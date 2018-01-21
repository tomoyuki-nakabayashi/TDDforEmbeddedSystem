// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <iostream>
extern "C" {
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <unistd.h>
}

namespace evdev_sample_test {
class EvdevSampleTest : public ::testing::Test {
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(EvdevSampleTest, FirstTest) {
  struct input_event event {};

  if (read(0, &event, sizeof(event)) != sizeof(event)) {
    exit(EXIT_FAILURE);
  }
}

}