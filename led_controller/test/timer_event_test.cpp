// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gmock/gmock.h>
#include <event_detector.h>
#include <timeout_detector.h>
#include <os/mock_time.h>

MOCK_TIME *mock_time {};

namespace led_controller_test {
using ::testing::Return;
class CreateTimerEventTest : public ::testing::Test {
 protected:
    void SetUp() override {
      mock_time = new MOCK_TIME{};
    }

    void TearDown() override {
      delete mock_time;
    }
};
/* 
TEST_F(TimerEventTest, AbstractUse) {
  auto detector = CreateTimerDetector(condition);
  EXPECT_NE(nullptr, detector);
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, InitDetector(detector));

  for (int i = 0; i < 10; i++)
    EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(detector));
  EXPECT_EQ(EVENT_DETECTED, CheckEvent(detector));

  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, CleaupDetector(detector));
}
*/

TEST_F(CreateTimerEventTest, CanInitDetector) {
  auto detector = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, StartEventDetector(detector));
  DestroyTimeOutDetector(detector);
}

TEST_F(CreateTimerEventTest, FailToInitDetectorWithInvalidFlag) {
  auto detector = CreateTimeOutDetector(5000, -1);
  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(detector));
  DestroyTimeOutDetector(detector);
}

class TimerEventTest : public ::testing::Test {
 protected:
    void SetUp() override {
      detector_ = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
      mock_time = new MOCK_TIME{};
    }

    void TearDown() override {
      delete mock_time;
    }

 protected:
    EventDetector detector_;
};

TEST_F(TimerEventTest, DetectTimeOut) {
  EXPECT_CALL(*mock_time, GET_MSEC_OF_DAY())
    .WillOnce(Return(0))
    .WillOnce(Return(4999))
    .WillOnce(Return(5000));

  StartEventDetector(detector_);
  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(detector_));
  EXPECT_EQ(EVENT_DETECTED, CheckEvent(detector_));
}

TEST_F(TimerEventTest, DetectOnlyOnce) {
  EXPECT_CALL(*mock_time, GET_MSEC_OF_DAY())
    .WillOnce(Return(0))
    .WillOnce(Return(5001));

  StartEventDetector(detector_);
  EXPECT_EQ(EVENT_DETECTED, CheckEvent(detector_));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CheckEvent(detector_));
}

TEST_F(TimerEventTest, DetectWrappedTime) {
  EXPECT_CALL(*mock_time, GET_MSEC_OF_DAY())
    .WillOnce(Return(UINT32_MAX))
    .WillOnce(Return(4998))
    .WillOnce(Return(4999));

  StartEventDetector(detector_);
  EXPECT_EQ(EVENT_NOT_DETECTED, CheckEvent(detector_));
  EXPECT_EQ(EVENT_DETECTED, CheckEvent(detector_));
}

TEST_F(TimerEventTest, CleanupTimeOutDetector) {
  StartEventDetector(detector_);
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, CleanupEventDetector(detector_));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CheckEvent(detector_));
}

TEST_F(TimerEventTest, NullPointerGuard) {
  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(nullptr));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CheckEvent(nullptr));
  EXPECT_EQ(EVENT_DETECTOR_ERROR, CleanupEventDetector(nullptr));
}

}  // namespace led_controller_test