#include "System/VoltMeter.hpp"
#include "hardware/pwm.h"

VoltMeter::VoltMeter(uint pinNumber):
    pinNumber(pinNumber), slice(pwm_gpio_to_slice_num(pinNumber)), channel(pwm_gpio_to_channel(pinNumber)) {
  gpio_set_function(pinNumber, GPIO_FUNC_PWM);
  pwm_set_wrap(slice, 100);    // reset counter when we reach 100 so percentages are easy
  pwm_set_enabled(slice, true);    // enable pwm on slice
}

void VoltMeter::setLevel(uint8_t lvl) {
  pwm_set_chan_level(slice, channel, lvl);
}
VoltMeter::~VoltMeter() {
  pwm_set_enabled(slice, false);
}