// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gmock/gmock.h>
#include <operator/operator.h>
#include <operator/led_operator_factory.h>
#include <drivers/led_driver.h>
#include <os/mock_io.h>

// Definition of mock_io is in mock_io.cpp

namespace led_controller_test {
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::InSequence;

class LedOperatorTest : public ::testing::Test {
 protected:
    void SetUp() override {
      mock_io = new MOCK_IO();
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

TEST_F(LedOperatorTest, LedTrunOnOperationCallsIoWriteWithOne) {
  Operator op = LedOperatorFactory(driver_, OP_LED_TURN_ON);
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("1\n"), 2)).Times(1);
  TriggerOperation(op);
}

TEST_F(LedOperatorTest, FatoryReturnsNullIfFailed) {
  Operator op = LedOperatorFactory(nullptr, OP_LED_TURN_ON);
  EXPECT_EQ(nullptr, op);

  op = LedOperatorFactory(driver_, -1);
  EXPECT_EQ(nullptr, op);

  op = LedOperatorFactory(driver_, OP_MAX_FACTORY_ID);
  EXPECT_EQ(nullptr, op);
}

TEST_F(LedOperatorTest, LedTrunOffOperationCallsIoWriteWithZero) {
  Operator op = LedOperatorFactory(driver_, OP_LED_TURN_OFF);
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("0\n"), 2)).Times(1);
  TriggerOperation(op);
}

TEST_F(LedOperatorTest, LedToggleOperationTogglesIoWrite) {
  Operator op = LedOperatorFactory(driver_, OP_LED_TOGGLE);

  InSequence s;
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("1\n"), 2)).Times(1);
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("0\n"), 2)).Times(1);
  EXPECT_CALL(*mock_io, IO_WRITE(kFd, StrEq("1\n"), 2)).Times(1);

  TriggerOperation(op);
  TriggerOperation(op);
  TriggerOperation(op);
}

}  //  namespace led_controller_test
