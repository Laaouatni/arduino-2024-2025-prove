#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

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
  pinMode(pins.sensoreLux, INPUT);
  pinMode(pins.fotocellula.ingresso, INPUT);
  pinMode(pins.fotocellula.uscita, INPUT);
  pinMode(pins.led, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
};

void loop() {
  const int livelloLux = analogRead(pins.sensoreLux);
  const bool isEntering = digitalWrite(pins.fotocellula.ingresso);
  const bool isExiting = digitalWrite(pins.fotocellula.uscita);
  if (isEntering) numberOfPeople++;
  const bool isNight = pins.sensoreLux.value < 250;
  bool isEmpty = numberOfPeople == 0;
  if (isExiting && !isEmpty) numberOfPeople--;
  isEmpty = numberOfPeople == 0;
  const bool canSystemTurnTheLight = !isEmpty && isNight;
  digitalWrite(pins.led.id, canSystemTurnTheLight);

  int thisCursorY = 0;
  String outputs[] = {"numero persone", String(numberOfPeople), "luminosita",
                      String(livelloLux)};

  lcd.clear();
  for(auto thisString : outputs) {
    lcd.print(thisString);
    thisCursor = x++;
    lcd.setCursor(0, thisCursor);
  };
}