// void example(String myString) {
//   Serial.println("ciao " + myString);
// };

// String listenToNewSerialData(void (*myCallback)(String)) {
//   String receivedString = "";

//   while(Serial.available() > 0) {
//     const char thisChar    = Serial.read()   ;
//     const bool isEndOfLine = thisChar == '\n';

//     if(isEndOfLine) {
//       myCallback(receivedString);
//       digitalWrite(2, !digitalRead(2));
//       return receivedString;
//     }

//     receivedString += thisChar;
//   };

//   return receivedString;
// };

// void setup() {
//   pinMode(2, OUTPUT);
//   Serial.begin(115200);
// };

// void loop() {
//   listenToNewSerialData(&example);
// };


void example(String myString) {
  Serial.println("ciao " + myString);  // Properly prints "ciao" with received string
}

String listenToNewSerialData(void (*myCallback)(String)) {
  static String receivedString = "";  // Accumulate across multiple calls

  // Check if there's data available in the serial buffer
  while (Serial.available() > 0) {
    char thisChar = Serial.read();
    
    // Check for newline character to determine the end of input
    if (thisChar == '\n') {
      myCallback(receivedString);       // Call the callback with the full string
      digitalWrite(2, !digitalRead(2)); // Toggle LED state
      String completedString = receivedString;
      receivedString = "";              // Clear buffer for the next message
      return completedString;
    }

    receivedString += thisChar; // Accumulate character by character
  }

  return "";
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  listenToNewSerialData(&example);  // Pass `example` as the callback
}

