void setup() {
  Serial.begin(115200);
};

void loop() {
  listenToNewSerialData([&](String myReceivedData) {
    Serial.println(myReceivedData);
  });
}

String listenToNewSerialData(void (*myCallback)(String)) {
  String receivedString = "";

  while(Serial.available() > 0) {
    const char thisChar    = Serial.read()   ;
    const bool isEndOfLine = thisChar == "\n";

    if(isEndOfLine) {
      myCallback(receivedString);
      return receivedString;
    }

    receivedString = receivedString + thisChar;
  };
}
