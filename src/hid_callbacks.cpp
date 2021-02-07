#include "System.hpp"
#include "tusb.h"
#include <algorithm>
#include <charconv>

extern "C" uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
  return 0;
}

extern "C" void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  uint32_t new_blinking_speed;
  auto     convResult = std::from_chars((const char *) buffer, (const char *) buffer + bufsize, new_blinking_speed);
  if(convResult.ec == std::errc() /*no error*/) {
    const auto new_pwm_value = std::min((uint32_t) 100, new_blinking_speed);
    System::getSystem().voltmeter.setLevel(new_pwm_value);
    System::getSystem().blink_interval_ms = new_blinking_speed;
  }
}