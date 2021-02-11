#include "hid/KeyboardHid.hpp"
#include <bsp/board.h>

bool KeyboardHid::_pressButton(KeyPress kp) {
  if(isPressed(kp.keycode) || keypresses.size() >= keypresses.max_size()) {
    return false;
  }
  keypresses.push_back(kp);
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
  keypresses.erase(it);
  return true;
}

std::array<uint8_t, 6> KeyboardHid::getCurrentKeycodes() {
  std::array<uint8_t, 6> keycodes{
    0,
  };
  keypresses.resize(6);
  std::transform(keypresses.begin(), keypresses.end(), keycodes.begin(), [](const KeyPress &kp) {
    return kp.keycode;
  });
  
  return keycodes;
}

void KeyboardHid::clearTimeouts() {
  std::remove_if(keypresses.begin(), keypresses.end(), [](const KeyPress &kp) {
    return kp.timeout_time.has_value() && time_us_64() > *kp.timeout_time;
  });
}

bool KeyboardHid::anyKeyPressed() {
  return keypresses.size() > 0;
}