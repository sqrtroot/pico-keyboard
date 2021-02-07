#pragma once
#include <pico/stdlib.h>
#include <stdint.h>

struct VoltMeter {
  const uint pinNumber;
  const uint slice;
  const uint channel;
  VoltMeter(uint pinNumber);
  void setLevel(uint8_t lvl);
  ~VoltMeter();
  VoltMeter(const VoltMeter &) = delete;
  VoltMeter operator=(const VoltMeter &) = delete;
};