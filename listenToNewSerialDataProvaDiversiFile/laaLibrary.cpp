#include <Arduino.h>

namespace laa {
  String listenToNewSerialData(void (*myCallback)(String)) {
    static String receivedString;

    while (Serial.available() > 0) {
      const char thisChar = Serial.read();
      const bool isLastChar = thisChar == '\n';

      if (!isLastChar) {
        receivedString += thisChar;
        continue;
      };

      myCallback(receivedString);
      receivedString = "";
    };

    return "";
  };
}