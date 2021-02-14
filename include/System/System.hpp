#pragma once
#include "Button.hpp"
#include "VoltMeter.hpp"
#include "bsp/board.h"
#include "hid/KeyboardHid.hpp"
#include <pico/stdlib.h>
class System {
public:
  VoltMeter   voltmeter;
  uint        report_interval_ms = 500;
  KeyboardHid keyboard_hid;
  Button      F14_button;

  static System &getSystem();

  void systemTask();

  System(const System &) = delete;
  void operator=(const System &) = delete;

private:
  System():
      voltmeter(10),
      F14_button(
        16,
        true,
        [&](bool toggled) {
            keyboard_hid.pressButton(HID_KEY_A, 100);
        },
        true){};
};