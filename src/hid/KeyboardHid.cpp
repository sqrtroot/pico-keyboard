#include "hid/KeyboardHid.hpp"
#include "usb/usb_configuration.h"
#include <bsp/board.h>
#include <tusb.h>

bool KeyboardHid::_pressButton(KeyPress kp) {
  if(isPressed(kp.keycode) || keypresses.size() >= keypresses.max_size()) {
    return false;
  }
  printf("Pressing button\n");
  keypresses.push_back(kp);
  newReport = true;
  return true;
}

bool KeyboardHid::pressButton(uint8_t keycode) {
  return _pressButton(KeyPress(keycode));
};

bool KeyboardHid::pressButton(uint8_t keycode, uint32_t time) {
  return _pressButton(KeyPress(keycode, time));
};

bool KeyboardHid::isPressed(uint8_t keycode) {
  return std::any_of(keypresses.begin(), keypresses.end(), [&](const KeyPress &t) {
    return t.keycode == keycode;
  });
}

bool KeyboardHid::releaseButton(uint8_t keycode) {
  const auto it = std::find_if(keypresses.begin(), keypresses.end(), [&](const KeyPress &kp) {
    return kp.keycode == keycode;
  });
  if(it == keypresses.end()) {
    return false;
  }
  printf("Releasing button\n");
  keypresses.erase(it);
  newReport = true;
  return true;
}

std::array<uint8_t, 6> KeyboardHid::getCurrentKeycodes() {
  std::array<uint8_t, 6> keycodes{
    0,
  };
  if(keypresses.size() > 6) {
    keypresses.resize(6);
  }
  std::transform(keypresses.begin(), keypresses.end(), keycodes.begin(), [](const KeyPress &kp) {
    return kp.keycode;
  });
  return keycodes;
}

void KeyboardHid::clearTimeouts() {
  const auto it = std::remove_if(keypresses.begin(), keypresses.end(), [](const KeyPress &kp) {
    return kp.timeout_time.has_value() && time_us_64() > *kp.timeout_time;
  });
  if(it != keypresses.end()) {
    keypresses.erase(it, keypresses.end());
    newReport = true;
  }
}

bool KeyboardHid::anyKeyPressed() {
  return keypresses.size() > 0;
}

void KeyboardHid::sendNewReports() {
  if(tud_hid_n_ready(ITF_NUM_HID_KBM)) {
    clearTimeouts();
    if(newReport) {
      if(anyKeyPressed()) {
        tud_hid_n_keyboard_report(ITF_NUM_HID_KBM, 1, 0, getCurrentKeycodes().data());
      } else {
        tud_hid_n_keyboard_report(1, 1, 0, NULL);
      }
      newReport = false;
    }
  }
}
