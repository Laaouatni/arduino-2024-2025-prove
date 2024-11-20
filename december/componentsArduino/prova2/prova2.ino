#include <LiquidCrystal_I2C.h>

const int MAX_LINES_IN_LCD_DIGIT_SPACE = 5;
const int NUMBER_DIGIT_SPACES = 16;
const int MAX_LINES_IN_LCD_FULL_SPACE = NUMBER_DIGIT_SPACES*MAX_LINES_IN_LCD_DIGIT_SPACE;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdLinesTransitionFromTo(int myStart, int myEnd, int myDelay = 50) {
  lcd.setCursor(0,0);
  lcd.print("                ");
  int numberOfWrittenLines = min(myStart, myEnd);

  while(numberOfWrittenLines < max(myStart, myEnd)) {
    numberOfWrittenLines++;
    const int thisIndexLcdDigitSpace = numberOfWrittenLines/MAX_LINES_IN_LCD_DIGIT_SPACE;
    const int myChoosedByteCharIndex = numberOfWrittenLines-((thisIndexLcdDigitSpace)*MAX_LINES_IN_LCD_DIGIT_SPACE)+1;

    lcd.setCursor(thisIndexLcdDigitSpace, 0);
    lcd.write(byte(myChoosedByteCharIndex));

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

float lastTemperature; 

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

  if((int)lastTemperature != (int)thisTemp) {
    lcdLinesTransitionFromTo(0,map(thisTemp, 0, 50, 0, MAX_LINES_IN_LCD_FULL_SPACE));
    lcd.setCursor(0,1);
    lcd.print(String((int)thisTemp));
  };

  Serial.println(thisTemp);

  for(int i=0; i<thisTemp; i++) {
    Serial.print(
      i>MAX ? "🟥" 
            : i<MIN ? "🟩" 
                    : "⚫"
                );
  };

  Serial.println("\n\n");

  lastTemperature = thisTemp;
};
