#pragma once
#include "VoltMeter.hpp"
#include "bsp/board.h"
#include <pico/stdlib.h>
class System {
public:
  VoltMeter voltmeter;
  uint      blink_interval_ms = 100;

  static System &getSystem() {
    static System system;
    return system;
  }

  void systemTask();

private:
  System(): voltmeter(0){};
};