#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your display's I2C address.

byte progressoChars[5][8] = = {
  {b10000, b11000, b11100, b11110, b11111},
  {b10000, b11000, b11100, b11110, b11111},
  {b10000, b11000, b11100, b11110, b11111},
  {b10000, b11000, b11100, b11110, b11111},
  {b10000, b11000, b11100, b11110, b11111}
};

int i=0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    lcd.createChar(i, progressoChars[i]);
  };

  lcd.begin(16,2);
  lcd.backlight();
}

void loop() {
  i++;
  const String myOutputString = String("ciao ") + String(i);
  const int posizioneXcentro = (16-myOutputString.length())/2;
  lcd.setCursor(posizioneXcentro, 0);
  lcd.print(myOutputString);
  delay(100);
  lcd.clear();
}