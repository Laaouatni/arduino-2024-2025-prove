#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your display's I2C address.

int i=0;

void setup() {
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