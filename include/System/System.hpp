#pragma once
#include "VoltMeter.hpp"
#include "bsp/board.h"
#include "hid/KeyboardHid.hpp"
#include <pico/stdlib.h>
class System {
public:
  VoltMeter   voltmeter;
  uint        blink_interval_ms = 100;
  KeyboardHid keyboard_hid;

  static System &getSystem() {
    static System system;
    return system;
  }

  void systemTask();

  System(const System &) = delete;
  void operator=(const System &) = delete;

private:
  System(): voltmeter(0){};
};