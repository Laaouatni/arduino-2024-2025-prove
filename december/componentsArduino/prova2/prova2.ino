struct Pins {
  const int inputs[1] = {5};
  const int outputs[2] = {5, 2};
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
    while(true) {
      digitalWrite(thisPin, HIGH);
      delay(500);
      digitalWrite(thisPin, LOW);
      delay(500);
    }
  };
}

void loop() {};