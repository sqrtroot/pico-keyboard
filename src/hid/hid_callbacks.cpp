#include "System.hpp"
#include "hid/hid_descriptors.h"
#include "tusb.h"
#include "usb/usb_configuration.h"
#include <algorithm>
#include <charconv>

extern "C" uint8_t const *tud_hid_descriptor_report_cb(uint8_t itf) {
  if(itf == ITF_NUM_HID_IO) {
    return desc_hid_io_report;
  } else if(itf == ITF_NUM_HID_KBM) {
    return desc_hid_kbm_report;
  }

  return NULL;
}

extern "C" uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
  return 0;
}

extern "C" void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  if(itf == ITF_NUM_HID_IO) {
    uint32_t new_blinking_speed;
    auto     convResult = std::from_chars((const char *) buffer, (const char *) buffer + bufsize, new_blinking_speed);
    if(convResult.ec == std::errc() /*no error*/) {
      const auto new_pwm_value = std::min((uint32_t) 100, new_blinking_speed);
      System::getSystem().voltmeter.setLevel(new_pwm_value);
      System::getSystem().blink_interval_ms = new_blinking_speed;
    }
  } else if(itf == ITF_NUM_HID_KBM) {
    if(tud_hid_n_ready(1) && false) {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_key = false;

      static bool toggle = false;
      if(toggle = !toggle) {
        uint8_t keycode[6] = {0};
        keycode[0]         = HID_KEY_A;
        tud_hid_n_keyboard_report(1, 1, 0, keycode);

        has_key = true;
      } else {
        // send empty key report if previously has key pressed
        if(has_key) tud_hid_n_keyboard_report(1, 1, 0, NULL);
        has_key = false;
      }
    }
  }
}