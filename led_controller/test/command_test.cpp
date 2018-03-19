// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <cstdint>
#include <gtest/gtest.h>
#include <command/command.h>

namespace command_test {
/* 
typedef struct CounterCommand {
  CommandStruct command;
  int32_t my_data;
} CounterCommand;

class CommandTest : public ::testing::Test {
};

static void IncrementCounter(Command super) {
  auto self = reinterpret_cast<CounterCommand*>(super);
  self->my_data++;
}

static CommandInterfaceStruct interface = {
  .Execute = IncrementCounter
};

TEST_F(CommandTest, CounterCommandTest) {
  CounterCommand cmd{};
  cmd.command.vtable = &interface;

  CommandExecute(reinterpret_cast<Command>(&cmd));
  EXPECT_EQ(1, cmd.my_data);
}
 */
}  // namespace command_test
