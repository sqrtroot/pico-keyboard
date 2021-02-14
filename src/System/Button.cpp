#include "System/Button.hpp"
#include <cstdio>

Button::Button(uint8_t pin, bool pullUp):
    Button(pin, pullUp, std::function<void(bool)>(), false){};

Button::Button(uint8_t pin, bool pullUp, std::function<void(bool)> onToggleCallback):
    Button(pin, pullUp, onToggleCallback, false){};

Button::Button(uint8_t pin, bool pullUp, std::function<void(bool)> onToggleCallback, bool inverse):
    pin(pin), pullUp(pullUp), onChange(onToggleCallback), inverse(inverse) {
  gpio_init(pin);
  gpio_set_function(pin, GPIO_FUNC_SIO);
  gpio_set_dir(pin, GPIO_IN);
  if(pullUp) {
    gpio_pull_up(pin);
  }
  previousState = gpio_get(pin);
};

Button::Button(uint8_t pin, bool pullUp, bool inverse):
    Button(pin, pullUp, std::function<void(bool)>(), inverse){};

void Button::update() {
  const bool newValue = gpio_get(pin);
  if(newValue != previousState) {
    previousState = newValue;
    if(onChange) {
      onChange(newValue);
    }
  }
}