void example(String myString) {
  Serial.println("ciao " + myString);
};

String listenToNewSerialData(void (*myCallback)(String)) {
  String receivedString = "";

  while(Serial.available() > 0) {
    const char thisChar    = Serial.read()   ;
    const bool isEndOfLine = thisChar == '\n';

    if(isEndOfLine) {
      myCallback(receivedString);
      digitalWrite(2, !digitalRead(2));
      return receivedString;
    }

    receivedString += thisChar;
  };

  return receivedString;
};

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
};

void loop() {
  listenToNewSerialData(&example);
};

