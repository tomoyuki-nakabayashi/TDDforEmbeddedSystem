# To Do List

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
- [ ] Finalize input device.
- [ ] Detect 'A' pressed.
- [ ] Are multiple instance required ?
- [ ] evdev operation fails after cleanup().

## LED Brightness

- [ ] Make abstract use.
- [ ] Initialize LED device.
- [ ] Finalize LED device.
- [ ] Turn on if LED is off.
- [ ] Turn off if LED is on.
