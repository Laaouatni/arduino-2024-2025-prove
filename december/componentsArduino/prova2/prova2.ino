#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

struct PinStruct {
  int id;
  float value;
};

struct pins {
  struct fotocellula {
    PinStruct ingresso  = {3};
    PinStruct uscita    = {2};
  };
  PinStruct sensoreLux  = {A0};
  PinStruct led         = {7};
};

int numberOfPeople = 0;

void setup() {
  pinMode(pins.sensoreLux          .id, INPUT );
  pinMode(pins.fotocellula.uscita  .id, INPUT );
  pinMode(pins.fotocellula.ingresso.id, INPUT );
  pinMode(pins.led                 .id, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
};

void loop() {
  pins.sensoreLux          .value = analogRead (pins.sensoreLux          .id);
  pins.fotocellula.ingresso.value = digitalRead(pins.fotocellula.ingresso.id);
  pins.fotocellula.output  .value = digitalRead(pins.fotocellula.output  .id);

  const bool isEntering = 

  const bool isEmpty = numberOfPeople == 0;
  const bool isNight = pins.sensoreLux.value < 250;

  const bool canSystemTurnTheLight = !isEmpty && isNight;

  digitalWrite(pins.led.id, canSystemTurnTheLight);
}