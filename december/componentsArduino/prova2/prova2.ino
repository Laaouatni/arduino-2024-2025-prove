const int inputs[19] = { 15, 2, 4, 5, 18, 19, 21, 22, 23, 13, 12, 14, 27, 26, 25, 33, 32, 35, 34 };
const int myPinInput = inputs[0];

void setup() {
  pinMode(myPinInput, INPUT);
  Serial.begin(115200);
  Serial.print("pinMode: " + String(myPinInput) + " INPUT");
}

void loop() {
  const int value = analogRead(thisPin);
  if (value != 0) {
    Serial.println("I read from pin input n." + String(thisPin) + "\t this value: " + String(analogRead(thisPin)));
  };
};