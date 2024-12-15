struct Pins {
  const int inputs[1] = { 5 };
  const int outputs[17] = { 2,5,18,19,21,22,23,31,12,14,27,26,25,33,32,35,34 };
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
  };
}

void loop() {
  for (auto thisPin : pins.outputs) {
    digitalWrite(thisPin, HIGH);
  };
  delay(1000);
  for (auto thisPin : pins.outputs) {
    digitalWrite(thisPin, LOW);
  };
  delay(1000);
};