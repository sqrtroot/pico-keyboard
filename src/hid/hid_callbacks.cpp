#include "hid/hid_callbacks.hpp"
#include "System/System.hpp"
#include "hid/hid_descriptors.h"
#include "tusb.h"
#include "usb/usb_configuration.h"
#include <algorithm>
#include <charconv>

extern "C" uint8_t const *tud_hid_descriptor_report_cb(uint8_t itf) {
  printf("tud_hid_descriptor_report_cb\n");
  if(itf == ITF_NUM_HID_IO) {
    return desc_hid_io_report;
  } else if(itf == ITF_NUM_HID_KBM) {
    return desc_hid_kbm_report;
  }
  return NULL;
}

extern "C" bool tud_hid_set_idle_cb(uint8_t itf, uint8_t idle_rate) {
  printf("Idle rate for interface %d is %d", itf, idle_rate);
  return true;
};

extern "C" uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
  printf("tud_hid_get_report_cb\n");
  return 0;
}

extern "C" void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  printf("tud_hid_set_report_cb\n");
  for(int i = 0; i < bufsize; i++) {
    printf("%02X", buffer[i]);
  }
  printf("\n");
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
  printf("hid_kbm_callback\n");
}

void hid_io_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  printf("hid_io_callback\n");
  uint32_t new_blinking_speed;
  auto     convResult = std::from_chars((const char *) buffer, (const char *) buffer + bufsize, new_blinking_speed);
  if(convResult.ec == std::errc() /*no error*/) {
    const auto new_pwm_value = std::min((uint32_t) 100, new_blinking_speed);
    System::getSystem().voltmeter.setLevel(new_pwm_value);
  }
}
