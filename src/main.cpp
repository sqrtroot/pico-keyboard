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

  tusb_init();
  auto &system = System::getSystem();
  while(true) {
    tud_task();
    system.systemTask();
  }
  return 0;
}