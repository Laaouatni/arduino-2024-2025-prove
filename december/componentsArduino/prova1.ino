void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  const int inputsPins[] = {A0, A1, 2};
  for(auto thisPin : inputsPins) {
    pinMode(thisPin, INPUT);
  }
}

struct JoyStickPin {
  int pin;
  int value;
};

struct JoystickData {
  JoyStickPin x;
  JoyStickPin y;
};

void loop() {
  JoystickData myJoystick;
  myJoystick.x = analogRead(A0);
  myJoystick.y = analogRead(A1);
  myJoystick.isClicked = analogRead(2);
  
  Serial.println("x:" + String(myJoystick.x) + "\t y:" + String(myJoystick.y) + "\t isClicked:" + String(myJoystick.isClicked));
}
