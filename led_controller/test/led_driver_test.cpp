// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <os/mock_io.h>
#include <led_driver.h>

// Definition of mock_io is in mock_io.cpp

namespace led_controller_test {
class LedDriverTest : public ::testing::Test {
 protected:
    void SetUp() override {
      mock_io = new MOCK_IO {};
    }

    void TearDown() override {
      delete mock_io;
    }
};
/* 
TEST_F(LedDriverTest, AbstractUse) {
  auto dev = CreateLedDriver();
  InitLedDriver(dev);
  TurnOn(dev);
  TurnOff(dev);
  Toggle(dev);
  DestroyLedDriver(dev);
}
*/
TEST_F(LedDriverTest, FirstTest) {
  EXPECT_TRUE(true);
}

}  // namespace led_controller_test
