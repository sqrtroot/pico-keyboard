#include "hid/hid_callbacks.hpp"
#include "System/System.hpp"
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
  switch(itf) {
    case ITF_NUM_HID_KBM:
      hid_kbm_callback(report_id, report_type, buffer, bufsize);
      break;
    case ITF_NUM_HID_IO:
      hid_io_callback(report_id, report_type, buffer, bufsize);
      break;
    default:
      __unreachable();
  };
}

void hid_kbm_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  if(tud_hid_n_ready(ITF_NUM_HID_KBM)) {
    // use to avoid send multiple consecutive zero report for keyboard
    static bool has_key  = false;
    auto &      keyboard = System::getSystem().keyboard_hid;
    if(keyboard.anyKeyPressed()) {
      auto keypresses = keyboard.getCurrentKeycodes();
      tud_hid_n_keyboard_report(ITF_NUM_HID_KBM, 1, 0, keypresses.data());
      has_key = true;
    } else {
      if(has_key) {
        tud_hid_n_keyboard_report(1, 1, 0, NULL);
        has_key = false;
      }
    }
  }
}

void hid_io_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  uint32_t new_blinking_speed;
  auto     convResult = std::from_chars((const char *) buffer, (const char *) buffer + bufsize, new_blinking_speed);
  if(convResult.ec == std::errc() /*no error*/) {
    const auto new_pwm_value = std::min((uint32_t) 100, new_blinking_speed);
    System::getSystem().voltmeter.setLevel(new_pwm_value);
    System::getSystem().blink_interval_ms = new_blinking_speed;
  }
}