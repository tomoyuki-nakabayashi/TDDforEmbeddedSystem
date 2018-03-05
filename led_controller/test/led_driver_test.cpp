// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <cstdint>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <os/mock_io.h>
#include <led_driver.h>

// Definition of mock_io is in mock_io.cpp

namespace led_controller_test {
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

class LedDriverTest : public ::testing::Test {
 protected:
    void SetUp() override {
      mock_io = new MOCK_IO {};
      driver_ = CreateLedDriver();
    }

    void TearDown() override {
      DestroyLedDriver(driver_);
      delete mock_io;
    }
 protected:
    LedDriver driver_;
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
TEST_F(LedDriverTest, CanInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(3));
  EXPECT_EQ(LED_DRIVER_SUCCESS, InitLedDriver(driver_, "dummy path"));
}

TEST_F(LedDriverTest, FailToInitInputDevice) {
  EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(-1));
  EXPECT_EQ(LED_DRIVER_INIT_ERROR, InitLedDriver(driver_, "dummy path"));
}

class LedDriverOnOffTest : public ::testing::Test {
 protected:
    void SetUp() override {
      mock_io = new MOCK_IO {};
      driver_ = CreateLedDriver();
      EXPECT_CALL(*mock_io, IO_OPEN(_, _)).WillOnce(Return(kFd));
      InitLedDriver(driver_, "dummy path");
    }

    void TearDown() override {
      DestroyLedDriver(driver_);
      delete mock_io;
    }
 protected:
    LedDriver driver_;
    constexpr static int32_t kFd = 3;
};

TEST_F(LedDriverOnOffTest, TurnOn) {
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("1\n"), 2)).Times(1);
  TurnOnLed(driver_);
}

}  // namespace led_controller_test
