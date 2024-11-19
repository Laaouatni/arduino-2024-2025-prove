#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdLinesTransitionFromTo(int myStart, int myEnd, int myDelay = 100) {
  lcd.clear();
  const int MAX_LINES_IN_LCD_DIGIT_SPACE = 5;
  int numberOfWrittenLines = myStart;

  while(numberOfWrittenLines < myEnd) {
    numberOfWrittenLines++;
    const int thisIndexLcdDigitSpace = numberOfWrittenLines/MAX_LINES_IN_LCD_DIGIT_SPACE;
    const int myChoosedByteCharIndex = numberOfWrittenLines-((thisIndexLcdDigitSpace)*MAX_LINES_IN_LCD_DIGIT_SPACE)+1;

    lcd.setCursor(thisIndexLcdDigitSpace, 0);
    lcd.write(byte(myChoosedByteCharIndex));

    Serial.println(numberOfWrittenLines);

    delay(myDelay);
  };
};

byte progressoChars[5][8] = {
  {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000},
  {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000},
  {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100},
  {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110},
  {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111}
};

const float DELTA = 5.0/1024.0 ;
const float K     = 10.0/1000.0;

const int ledR = 2;
const int ledV = 3;

const int MAX = 30;
const int MIN = 20;

int numberOfWrittenLines=0;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(A0, INPUT);

  for (int i = 1; i <= 5; i++) {
    lcd.createChar(i, progressoChars[i-1]);
  };

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  const int   livello  = analogRead(A0);
  const float thisTemp = (livello * DELTA) / K;

  const bool isCaldo  = thisTemp > MAX;
  const bool isFreddo = thisTemp < MIN;

  digitalWrite(ledR, isCaldo );
  digitalWrite(ledV, isFreddo);

  Serial.println(thisTemp);

  lcdLinesTransitionFromTo(0,20);

  for(int i=0; i<thisTemp; i++) {
    Serial.print(
      i>MAX ? "🟥" 
            : i<MIN ? "🟩" 
                    : "⚫"
                );
  };

  Serial.println("\n\n");
};
