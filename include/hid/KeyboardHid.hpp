#pragma once
#include <array>
#include <hardware/timer.h>
#include <optional>
#include <pico/stdlib.h>
#include <stdint.h>
#include <tusb.h>
#include <vector>
#include <bsp/board.h>

struct KeyPress {
  uint8_t                 keycode;
  std::optional<uint64_t> timeout_time;

  KeyPress(): keycode(0), timeout_time(std::nullopt){};
  KeyPress(uint8_t keycode): keycode(keycode), timeout_time(std::nullopt){};
  KeyPress(uint8_t keycode, uint16_t timeout_ms):
      keycode(keycode), timeout_time(time_us_64() + timeout_ms * 1000){};
};

class KeyboardHid {
public:
  std::vector<KeyPress> keypresses;

private:
  bool _pressButton(KeyPress kp);
  void clearTimeouts();

public:
  bool pressButton(uint8_t keycode);
  bool pressButton(uint8_t keycode, uint32_t time);
  bool releaseButton(uint8_t keycode);

  bool isPressed(uint8_t keycode);
  bool anyKeyPressed();

  std::array<uint8_t, 6> getCurrentKeycodes();
};