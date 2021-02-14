#pragma once
#include "VoltMeter.hpp"
#include "bsp/board.h"
#include "hid/KeyboardHid.hpp"
#include <pico/stdlib.h>
class System {
public:
  VoltMeter   voltmeter;
  uint        report_interval_ms = 500;
  KeyboardHid keyboard_hid;

  static System &getSystem();

  void systemTask();

  System(const System &) = delete;
  void operator=(const System &) = delete;

private:
  System(): voltmeter(10){};
};