#include "System/System.hpp"

void System::systemTask() {
  F14_button.update();
  keyboard_hid.sendNewReports();
}

System &System::getSystem() {
  static System __system;
  return __system;
}