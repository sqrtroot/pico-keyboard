#pragma once
#include <stdint.h>
#include <tusb.h>

extern "C" {
void            tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);
uint16_t        tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen);
uint8_t const * tud_hid_descriptor_report_cb(uint8_t itf);
extern "C" bool tud_hid_set_idle_cb(uint8_t itf, uint8_t idle_rate);
}

void hid_kbm_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);
void hid_io_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);