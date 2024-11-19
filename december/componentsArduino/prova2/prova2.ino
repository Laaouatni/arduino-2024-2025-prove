#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your display's I2C address.

byte progressoChars[5][8] = {
  {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000},
  {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000},
  {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100},
  {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110},
  {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111}
};

int i=0;

void setup() {
  Serial.begin(9600);

  for (int i = 1; i <= 5; i++) {
    lcd.createChar(i, progressoChars[i-1]);
  };

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.backlight();
}

void loop() {
  i++;
  const int x = i/5;
  lcd.setCursor(x, 0);
  const int myByteChar = i-((x)*5)+1;
  lcd.write(byte(myByteChar));
  Serial.println("i=" + String(i) + "\t myByteChar=" + String(myByteChar));
  delay(50);
}