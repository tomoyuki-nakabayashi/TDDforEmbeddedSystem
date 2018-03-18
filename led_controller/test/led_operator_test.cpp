// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gmock/gmock.h>
#include <operator/operator.h>

// Definition of mock_io is in mock_io.cpp

namespace led_controller_test {

class LedOperatorTest : public ::testing::Test {
};

TEST_F(LedOperatorTest, FirstTest) {
  EXPECT_TRUE(true);
}

}  //  namespace led_controller_test
