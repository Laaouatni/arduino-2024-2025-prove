struct Pins {
  int inputs[] = {5};
  int outputs[] = {5};
} pins;

void setup() {
  // for (auto thisPin : pins.inputs) {
  //   pinMode(thisPin, INPUT);
  //   Serial.print("I read from pin input n." + String(thisPin) +
  //                "\t this value: " + String(analogRead(thisPin))
  //               );
  // };
  for (auto thisPin : pins.outputs) {
    pinMode(thisPin, OUTPUT);
    digitalWrite(thisPin, HIGH);
  };
}

void loop() {};