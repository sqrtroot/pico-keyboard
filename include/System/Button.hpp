#pragma once
#include <functional>
#include <pico/stdlib.h>
#include <stdint.h>

class Button {
  uint8_t pin;
  uint8_t pullUp;

  bool previousState;
  bool inverse = false;

  std::function<void(bool)> onChange;

public:
  Button(uint8_t pin, bool pullUp);
  Button(uint8_t pin, bool pullUp, std::function<void(bool)> onToggleCallback);
  Button(uint8_t pin, bool pullUp, std::function<void(bool)> onToggleCallback, bool inverse);
  Button(uint8_t pin, bool pullUp, bool inverse);
  void update();
};