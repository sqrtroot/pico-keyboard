#include "bsp/board.h"
#include "pico/stdlib.h"
#include <optional>
#include <stdint.h>
#include "System.hpp"

int main() {
  board_init();
  tusb_init();
  while(true) {
    tud_task();
    System::getSystem().systemTask();
  }
  return 0;
}