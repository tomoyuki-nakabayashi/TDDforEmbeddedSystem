// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gtest/gtest.h>
#include <event_detector.h>
#include <timeout_detector.h>

namespace led_controller_test {
class TimerEventTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

 protected:
    EventDetector detector_;
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

TEST_F(TimerEventTest, CanInitDetector) {
  auto detector = CreateTimeOutDetector(5000, TIMER_ONE_SHOT);
  EXPECT_EQ(EVENT_DETECTOR_SUCCESS, InitEventDetector(detector));
  DestroyTimeOutDetector(detector);
}

}  // namespace led_controller_test