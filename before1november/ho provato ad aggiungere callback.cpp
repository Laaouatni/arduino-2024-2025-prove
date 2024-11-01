void setup() {
  Serial.begin(115200);
};

void loop() {
  // const String thisNewData = getDataFromEsp8266();
  // const bool isNewData = thisNewData != "";
  // if(isNewData) Serial.println("your string: " + thisNewData);
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

// String getDataFromEsp8266() {
//   String receivedString = "";
//   bool isNewData = false;

//   while(Serial.available() > 0 && !isNewData) {
//     const char thisChar    = Serial.read()   ;
//     const bool isEndOfLine = thisChar == "\n";

//     if(isEndOfLine) return receivedString;

//     receivedString = receivedString + thisChar;
//   }
// }
