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
/* 
TEST_F(TriggerActionMapTest, AbstractUse) {
  GArray action_trigger_array;

  auto detector = reinterpret_cast<EventDetector>(new EvenDetector{});
  detector->vtable = &even_interface;
  auto op = reinterpret_cast<Operator>(new CountOperator{});
  op->vtable = &count_interface;

  auto count_even_value = CreateTriggerActionPair(detector, op);

  g_array_append_val(action_trigger_array, count_even_value);
  g_array_append_val(action_trigger_array, count_even_value);

  auto cmd = CreateSerializedTriggerActionMap(action_trigger_array);

  auto engine = CreateActiveObjectEngine();
  FuelEngine(engine, cmd);

  while(true) {
    int rc = ExecuteEngine(engine);
    if (rc == FINISH_ENGINE_EXECUTION) break;
  }
}
 */

TEST_F(ActionOnTriggerTest, ActionOnTriggerPieceOfChains) {
  auto detector = reinterpret_cast<EventDetector>(new EvenDetector{});
  detector->vtable = &even_interface;
  auto op = reinterpret_cast<Operator>(new CountOperator{});
  op->vtable = &count_interface;

  auto count_even_value = CreateTriggerActionPair(detector, op);

  auto chained_cmd = CreateActionOnTriggerChain(&count_even_value);
  CommandExecute(chained_cmd);
  CommandExecute(chained_cmd);

  EXPECT_EQ(1, reinterpret_cast<CountOperator*>(op)->my_data);
}

}  // namespace led_controller_test
