// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <gmock/gmock.h>
#include <command/action_on_trigger.h>
#include <detector/event_detector.h>
#include <detector/timeout_detector.h>
#include <operator/operator.h>

namespace led_controller_test {

class ActionOnTriggerTest : public ::testing::Test {
 protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

 protected:
};

typedef struct EvenDetector {
  EventDetectorStruct base;
  uint32_t my_data;
} EvenDetector;

static int ClearEvenCounter(EventDetector super) {
  auto self = reinterpret_cast<EvenDetector*>(super);
  self->my_data = 0;
  return DETECTOR_SUCCESS;
}

static int CheckEvenCounter(EventDetector super) {
  auto self = reinterpret_cast<EvenDetector*>(super);
  self->my_data++;
  return ((self->my_data % 2) == 0) ?
    DETECTOR_EVENT_DETECTED : DETECTOR_EVENT_NOT_DETECTED;
}

static EventDetectorInterfaceStruct even_interface = {
  ClearEvenCounter, CheckEvenCounter, ClearEvenCounter,
};

typedef struct CountOperator {
  OperatorStruct base;
  int32_t my_data;
} CountOperator;

static void IncrementCounter(Operator super) {
  auto self = reinterpret_cast<CountOperator*>(super);
  self->my_data++;
}

static OperatorInterfaceStruct count_interface = {
  IncrementCounter
};

TEST_F(ActionOnTriggerTest, AbstractUse) {
  EventDetector detector = reinterpret_cast<EventDetector>(new EvenDetector{});
  detector->vtable = &even_interface;
  Operator op = reinterpret_cast<Operator>(new CountOperator{});
  op->vtable = &count_interface;
  Command ood = static_cast<Command>(CreateActionOnTrigger(detector, op));

  CommandExecute(ood);
  EXPECT_EQ(0, reinterpret_cast<CountOperator*>(op)->my_data);

  CommandExecute(ood);
  EXPECT_EQ(1, reinterpret_cast<CountOperator*>(op)->my_data);
}

}  // namespace led_controller_test
