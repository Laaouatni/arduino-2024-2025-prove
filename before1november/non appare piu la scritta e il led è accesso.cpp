void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
};

void loop() {
  digitalWrite(2, 0);
  listenToNewSerialData(example);
};

String listenToNewSerialData(void (*myCallback)(String)) {
  digitalWrite(2, 1);
  String receivedString = "";

  while(Serial.available() > 0) {
    const char thisChar    = Serial.read()   ;
    const bool isEndOfLine = thisChar == '\n';

    if(isEndOfLine) {
      myCallback(receivedString);
      return receivedString;
    }

    receivedString += thisChar;
  };

  return receivedString;
}

void example(String myString) {
  Serial.println(myString);
};
