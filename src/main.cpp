#include "System/System.hpp"
#include <bsp/board.h>
#include <hardware/gpio.h>
#include <optional>
#include <pico/multicore.h>
#include <pico/stdlib.h>
#include <stdint.h>

int main() {
  board_init();
  stdio_init_all();
  printf("Hello, world!\n");
  gpio_init(16);
  gpio_set_function(16, GPIO_FUNC_SIO);
  gpio_set_dir(16, GPIO_IN);
  gpio_pull_up(16);

  tusb_init();
  bool  pressed = false;
  auto &system  = System::getSystem();
  // board_led_off();
  while(true) {
    tud_task();
    system.systemTask();
    if(!pressed) {
      if(!gpio_get(16)) {
        system.keyboard_hid.pressButton(HID_KEY_A);
        pressed                  = true;
      }
    } else {
      if(gpio_get(16)) {
        system.keyboard_hid.releaseButton(HID_KEY_A);
        pressed                  = false;
      }
    }
  }
  return 0;
}