#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int NIGHT_MAX_LUX = 250;

struct pins {
  struct fotocellula {
    int ingresso = 3;
    int uscita = 2;
  };
  int sensoreLux = A0;
  int led = 7;
};

int numberOfPeople = 0;

void setup() {
  pinMode(pins.sensoreLux           , INPUT);
  pinMode(pins.fotocellula.ingresso , INPUT);
  pinMode(pins.fotocellula.uscita   , INPUT);
  pinMode(pins.led                  , OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
};

void loop() {
  const int livelloLux  = analogRead(pins.sensoreLux);

  const bool isEntering = digitalWrite(pins.fotocellula.ingresso);
  const bool isExiting  = digitalWrite(pins.fotocellula.uscita);

  if (isEntering)               numberOfPeople++;
  if (isExiting && !isEmpty())  numberOfPeople--;

  const bool isNight = pins.sensoreLux.value < NIGHT_MAX_LUX;
  const bool canSystemTurnTheLight = isNight && !isEmpty();

  digitalWrite(pins.led.id, canSystemTurnTheLight);

  String outputs[] = {
    "numero persone", String(numberOfPeople), 
    "luminosita"    , String(livelloLux)
  };
  int thisCursorY = 0;

  lcd.clear();
  for(auto thisString : outputs) {
    lcd.print(thisString);
    lcd.setCursor(0, thisCursorY++);
  };

  bool isEmpty() { return numberOfPeople == 0; }
}