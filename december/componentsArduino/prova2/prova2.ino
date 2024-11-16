struct JoyStickPin {
  int pin;
  int value;
};

struct JoystickData {
  JoyStickPin x;
  JoyStickPin y;
};

JoystickData myJoystick = { 
  .x = {.pin = A0} 
  .y = {.pin = A1}
};

void setup() {
  Serial.begin(9600);
  const int inputsPins[] = {A0, A1};
  
  for(auto thisPin : inputsPins) {
    pinMode(thisPin, INPUT);
  }
}


void loop() {
  myJoystick.x.value = analogRead(myJoystick.x.pin);
  myJoystick.y.value = analogRead(myJoystick.y.pin);
  
  Serial.print("X: " + String(myJoystick.x.value) + "\n Y: " + String(myJoystick.y.value));
}
