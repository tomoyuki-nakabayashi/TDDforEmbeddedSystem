// Copyright <2018> Tomoyuki-Nakabayashi
// This software is released under the MIT License, see LICENSE.

#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEY_RELEASED 0
#define KEY_PRESSED 1

static void mainloop() {
struct libevdev *dev = NULL;
  int key_fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  int rc = libevdev_new_from_fd(key_fd, &dev);

  if (rc < 0) {
    fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
    exit(1);
  }

  int led_fd = open("/sys/class/leds/input2::capslock/brightness", O_WRONLY|O_NONBLOCK);
  if (led_fd < 0) {
    fprintf(stderr, "Failed to init LED device.\n");
    exit(1);
  }

  bool led_on = false;
  do {
    struct input_event ev;
    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    if (rc == 0) {
      if (ev.type == EV_KEY && ev.code == KEY_A && ev.value == KEY_PRESSED) {
        led_on = !led_on;
        char buf[2];
        snprintf(buf, 2, "%d", led_on ? 1 : 0);
        write(led_fd, buf, 2);
      }
    }
  } while (rc == 1 || rc == 0 || rc == -EAGAIN);

  libevdev_free(dev);
  close(key_fd);
  close(led_fd);
}

int main() {
  mainloop();
  return 0;
}