#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your display's I2C address.

int i=0;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  i++;
  lcd.clear();
  lcd.print(i);
  delay(50);
}