// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <command/command.h>
#include <stddef.h>

void CommandExecute(Command cmd) {
  if (cmd == NULL) return;
  cmd->vtable->Execute(cmd);
}