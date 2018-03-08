// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#ifndef LED_CONTROLLER_COMMAND_COMMAND_H_
#define LED_CONTROLLER_COMMAND_COMMAND_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CommandInterfaceStruct *CommandInterface;
typedef struct CommandStruct *Command;

typedef struct CommandStruct {
  CommandInterface vtable;
} CommandStruct;

typedef struct CommandInterfaceStruct {
  void (*Execute)(Command);
} CommandInterfaceStruct;

void CommandExecute(Command cmd) {
  cmd->vtable->Execute(cmd);
}

#ifdef __cplusplus
}
#endif

#endif  // LED_CONTROLLER_COMMAND_COMMAND_H_
