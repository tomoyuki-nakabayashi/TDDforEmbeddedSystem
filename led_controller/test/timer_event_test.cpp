// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <event_detector.h>
#include <timeout_detector.h>

namespace led_controller_test {
using ::testing::Return;
class CreateTimerEventTest : public ::testing::Test {
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
  auto detector = CreateTimeOutDetector(5, TIMER_ONE_SHOT);
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, StartEventDetector(detector));
  DestroyTimeOutDetector(detector);
}

TEST_F(CreateTimerEventTest, FailToInitDetectorWithInvalidFlag) {
  auto detector = CreateTimeOutDetector(5, -1);
  EXPECT_EQ(EVENT_DETECTOR_ERROR, StartEventDetector(detector));
  DestroyTimeOutDetector(detector);
}

class TimerEventTest : public ::testing::Test {
 protected:
    void SetUp() override {
      detector_ = CreateTimeOutDetector(5, TIMER_ONE_SHOT);
    }

    void TearDown() override {
    }

 protected:
    EventDetector detector_;
};

}  // namespace led_controller_test