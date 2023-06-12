// 프로젝트 17 USB메세지 보드
#include <LiquidCrystal.h>

//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(2,20);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("evill Genius");
  lcd.setCursor(0,1);
  lcd.print("Rules");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == '#')
    {
      lcd.clear();
    }
    else if (ch == '/')
    {
      lcd.setCursor(0,1);
    }
    else
    {
      lcd.write(ch);
    }
  }
}
