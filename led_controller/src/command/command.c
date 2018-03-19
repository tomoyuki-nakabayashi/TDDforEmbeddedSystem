// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/command.h>

void CommandExecute(Command cmd) {
  cmd->vtable->Execute(cmd);
}