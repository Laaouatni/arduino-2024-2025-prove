/*  GND -> GND 
    5V  -> 5V
    VRx -> A0
    VRy -> A1
    sw  -> ...
*/

struct JoyStickPin {
  int pin;
  int value;
};

struct JoystickData {
  JoyStickPin x;
  JoyStickPin y;
};

JoystickData myJoystick = { 
  .x = {.pin = A0},
  .y = {.pin = A1}
};

void setup() {
  Serial.begin(9600);
  
  pinMode(myJoystick.x.pin, INPUT);
  pinMode(myJoystick.y.pin, INPUT);
};


void loop() {
  myJoystick.x.value = analogRead(myJoystick.x.pin);
  myJoystick.y.value = analogRead(myJoystick.y.pin);
  
  Serial.println("X: " + String(myJoystick.x.value) + "\t Y: " + String(myJoystick.y.value));
};
