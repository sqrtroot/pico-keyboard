#pragma once
#include <tusb.h>

static tusb_desc_device_t const desc_device = {.bLength = sizeof(tusb_desc_device_t),
                                               .bDescriptorType = TUSB_DESC_DEVICE,
                                               .bcdUSB          = 0x0200,
                                               .bDeviceClass    = 0x00,
                                               .bDeviceSubClass = 0x00,
                                               .bDeviceProtocol = 0x00,
                                               .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

                                               .idVendor  = 0xCAFE,
                                               .idProduct = 0xBEEF,
                                               .bcdDevice = 0x0100,

                                               .iManufacturer = 0x01,
                                               .iProduct      = 0x02,
                                               .iSerialNumber = 0x03,

                                               .bNumConfigurations = 0x01};
