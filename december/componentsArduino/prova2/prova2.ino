struct Pins {
  const int inputs[19] = { 18,19,21,22,23,12,27,26,25,33,32,35,34 };
  const int outputs[19] = { 15,2,4,5,18,19,21,22,23,13,12,14,27,26,25,33,32,35,34 };
} pins;

void setup() {
  for (auto thisPin : pins.inputs) {
    pinMode(thisPin, INPUT);
  };
  // for (auto thisPin : pins.outputs) {
  //   pinMode(thisPin, OUTPUT);
  // };
  Serial.begin(115200);
}

void loop() {
  for (auto thisPin : pins.inputs) {
    const int value = analogRead(thisPin);
    if(value != 0) {
      Serial.println("I read from pin input n." + String(thisPin) +
                 "\t this value: " + String(analogRead(thisPin))
                );
    }
  };
};