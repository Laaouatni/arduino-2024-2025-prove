#include <Arduino.h>

namespace laa {
  String listenToNewSerialData(void (*myCallback)(String));
};