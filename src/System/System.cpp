#include "System/System.hpp"

void System::systemTask() {
  keyboard_hid.sendNewReports();
}

System &System::getSystem() {
  static System __system;
  return __system;
}