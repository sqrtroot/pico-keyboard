#pragma once
#include <tusb.h>
static uint8_t const desc_hid_io_report[] = {
  TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_BUFSIZE),    // generic hid for leds/meters
};
static uint8_t const desc_hid_kbm_report[] = {TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(1)), TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(2))};