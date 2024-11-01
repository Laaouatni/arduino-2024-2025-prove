#include "laaLibrary.h"

void example(String myString) {
  Serial.println("ciao " + myString);
};

void setup() {
  Serial.begin(115200);
};

void loop() {
  laa::listenToNewSerialData(&example);
};