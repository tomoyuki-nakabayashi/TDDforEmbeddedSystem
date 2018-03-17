# To Do List

## Environment

- [ ] Link glib to use variable length array.

## LED Controller

- [x] Consider top-level absctract use.

## Key input event

- [x] Make abstract use.
- [x] Initialize input device.
  - [x] Open input device file.
  - [x] Initialize returns true.
  - [x] Initialize returns false.
  - [x] Output permisiion denied.
  - [x] Initialize libevdev.
  - [x] Add failure case of initializing libevdev.
- [x] Finalize input device.
- [x] Detect 'A' pressed.
- [x] Multi-instantiation required.
- [x] Move specific struct definition into private header.
- [x] Check null pointer check.
- [x] evdev operation fails after cleanup().
- [x] Extract Detect interface.
- [ ] input event factory.

## LED Brightness

- [x] Make abstract use.
- [x] Initialize LED device.
- [x] Finalize LED device.
- [x] Turn on if LED is off.
- [x] Turn off if LED is on.
- [x] Toggle LED.
- [ ] Extract Operate interface.

## Timer event

- [x] Create timer.
- [x] Start timer.
- [x] Detect timeout.
- [ ] Detect wrapped timeout.
- [ ] Oneshot.
- [ ] Repeatedly.

## Engine control command

- [ ] Implement flush by overriding Operate interface.
