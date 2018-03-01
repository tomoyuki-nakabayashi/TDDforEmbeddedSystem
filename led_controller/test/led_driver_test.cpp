// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <os/mock_io.h>

// Definition of mock_io is in mock_io.cpp

namespace led_controller_test {
class LedDriverTest : public ::testing::Test {
};

TEST_F(LedDriverTest, FirstTest) {
  EXPECT_TRUE(true);
}

}  // namespace led_controller_test
