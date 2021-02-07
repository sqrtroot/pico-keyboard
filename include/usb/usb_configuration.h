#pragma once
#include <tusb.h>
#include "hid/hid_descriptors.h"

enum { ITF_NUM_HID_IO, ITF_NUM_HID_KBM, ITF_NUM_TOTAL };

#define CONFIG_TOTAL_LEN \
  (TUD_CONFIG_DESC_LEN + TUD_HID_INOUT_DESC_LEN + TUD_HID_DESC_LEN)

#define EPNUM_HID_IO_I 0x1
#define EPNUM_HID_IO_O 0x81
#define EPNUM_HID_KBM  0x82

static uint8_t const desc_configuration[] = {
  // Config number, interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

  // Interface number, string index, protocol, report descriptor len, EP In & Out address, size & polling interval
  TUD_HID_INOUT_DESCRIPTOR(ITF_NUM_HID_IO, 0, HID_PROTOCOL_NONE, sizeof(desc_hid_io_report), EPNUM_HID_IO_I, EPNUM_HID_IO_O, CFG_TUD_HID_BUFSIZE, 10),
  TUD_HID_DESCRIPTOR(ITF_NUM_HID_KBM, 0, HID_PROTOCOL_NONE, sizeof(desc_hid_kbm_report), EPNUM_HID_KBM, CFG_TUD_HID_EP_BUFSIZE, 10)};

static char const *string_desc_arr[] = {
  (const char[]){0x09, 0x04},    // 0: is supported language is English (0x0409)
  "sqrtroot",                    // 1: Manufacturer
  "SUPERKEYBOARD Device",        // 2: Product
  "1337",                        // 3: Serials, should use chip ID
};