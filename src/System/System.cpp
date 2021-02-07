#include "System/System.hpp"

void System::systemTask() {
  static uint32_t start_ms  = 0;
  static bool     led_state = false;

  // Blink every interval ms
  if(board_millis() - start_ms < blink_interval_ms) return;    // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state;    // toggle
}