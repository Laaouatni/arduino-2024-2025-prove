struct JoyStickPin {
  int pin;
  int value;
};

struct JoystickData {
  JoyStickPin x;
  JoyStickPin y;
};

JoystickData myJoystick = { 
  .x = {.pin = A0, .value=analogRead(myJoystick.x.pin)} 
  .y = {.pin = A1, .value=analogRead(myJoystick.y.pin)}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  const int inputsPins[] = {A0, A1, 2};
  for(auto thisPin : inputsPins) {
    pinMode(thisPin, INPUT);
  }
}


void loop() {
  

  
  myJoystick.isClicked = analogRead(2);
  
  Serial.println("x:" + String(myJoystick.x) + "\t y:" + String(myJoystick.y) + "\t isClicked:" + String(myJoystick.isClicked));
}
