#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int NIGHT_MAX_LUX = 250;

struct Pins {
  struct Fotocellula {
    int ingresso = 3;
    int uscita = 2;
  } fotocellula;
  int sensoreLux = A0;
  int led = 7;
} pins;

int numberOfPeople = 0;
bool isEmpty() { return numberOfPeople == 0; };
bool hasEntered, hasExited;

void setup() {
  pinMode(pins.sensoreLux          , INPUT);
  pinMode(pins.fotocellula.ingresso, INPUT);
  pinMode(pins.fotocellula.uscita  , INPUT);
  pinMode(pins.led                 , OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
};

void loop() {
  const int livelloLux  = analogRead(pins.sensoreLux);

  const bool isEntering = digitalWrite(pins.fotocellula.ingresso);
  const bool isExiting  = digitalWrite(pins.fotocellula.uscita);

  if (isEntering != hasEntered)                numberOfPeople++;
  if ((isExiting && !isEmpty()) != hasExiting) numberOfPeople--;

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
    Serial.print(String(thisString) + "\t");
    lcd.setCursor(0, thisCursorY++);
  };
  Serial.println(" ");

  hasEntered = isEntering;
  hasExited = isExiting;
}